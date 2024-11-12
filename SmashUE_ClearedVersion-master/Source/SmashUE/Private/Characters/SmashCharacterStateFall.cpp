// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateFall.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeSpeed(StateSpeed*FallAirControl);
	Character->ChangeAnimation(Montage);
	Character->GetCharacterMovement()->GravityScale=FallGravityScale;
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->IsJumping=false;
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(FMath::Abs(Character->GetInputMoveX())> Threshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
	}
	if(Character->GetInputMoveY()<-Threshold)
	{
		Character->GetCharacterMovement()->GravityScale=FallFastGravityScale;
	}
	else
	{
		Character->GetCharacterMovement()->GravityScale=FallAirControl;
	}
	if(Character->GetVelocity().Z>-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}