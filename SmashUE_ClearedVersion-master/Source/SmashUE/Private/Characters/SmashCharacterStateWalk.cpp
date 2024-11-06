// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateWalk.h"

#include "Characters/SmashCharacter.h"


ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}
void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeAnimation(Montage);
	Character->ChangeSpeed(StateSpeed);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Green,
		TEXT("Enter State: Walk")
	);
}
void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateEnter(NextStateID);
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Exit State: Walk")
	);
}
void USmashCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Tick State: Walk")
	);
}
