// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateRun.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"


ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeAnimation(Montage);
	Character->ChangeSpeed(StateSpeed);

}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(FMath::Abs(Character->GetInputMoveX())< Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
	}
	if(Character->GetInputJump()>Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Jump);
	}
	if(Character->GetVelocity().Z<-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}

