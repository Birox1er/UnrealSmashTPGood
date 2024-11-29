// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CommonStates/SmashCharacterState.h"
#include "EnergyBallContainer.h"
#include "SmashJammusNSpecial.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashJammusNSpecial : public USmashCharacterState
{
	GENERATED_BODY()
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	float MaxDuration=3;
};
