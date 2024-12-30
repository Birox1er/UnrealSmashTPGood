// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PsyBall.h"
#include "Characters/CommonStates/SmashCharacterState.h"
#include "SmashJamnesNSpecial.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashJamnesNSpecial : public USmashCharacterState
{
	GENERATED_BODY()

public:
	virtual ESmashCharacterStateID GetStateID() override;

	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APsyBall* PsyBall;
	UPROPERTY(EditDefaultsOnly, Category = "Ness Projectile")
	TSubclassOf<APsyBall> PsyBallClass;
	UPROPERTY(EditAnywhere)
	float MaxDuration=2.f;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ReleaseMontage;
	float Timer;
	float EndTimer;
};
