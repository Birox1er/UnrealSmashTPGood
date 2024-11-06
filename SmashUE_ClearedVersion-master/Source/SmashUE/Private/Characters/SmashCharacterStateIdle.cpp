// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateIdle.h"

#include "Characters/SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeAnimation(Montage);
	Character->ChangeSpeed(StateSpeed);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Enter State: Idle")
	);
}
void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateEnter(NextStateID);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit State: Idle")
	);
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Tick State: Idle")
	);
}
