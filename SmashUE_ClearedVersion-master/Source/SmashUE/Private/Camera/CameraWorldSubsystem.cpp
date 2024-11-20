// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "EditorClassUtils.h"
#include "FrameTypes.h"
#include "ToolBuilderUtil.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraFollowTarget.h"
#include "Camera/CameraSettings.h"
#include "Characters/SmashCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	const UCameraSettings* CameraSettings=GetDefault<UCameraSettings>();
	if(CameraSettings==nullptr) return;
	Super::OnWorldBeginPlay(InWorld);
	CameraMain= FindCameraByTag(CameraSettings->CameraMainTag);

	AActor* CameraBoundActor=FindCameraBoundsActor();
	if(CameraBoundActor!=nullptr)
	{
		InitCameraBounds(CameraBoundActor);
	}
	InitCameraZoomParameters();
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickUpdateCameraZoom(DeltaTime);
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
	const UCameraSettings* CameraSettings=GetDefault<UCameraSettings>();
	if(CameraSettings==nullptr) return;
	FVector BaseLocation=CameraMain->GetAttachParentActor()->GetActorLocation();
	FVector CurrentLocation=CalculateAveragePositionBetweenTargets();
	ClampPositionInCameraBounds(CurrentLocation);
	CameraMain->GetAttachParentActor()->SetActorLocation(BaseLocation+(CurrentLocation-BaseLocation)*DeltaTime*CameraSettings->PositionDampingFactor);
}

void UCameraWorldSubsystem::TickUpdateCameraZoom(float DeltaTime)
{
	const UCameraSettings* CameraSettings=GetDefault<UCameraSettings>();
	if(CameraSettings==nullptr) return;
	if(CameraMain==nullptr)return;
	float GreatestDistanceBetweenTargets=CalculateGreatestDistanceBetweenTargets();
	float CurrentInvZoom=UKismetMathLibrary::NormalizeToRange(GreatestDistanceBetweenTargets,
		CameraSettings->DistanceBetweenTargetsMin,
		CameraSettings->DistanceBetweenTargetsMax);
	if(CurrentInvZoom>1)
	{
		CurrentInvZoom=1;
	}
	else if(CurrentInvZoom<0)
	{
		CurrentInvZoom=0;
	}
	FVector BaseLocation=CameraMain->GetAttachParentActor()->GetActorLocation();
	FVector CurrentLocation=CameraMain->GetAttachParentActor()->GetActorLocation();
	CurrentLocation.Y =FMath::Lerp(CameraZoomMin,CameraZoomMax,CurrentInvZoom);
	CameraMain->GetAttachParentActor()->SetActorLocation(BaseLocation+(CurrentLocation-BaseLocation)*DeltaTime*CameraSettings->SizeDampingFactor);
}

AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
{
	const UCameraSettings* CameraSettings=GetDefault<UCameraSettings>();
	if(CameraSettings==nullptr) return nullptr;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraBoundsTag,FoundActors);
	if(FoundActors.Num()>0)
	{
		return FoundActors[0];
	}
	return nullptr;
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
	FVector Diag=(WorldBoundsMax-WorldBoundsMin);
	if(Position.X>CameraBoundsMax.X-Diag.X/2)
	{
		Position.X=CameraBoundsMax.X-Diag.X/2;
	}
	else if(Position.X<CameraBoundsMin.X+Diag.X/2)
	{
		Position.X=CameraBoundsMin.X+Diag.X/2;
	}
	if(Position.Z>CameraBoundsMax.Y+Diag.Z/2)
	{
		Position.Z=CameraBoundsMax.Y+Diag.Z/2;
	}
	else if(Position.Z<CameraBoundsMin.Y-Diag.Z/2)
	{
		Position.Z=CameraBoundsMin.Y-Diag.Z/2;
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

void UCameraWorldSubsystem::InitCameraZoomParameters()
{
	const UCameraSettings* CameraSettings=GetDefault<UCameraSettings>();
	if(CameraSettings==nullptr) return;
	TArray<AActor*> FoundActorsMin;
	TArray<AActor*> FoundActorsMax;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraDistanceMinTag,FoundActorsMin);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),CameraSettings->CameraDistanceMaxTag,FoundActorsMax);
	if(FoundActorsMin.Num()>0)
	{
		CameraZoomMin=FoundActorsMin[0]->GetActorLocation().Y;

	}
	if(FoundActorsMax.Num()>0)
	{
		CameraZoomMax=FoundActorsMax[0]->GetActorLocation().Y;

	}
	
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

float UCameraWorldSubsystem::CalculateGreatestDistanceBetweenTargets()
{
	float GreatestDistance=0;
	if(FollowTargets.Num() > 1)
	{
		for(int32 i = 0; i < FollowTargets.Num()-1; i++)
		{
			for(int32 j = i+1; j < FollowTargets.Num(); j++)
			{
				float CurrentDistance = FVector::Dist(Cast<ASmashCharacter>(FollowTargets[i])->GetFollowPosition(),Cast<ASmashCharacter>(FollowTargets[j])->GetFollowPosition());
				if(GreatestDistance<CurrentDistance)
				{
					GreatestDistance=CurrentDistance;
				}
			}
		}
	}
	return GreatestDistance;
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
			Cam=FoundActors[0]->GetComponentByClass<UCameraComponent>();
		}
	}
	return Cam;
}
