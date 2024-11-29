// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jammus/SmashJammusNSpecial.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
//#include "EnergyBallContainer.generated.h.h"


ESmashCharacterStateID USmashJammusNSpecial::GetStateID()
{
	return ESmashCharacterStateID::NSpecial;
}

void USmashJammusNSpecial::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	//UEnergyBallContainer* Container=Character->GetComponents(UEnergyBallContainer)
	if(FMath::Abs(Character->GetCharacterMovement()->Velocity.Z)>Threshold)
	{
		//Shoot
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}

}

void USmashJammusNSpecial::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashJammusNSpecial::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(Character->GetInputSpecial()<Threshold)
	{

	StateMachine->ChangeState(ESmashCharacterStateID::Idle);

	}
	//charge;
}
