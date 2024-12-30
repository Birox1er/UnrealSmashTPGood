// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateDownTilt.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "Components/SphereComponent.h"


ESmashCharacterStateID USmashCharacterStateDownTilt::GetStateID()
{
	return ESmashCharacterStateID::DAtk;
}

void USmashCharacterStateDownTilt::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	for(UActorComponent* Comp : Character->GetComponents())
	{
		if(Comp->ComponentHasTag(HitBoxesDownTiltTags))
		{
			HitBoxesDownTilt.Add(Cast<USphereComponent>(Comp));
		}
	}
	CurrentTime=0;
	Duration=Character->PlayAnimMontage(Montage);
}

void USmashCharacterStateDownTilt::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	for(UPrimitiveComponent* HitBox : HitBoxesDownTilt)
	{
		HitBox->SetGenerateOverlapEvents(false);
	}
}

void USmashCharacterStateDownTilt::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	CurrentTime+=DeltaTime;
	if(CurrentTime<Duration*6/21)
	{
		return;
	}
	if(CurrentTime<Duration*15/21)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesDownTilt)
		{
			HitBox->SetGenerateOverlapEvents(true);
		}
	}
	else if(CurrentTime>Duration)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesDownTilt)
		{
			HitBox->SetGenerateOverlapEvents(false);
		}
		if (Character->GetInputAtk()>Threshold)
		{
			if(Character->GetInputMoveY()>Threshold)
			{
				StateMachine->ChangeState(ESmashCharacterStateID::UAtk);
			}
			else if(Character->GetInputMoveY()<-Threshold)
			{
				StateMachine->ChangeState(ESmashCharacterStateID::DAtk);
			}
			else
			{
				StateMachine->ChangeState(ESmashCharacterStateID::NAtk);
			}
		}
		else
		{
			StateMachine->ChangeState(ESmashCharacterStateID::Idle);
		}
	}
}
