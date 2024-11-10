// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateWalk.h"

#include <filesystem>

#include "Characters/SmashCharacterStateMachine.h"

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
	Character->InputMoveXFastEvent.AddDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);

}

void USmashCharacterStateWalk::OnInputMoveXFast(float X)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateEnter(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);

}
void USmashCharacterStateWalk::StateTick(float DeltaTime)
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
