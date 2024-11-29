// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jamnes/SmashJamnesNSpecial.h"
#include "Characters/CommonStates/SmashCharacterStateID.h"


ESmashCharacterStateID USmashJamnesNSpecial::GetStateID()
{
	return ESmashCharacterStateID::NSpecial;
}

void USmashJamnesNSpecial::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
}

void USmashJamnesNSpecial::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashJamnesNSpecial::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
}
