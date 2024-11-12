// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "EditorClassUtils.h"
#include "ToolBuilderUtil.h"
#include "Camera/CameraComponent.h"
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

void UCameraWorldSubsystem::AddFollowTarget(AActor* Target)
{
	FollowTargets.Add(Target);
}

void UCameraWorldSubsystem::RemoveFollowTarget(AActor* Target)
{
	if(FollowTargets.Contains(Target))
	{
		FollowTargets.Remove(Target);
	}
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector CurrentLocation=CalculateAveragePositionBetweenTargets();
	CameraMain->SetWorldLocation(CurrentLocation);
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector Average = FVector::ZeroVector;
	if(FollowTargets.Num() > 0)
	{
		for(int32 i = 0; i < FollowTargets.Num(); i++)
		{
			Average = Average + FollowTargets[i]->GetActorLocation();
		}
		Average = Average / FollowTargets.Num();	
	}
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,FString::SanitizeFloat(Average.X));
	return Average;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UCameraComponent* Cam=nullptr;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),Tag,FoundActors);
	if(FoundActors.Num() > 0)
	{
		Cam = Cast<UCameraComponent>(FoundActors[0]);
	}
	return Cam;
}
