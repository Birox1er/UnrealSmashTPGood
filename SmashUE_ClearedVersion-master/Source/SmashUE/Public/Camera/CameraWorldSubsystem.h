// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
#pragma region Subsytems Overrides
	public:
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
protected:
#pragma endregion
#pragma region Main Camera
	public:
	virtual TStatId GetStatId() const override{return TStatId();};
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;
#pragma endregion
#pragma region Follow Target
	public:
	void AddFollowTarget(UObject* Target);
	void RemoveFollowTarget(UObject* Target);
protected:
	UPROPERTY()
	TArray<UObject*> FollowTargets;
	FVector CalculateAveragePositionBetweenTargets();
#pragma endregion
#pragma region Misc
public:
protected:
	UCameraComponent* FindCameraByTag(const FName& Tag) const;
	void TickUpdateCameraPosition(float DeltaTime);
#pragma endregion
	#pragma region Bounds

};
