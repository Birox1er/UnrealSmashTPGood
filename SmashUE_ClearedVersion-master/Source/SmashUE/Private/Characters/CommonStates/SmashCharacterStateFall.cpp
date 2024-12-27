// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateFall.h"

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
	Character->PlayAnimMontage(Montage);
	Character->GetCharacterMovement()->GravityScale=FallGravityScale;
	Character->GetCharacterMovement()->AirControl=FallAirControl;

}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Character->MoveForward(DeltaTime);
	if(Character->GetInputMoveY()<-Threshold)
	{
		Character->GetCharacterMovement()->GravityScale=FallFastGravityScale;
	}
	else
	{
		Character->GetCharacterMovement()->GravityScale=FallGravityScale;
	}
	if(Character->GetVelocity().Z>-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	if(Character->GetInputSpecial()>Threshold)
	{
		Character->GetCharacterMovement()->Velocity=FVector(0, 0, 0);
		StateMachine->ChangeState(ESmashCharacterStateID::NSpecial);
	}
	if(Character->GetInputJump()>Threshold&&Character->JumpCurrentCount<Character->JumpMaxCount)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Rejump);
	}
}