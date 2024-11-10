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
	Character->ChangeSpeed(	StateSpeed*JumpAirControl);
	Character->IsJumping = true;
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
	GEngine->AddOnScreenDebugMessage(
		1,
		0.3f,
		FColor::Red,
		"Jump State: Jump"+FString::FromInt(Timer)+"/"+FString::FromInt(JumpDuration)
		);
	if(FMath::Abs(Character->GetInputMoveX())> Threshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
	}
	if(Timer<JumpDuration)
	{
		Character->Jump(JumpDuration,MaxHeight,DeltaTime);
	}
	else
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}