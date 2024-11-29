// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterMultiJump.h"

#include "Characters/SmashCharacter.h"
#include "Characters/CommonStates/SmashCharacterStateID.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterMultiJump::GetStateID()
{
	return ESmashCharacterStateID::Rejump;
}

void USmashCharacterMultiJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	if(Character->GetInputMoveX()*Character->GetOrientX()<0)
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"Jump Back");

		Character->PlayAnimMontage(MontageBackJump);;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"Jump");

		Character->PlayAnimMontage(Montage);;
	}
	Character->ChangeSpeed(	StateSpeed);
	Character->GetCharacterMovement()->AirControl=JumpAirControl;
	Character->IsJumping = true;
	float vel0= (2*MaxHeight/JumpDuration);
	Character->GetCharacterMovement()->JumpZVelocity=vel0;
	Character->GetCharacterMovement()->GravityScale=vel0/(JumpDuration*981);
	//CurrentPos.Z+=GetCharacterMovement()->GetGravityZ()*Timer*Timer/2+Timer*JumpMaxHeight/Duration;
	//SetActorLocation(CurrentPos);
	Character->Jump();

	Timer=0;
}

void USmashCharacterMultiJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterMultiJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Timer+=DeltaTime;
	if(Timer>JumpDuration)
	{
		Character->StopJumping();
	}
	if(Character->GetVelocity().Z<-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
	if(Character->GetInputSpecial()>Threshold)
	{
		Character->GetCharacterMovement()->Velocity=FVector(0, 0, 0);
		StateMachine->ChangeState(ESmashCharacterStateID::NSpecial);
	}
}


