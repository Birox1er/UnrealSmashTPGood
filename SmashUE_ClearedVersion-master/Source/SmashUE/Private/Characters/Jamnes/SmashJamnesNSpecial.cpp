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
	Timer=0;
	EndTimer=0;
	Character->PlayAnimMontage(Montage);
}

void USmashJamnesNSpecial::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void USmashJamnesNSpecial::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Timer+=DeltaTime;
	if(Timer>MaxDuration||Character->GetInputSpecial()<Threshold)
	{
		if(PsyBall!=nullptr&&EndTimer==0)
		{
			EndTimer=Timer;
			Character->StopAnimMontage(Montage);
			Character->PlayAnimMontage(ReleaseMontage);
			PsyBall->OnExplode();
		}
		if(Timer>EndTimer+1.5f)
		{
			StateMachine->ChangeState(ESmashCharacterStateID::Idle);
		}
	}
	else if(abs(Character->GetInputMoveX())>Threshold)
	{
		PsyBall->MovePsyBallX(Character->GetInputMoveX(),30,DeltaTime);
	}
}
