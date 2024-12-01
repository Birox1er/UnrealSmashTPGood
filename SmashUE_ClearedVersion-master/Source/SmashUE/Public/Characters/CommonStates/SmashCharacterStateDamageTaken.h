// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateDamageTaken.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateDamageTaken : public USmashCharacterState
{
	GENERATED_BODY()
public:
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	float Timer=0;
	UPROPERTY()
	float TimerMult=1;
	UPROPERTY(EditAnywhere)
	UAnimMontage* NotEjectionMontage;
};
