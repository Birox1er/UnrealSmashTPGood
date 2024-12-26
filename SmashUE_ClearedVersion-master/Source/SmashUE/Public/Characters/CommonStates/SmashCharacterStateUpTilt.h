// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateUpTilt.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateUpTilt : public USmashCharacterState
{
public:
	GENERATED_BODY()

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
	TArray<UPrimitiveComponent*> HitBoxesUpTilt;
	UPROPERTY(EditAnywhere)
	FName HitBoxesUpTiltTags;
};
