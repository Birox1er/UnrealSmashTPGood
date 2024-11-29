// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterState.h"

#include "Characters/CommonStates/SmashCharacterStateID.h"
#include "Characters/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterState::USmashCharacterState()
{

	PrimaryComponentTick.bCanEverTick = false;

}

ESmashCharacterStateID USmashCharacterState::GetStateID()
{
	return ESmashCharacterStateID::None;
}

void USmashCharacterState::StateInit(USmashCharacterStateMachine* InStateMachine)
{
	StateMachine = InStateMachine;
	Character = InStateMachine->GetCharacter();
	Threshold=GetThreshold();
}

float USmashCharacterState::GetThreshold()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	if(CharacterSettings == nullptr) return 0;
	return  CharacterSettings->InputMoveXThreshold;
}

void USmashCharacterState::StateEnter(ESmashCharacterStateID PreviousStateID)
{
}

void USmashCharacterState::StateExit(ESmashCharacterStateID NextStateID)
{
}

void USmashCharacterState::StateTick(float DeltaTime)
{
}


