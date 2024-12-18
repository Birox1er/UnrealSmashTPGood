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
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;
	void TickUpdateCameraPosition(float DeltaTime);
	void TickUpdateCameraZoom(float DeltaTime);
#pragma endregion
#pragma region Follow Target
	public:
	void AddFollowTarget(UObject* Target);
	void RemoveFollowTarget(UObject* Target);
protected:
	UPROPERTY()
	TArray<UObject*> FollowTargets;
	FVector CalculateAveragePositionBetweenTargets();
	float CalculateGreatestDistanceBetweenTargets();
#pragma endregion
#pragma region Misc
public:
	virtual TStatId GetStatId() const override{return TStatId();};
protected:
	UCameraComponent* FindCameraByTag(const FName& Tag) const;
#pragma endregion
#pragma region Bounds
protected:
	UPROPERTY()
	FVector2D CameraBoundsMin;
	UPROPERTY()
	FVector2D CameraBoundsMax;
	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	AActor* FindCameraBoundsActor();

	void InitCameraBounds(AActor* CameraBoundsActor);
	void ClampPositionInCameraBounds(FVector& Position);
	void GetViewportBounds(FVector2D& OutViewportBoundsMin,FVector2d& OutViewportBoundsMax);
	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);
#pragma endregion
#pragma region Zoom
protected:
	UPROPERTY()
	float CameraZoomMin=0.f;
	UPROPERTY()
	float CameraZoomMax=0.f;
	UFUNCTION()
	void InitCameraZoomParameters();
#pragma endregion

};
