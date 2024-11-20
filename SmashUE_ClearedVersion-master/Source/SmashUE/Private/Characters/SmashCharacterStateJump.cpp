// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacterStateJump.h"
#include "Characters/SmashCharacterStateMachine.h"

#include "Characters/SmashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnitConversion.h"


ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->ChangeAnimation(Montage,.5/JumpDuration);
	Character->ChangeSpeed(	StateSpeed);
	Character->GetCharacterMovement()->AirControl=JumpAirControl;
	Character->IsJumping = true;
	float vel0= 2*MaxHeight/JumpDuration;
	Character->GetCharacterMovement()->JumpZVelocity=vel0;
	Character->GetCharacterMovement()->GravityScale=vel0/(JumpDuration*981);
	//CurrentPos.Z+=GetCharacterMovement()->GetGravityZ()*Timer*Timer/2+Timer*JumpMaxHeight/Duration;
	//SetActorLocation(CurrentPos);
	Character->Jump();
	
	Timer=0;
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Timer+=DeltaTime;
	if(Timer>JumpDuration)
	if(FMath::Abs(Character->GetInputMoveX())> Threshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
	}
	if(Character->GetVelocity().Z<-Threshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}