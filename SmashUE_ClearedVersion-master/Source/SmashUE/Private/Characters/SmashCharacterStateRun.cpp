// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateRun.h"

#include "Characters/SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeAnimation(Montage);
	Character->ChangeSpeed(StateSpeed);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Enter State: Run")
	);
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit State: Run")
	);
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Black,
		TEXT("Tick State: Run")
	);
}

