// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jamnes/SmashJamnesNSpecial.h"

#include "Characters/SmashCharacterStateMachine.h"
#include "Characters/CommonStates/SmashCharacterStateID.h"


ESmashCharacterStateID USmashJamnesNSpecial::GetStateID()
{
	return ESmashCharacterStateID::NSpecial;
}

void USmashJamnesNSpecial::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	
	PsyBall=GetWorld()->SpawnActor<APsyBall>(PsyBallClass,Character->GetActorLocation(), Character->GetActorRotation());
	timer=0;;
}

void USmashJamnesNSpecial::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashJamnesNSpecial::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	timer+=DeltaTime;
	if(timer>MaxDuration||Character->GetInputSpecial()<Threshold)
	{
		if(PsyBall!=nullptr)
		{
			PsyBall->OnExplode();

		}
		if(timer>MaxDuration+1.5)
		{
			StateMachine->ChangeState(ESmashCharacterStateID::Idle);
		}
	}
	else if(abs(Character->GetInputMoveX())>Threshold)
	{
		PsyBall->MovePsyBallX(Character->GetInputMoveX(),30,DeltaTime);
	}
}
