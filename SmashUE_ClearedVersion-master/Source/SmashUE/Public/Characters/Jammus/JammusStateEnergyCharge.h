// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "JammusStateEnergyCharge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API UJammusStateEnergyCharge : public USmashCharacterState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	float ChargeTime=3;

};
