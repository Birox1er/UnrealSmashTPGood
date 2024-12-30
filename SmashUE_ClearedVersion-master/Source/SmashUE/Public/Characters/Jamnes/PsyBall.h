// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacter.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ASmashCharacter* Ness=nullptr;
public:
	// Called every frames
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode();
	void MovePsyBallX(float Dir,float Speed,float DeltaTime);
	void SetNess(ASmashCharacter* ThisNess);
};
