// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CameraSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game,DefaultConfig,meta=(DisplayName="Smash Camera settings"))
class SMASHUE_API UCameraSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	FName CameraMainTag="CameraMain";
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	FName CameraDistanceMinTag="CameraDistanceMin";
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	FName CameraDistanceMaxTag="CameraDistanceMax";
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	FName CameraBoundsTag="CameraBounds";
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	float DistanceBetweenTargetsMin=300.f;
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	float DistanceBetweenTargetsMax=1500.f;
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	float SizeDampingFactor=5.f;
	UPROPERTY(Config, EditAnywhere, Category="CameraSettings")
	float PositionDampingFactor=5.f;

};
