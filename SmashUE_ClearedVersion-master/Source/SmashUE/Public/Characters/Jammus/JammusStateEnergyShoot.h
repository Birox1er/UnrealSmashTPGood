// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "JammusStateEnergyShoot.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API UJammusStateEnergyShoot : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
};
