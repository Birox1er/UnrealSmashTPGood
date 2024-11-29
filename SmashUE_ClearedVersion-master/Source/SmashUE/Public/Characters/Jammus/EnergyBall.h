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
	UFUNCTION(BlueprintCallable)
	void Charge();
	UFUNCTION(BlueprintCallable)
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float Damage=1.f;
	UPROPERTY(EditAnywhere)
	float Duration=800.f;
	UPROPERTY(EditAnywhere)
	float Range=800.f;
	UPROPERTY()
	FVector OrientX=FVector(1, 0, 0);
	UPROPERTY(EditAnywhere)
	FVector EjectionVector=FVector(0.7f, 0.7f, 0);
	UPROPERTY(EditAnywhere)
	float EjectionFactor=1.f;
	UPROPERTY()
	bool IsMoving=false;
	UPROPERTY()
	float Timer=0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
