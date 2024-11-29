// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PsyBall.generated.h"

UCLASS()
class SMASHUE_API APsyBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APsyBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float PsyBallSpeed=30.f;
	UPROPERTY(EditAnywhere)
	float PsyBallRadius=10.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Explode();
	void MovePsyBall();
};
