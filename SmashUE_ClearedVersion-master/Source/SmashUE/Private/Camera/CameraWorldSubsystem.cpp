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
	CameraMain->GetAttachParentActor()->SetActorLocation(CurrentLocation);
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
			if(FollowTargets[i]->Implements<ICameraFollowTarget>()&&Cast<ASmashCharacter>(FollowTargets[i])->IsFollowing())
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
		if(Cam==nullptr)
		{
			
		}
	}
	return Cam;
}
