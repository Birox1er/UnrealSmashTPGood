// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "EditorClassUtils.h"
#include "ToolBuilderUtil.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraFollowTarget.h"
#include "Characters/SmashCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain= FindCameraByTag(TEXT("CameraMain"));

	AActor* CameraBoundActor=FindCameraBoundsActor();
	if(CameraBoundActor!=nullptr)
	{
		InitCameraBounds(CameraBoundActor);
	}
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraPosition(DeltaTime);
}

void UCameraWorldSubsystem::AddFollowTarget(UObject* Target)
{
	FollowTargets.Add(Target);
}

void UCameraWorldSubsystem::RemoveFollowTarget(UObject* Target)
{
	if(FollowTargets.Contains(Target))
	{
		FollowTargets.Remove(Target);
	}
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector CurrentLocation=CalculateAveragePositionBetweenTargets();
	ClampPositionInCameraBounds(CurrentLocation);
	CameraMain->GetAttachParentActor()->SetActorLocation(CurrentLocation);
}

AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"CameraBounds",FoundActors);
	return FoundActors[0];
}

void UCameraWorldSubsystem::InitCameraBounds(AActor* CameraBoundsActor)
{
	FVector BoundsCenter;
	FVector BoundsExtent;
	CameraBoundsActor->GetActorBounds(false, BoundsCenter, BoundsExtent);
	CameraBoundsMin=FVector2d(BoundsCenter.X-BoundsExtent.X, BoundsCenter.Z-BoundsExtent.Z);
	CameraBoundsMax=FVector2d(BoundsCenter.X+BoundsExtent.X, BoundsCenter.Z+BoundsExtent.Z);
	CameraBoundsYProjectionCenter=BoundsCenter.Y;
}

void UCameraWorldSubsystem::ClampPositionInCameraBounds(FVector& Position)
{
	FVector2D ViewportBoundsMin,ViewportBoundsMax;
	GetViewportBounds(ViewportBoundsMin, ViewportBoundsMax);
	FVector WorldBoundsMin=CalculateWorldPositionFromViewportPosition(ViewportBoundsMin);
	FVector WorldBoundsMax=CalculateWorldPositionFromViewportPosition(ViewportBoundsMax);
	if(Position.X+WorldBoundsMax.X/2>CameraBoundsMax.X)//-CameraMain->OrthoWidth/2)
	{
		Position.X=CameraBoundsMax.X-WorldBoundsMax.X/2;//-CameraMain->OrthoWidth/2;
	}
	else if(Position.X+WorldBoundsMin.X/2<CameraBoundsMin.X)//+CameraMain->OrthoWidth/2)
	{
		Position.X=CameraBoundsMin.X+WorldBoundsMin.X;//+CameraMain->OrthoWidth/2;
	}
	if(Position.Z+WorldBoundsMin.Z/2>CameraBoundsMax.Y)//-CameraMain->OrthoWidth/CameraMain->AspectRatio/2)
	{
 		Position.Z=CameraBoundsMax.Y-WorldBoundsMin.Z/2;//-CameraMain->OrthoWidth/CameraMain->AspectRatio/2;
	}
	else if(Position.Z+WorldBoundsMax.Z/2<CameraBoundsMin.Y)//+CameraMain->OrthoWidth/CameraMain->AspectRatio/2)
	{
		Position.Z=CameraBoundsMin.Y+WorldBoundsMax.Z;//+ CameraMain->OrthoWidth/CameraMain->AspectRatio/2;
	}
}

void UCameraWorldSubsystem::GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2d& OutViewportBoundsMax)
{
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	if(ViewportClient==nullptr) return;
	FViewport* Viewport=ViewportClient->Viewport;
	if(Viewport==nullptr) return;
	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetSizeXY()+Viewport->GetInitialPositionXY());
	FIntRect ViewportRect =Viewport->CalculateViewExtents(CameraMain->AspectRatio,ViewRect);
	OutViewportBoundsMin.X=ViewportRect.Min.X;
	OutViewportBoundsMin.Y=ViewportRect.Min.Y;
	
	OutViewportBoundsMax.X=ViewportRect.Max.X;
	OutViewportBoundsMax.Y=ViewportRect.Max.Y;
}

FVector UCameraWorldSubsystem::CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition)
{
	if(CameraMain==nullptr)	return FVector::ZeroVector;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if(PlayerController==nullptr)	return FVector::ZeroVector;
	float YDistanceToCenter=CameraMain->GetOwner()->GetActorLocation().Y-CameraBoundsYProjectionCenter;
	FVector CameraWorldProjectDir;
	FVector WorldPosition;
	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewportPosition,
		WorldPosition,
		CameraWorldProjectDir);
	WorldPosition+=CameraWorldProjectDir*YDistanceToCenter;
	return WorldPosition;
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector CurrentLocationY=FVector(0, CameraMain->GetAttachParentActor()->GetActorLocation().Y, 0);
	FVector Average = FVector::ZeroVector;
	if(FollowTargets.Num() > 0)
	{
		int Index = 0;
		for(int32 i = 0; i < FollowTargets.Num(); i++)
		{
			if(FollowTargets[i]->GetClass()->ImplementsInterface(UCameraFollowTarget::StaticClass())&&Cast<ASmashCharacter>(FollowTargets[i])->IsFollowing())
			{
				Average += Cast<ASmashCharacter>(FollowTargets[i])->GetFollowPosition();
				Index++;
			}
		}
		Average = FVector(Average.X / Index,0,Average.Z/Index)+CurrentLocationY;	
	}
	return Average;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UCameraComponent* Cam=nullptr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),Tag,FoundActors);
	if(FoundActors.Num() > 0)
	{
		if(FoundActors[0]->GetComponentByClass<UCameraComponent>()!=nullptr)
		{
			GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,FString::FromInt(FoundActors.Num()));
			Cam=FoundActors[0]->GetComponentByClass<UCameraComponent>();
		}
	}
	return Cam;
}
