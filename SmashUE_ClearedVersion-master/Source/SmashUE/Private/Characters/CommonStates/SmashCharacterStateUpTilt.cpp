// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateUpTilt.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "Components/SphereComponent.h"


ESmashCharacterStateID USmashCharacterStateUpTilt::GetStateID()
{
	return ESmashCharacterStateID::UAtk;
}

void USmashCharacterStateUpTilt::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	for(UActorComponent* Comp : Character->GetComponents())
	{
		if(Comp->ComponentHasTag(HitBoxesUpTiltTags))
		{
			HitBoxesUpTilt.Add(Cast<USphereComponent>(Comp));
		}
	}
	CurrentTime=0;
	Duration=Character->PlayAnimMontage(Montage);

}

void USmashCharacterStateUpTilt::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	for(UPrimitiveComponent* HitBox : HitBoxesUpTilt)
	{
		HitBox->SetGenerateOverlapEvents(false);
	}
}

void USmashCharacterStateUpTilt::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	CurrentTime+=DeltaTime;
	if(CurrentTime<Duration*520/1774)
	{
		return;
	}
	if(CurrentTime<Duration*760/1774)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesUpTilt)
		{
			HitBox->SetGenerateOverlapEvents(true);
		}
	}
	else if(CurrentTime<Duration*1448/1774)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesUpTilt)
		{
			HitBox->SetGenerateOverlapEvents(false);
		}
	}
	else if(CurrentTime<Duration+.2f&&Character->GetInputAtk()>Threshold)
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
	else if(CurrentTime>Duration+.2f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}
