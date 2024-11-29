// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterBasicJab.h"

#include <filesystem>

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"


ESmashCharacterStateID USmashCharacterBasicJab::GetStateID()
{
	return ESmashCharacterStateID::NAtk;
}

void USmashCharacterBasicJab::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	CurrentTime=0;
	GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"JAb");
	Duration=Character->PlayAnimMontage(Montage);
}

void USmashCharacterBasicJab::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashCharacterBasicJab::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	CurrentTime+=DeltaTime;
	if(CurrentTime>Duration*5/18&&CurrentTime<Duration*12/18)
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,FString::SanitizeFloat(CurrentTime/18));
	}
	else if(CurrentTime>Duration*15/18)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}
