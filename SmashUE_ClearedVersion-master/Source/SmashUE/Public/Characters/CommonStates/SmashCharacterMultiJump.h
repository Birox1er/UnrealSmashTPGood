// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterMultiJump.generated.h"
class USmashCharacterInputData;

/**
 * 
 */
UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterMultiJump : public USmashCharacterState
{
	GENERATED_BODY()
public:
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	float MaxHeight=280;
	UPROPERTY(EditAnywhere)
	float JumpDuration=1;
	UPROPERTY(EditAnywhere)
	float JumpAirControl=1;
	UPROPERTY(EditAnywhere)
	UAnimMontage* MontageBackJump;
	UPROPERTY(EditAnywhere)
	float TimeBeforeRejump=1;
private:
	float Timer=0;
};
