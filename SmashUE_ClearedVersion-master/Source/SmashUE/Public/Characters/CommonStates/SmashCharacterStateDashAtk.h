// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateDashAtk.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateDashAtk : public USmashCharacterState
{
	GENERATED_BODY()

public:

	virtual ESmashCharacterStateID GetStateID() override;

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID);
	virtual void StateExit(ESmashCharacterStateID NextStateID);
	virtual void StateTick(float DeltaTime);
protected:
	UPROPERTY()
	float Duration;
	UPROPERTY()
	float CurrentTime;
	UPROPERTY()
	TArray<UPrimitiveComponent*> HitBoxesDashAtk;
	UPROPERTY()
	TArray<UPrimitiveComponent*> HitBoxesDashAtk2;
	UPROPERTY(EditAnywhere)
	FName HitBoxesDashAtkTags;
	UPROPERTY(EditAnywhere)
	FName HitBoxesDashAtkTags2;
};
