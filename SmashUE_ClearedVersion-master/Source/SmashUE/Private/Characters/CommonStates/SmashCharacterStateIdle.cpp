// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateIdle.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterSettings.h"
#include "Characters/SmashCharacterStateMachine.h"


ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->InputMoveXFastEvent.AddDynamic(this,&USmashCharacterStateIdle::OnInputMoveXFast);
	Character->ChangeAnimation(Montage);
	Character->ChangeSpeed(StateSpeed);
}
void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateEnter(NextStateID);
	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateIdle::OnInputMoveXFast);

}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(FMath::Abs(Character->GetInputMoveX())>Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Walk);
	}
	if(Character->GetInputJump()>Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Jump);
	}
	if(Character->GetVelocity().Z<-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
	if(Character->GetInputSpecial()>Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::NSpecial);
	}
	if(Character->GetInputAtk()>Threshold)
	{
		if(Character->GetInputMoveY()>Threshold)
		{
			GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"Fall");
			StateMachine->ChangeState(ESmashCharacterStateID::UAtk);
		}
		else
		{
			StateMachine->ChangeState(ESmashCharacterStateID::NAtk);
		}
	}
}
