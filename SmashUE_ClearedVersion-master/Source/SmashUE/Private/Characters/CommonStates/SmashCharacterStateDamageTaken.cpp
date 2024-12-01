// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateDamageTaken.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateDamageTaken::GetStateID()
{
	return ESmashCharacterStateID::TakeDmg;
}

void USmashCharacterStateDamageTaken::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->GetCharacterMovement()->GravityScale=Character->GetEjectionVector().Y*(1+Character->GetDamageAmount()/100)/(2*981);
	Timer=0;
	TimerMult=Character->GetEjectionVector().Length();
	Character->GetCharacterMovement()->Launch(Character->GetEjectionVector()*(1+Character->GetDamageAmount()/100));
	if (TimerMult<10)
	{
		Character->PlayAnimMontage(NotEjectionMontage);
	}
	else
	{
		Character->PlayAnimMontage(Montage);
	}
}

void USmashCharacterStateDamageTaken::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	
}

void USmashCharacterStateDamageTaken::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Timer+=DeltaTime;
	if(Timer>1*TimerMult/500)
	{
		Character->GetCharacterMovement()->GravityScale=0;
		if(!Character->GetCharacterMovement()->IsMovingOnGround())
		{
			StateMachine->ChangeState(ESmashCharacterStateID::Fall);
			GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"Fall");
		}
		else
		{
			StateMachine->ChangeState(ESmashCharacterStateID::Idle);
		}
	}
	
}
