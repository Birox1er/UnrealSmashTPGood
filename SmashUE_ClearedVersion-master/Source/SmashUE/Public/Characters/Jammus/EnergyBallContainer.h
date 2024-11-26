// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyBallContainer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API UEnergyBallContainer : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnergyBallContainer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY()
	float EnergyBallFill=0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
