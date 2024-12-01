// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "Components/SphereComponent.h"
#include "SmashCharacterBasicJab.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterBasicJab : public USmashCharacterState
{
	GENERATED_BODY()
	virtual ESmashCharacterStateID GetStateID() override;

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID);
	virtual void StateExit(ESmashCharacterStateID NextStateID);
	virtual void StateTick(float DeltaTime);
	void Jab1(float DeltaTime);
	void Jab2(float DeltaTime);


protected:
	UPROPERTY()
	float Duration;
	UPROPERTY()
	float CurrentTime;
	UPROPERTY()
	int CurrentJab=0;
	UPROPERTY(EditAnywhere)
	UAnimMontage* SecondJab;
	UPROPERTY()
	TArray<UPrimitiveComponent*> HitBoxesJab;
	UPROPERTY(EditAnywhere)
	FName HitBoxesJab1Tags;
	UPROPERTY(EditAnywhere)
	FName HitBoxesJab2Tags;

};
