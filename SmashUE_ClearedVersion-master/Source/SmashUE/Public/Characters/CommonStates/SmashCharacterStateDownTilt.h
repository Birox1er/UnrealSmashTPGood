// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateDownTilt.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateDownTilt : public USmashCharacterState
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
	TArray<UPrimitiveComponent*> HitBoxesDownTilt;
	UPROPERTY(EditAnywhere)
	FName HitBoxesDownTiltTags;
};
