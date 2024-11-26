// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyBall.generated.h"

UCLASS()
class SMASHUE_API AEnergyBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnergyBall();
	void SetOrientX(FVector Dir);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float Damage=1.f;
	UPROPERTY(EditAnywhere)
	float Speed=800.f;
	UPROPERTY(EditAnywhere)
	float Range=800.f;
	UPROPERTY()
	FVector OrientX;
	UPROPERTY()
	FVector EjectionVector;
	UPROPERTY(EditAnywhere)
	float EjectionFactor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
