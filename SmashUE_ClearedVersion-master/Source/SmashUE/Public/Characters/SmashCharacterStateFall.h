// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateFall.generated.h"


UCLASS(ClassGroup=(SmashCharacterState), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateFall : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
	UFUNCTION()
	void OnInputMoveY(float InputMoveY);
protected:
	UPROPERTY(EditAnywhere)
	float MaxHeight=280;
	UPROPERTY(EditAnywhere)
	float FallGravityScale=3;
	UPROPERTY(EditAnywhere)
	float FallAirControl=1;
	UPROPERTY(EditAnywhere)
	float FallFastGravityScale=5;
};
