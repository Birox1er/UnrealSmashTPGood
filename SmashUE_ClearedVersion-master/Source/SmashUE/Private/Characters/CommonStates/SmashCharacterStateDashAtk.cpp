// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterStateDashAtk.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "Components/SphereComponent.h"


ESmashCharacterStateID USmashCharacterStateDashAtk::GetStateID()
{
	return ESmashCharacterStateID::DashAtk;
}

void USmashCharacterStateDashAtk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->CanReorient=false;
	for(UActorComponent* Comp : Character->GetComponents())
	{
		if(Comp->ComponentHasTag(HitBoxesDashAtkTags))
		{
			HitBoxesDashAtk.Add(Cast<USphereComponent>(Comp));
		}
		if(Comp->ComponentHasTag(HitBoxesDashAtkTags2))
		{
			HitBoxesDashAtk2.Add(Cast<USphereComponent>(Comp));
		}
	}
	CurrentTime=0;
	Duration=Character->PlayAnimMontage(Montage,2);
	Character->ChangeSpeed(StateSpeed);
}

void USmashCharacterStateDashAtk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->CanReorient=true;

}

void USmashCharacterStateDashAtk::StateTick(float DeltaTime)
{
	CurrentTime+=DeltaTime*2;
	if(CurrentTime<Duration*45/77)
	{
		Character->AddMovementInput(Character->GetActorForwardVector(),Character->GetOrientX(),true);

	}
	if(CurrentTime<Duration*25/77)
	{
		return;
	}
	if(CurrentTime<Duration*35/77)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesDashAtk)
		{
			HitBox->SetGenerateOverlapEvents(true);
		}
	}
	else if(CurrentTime<Duration*45/77)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesDashAtk)
		{
			HitBox->SetGenerateOverlapEvents(false);
		}
		for(UPrimitiveComponent* HitBox : HitBoxesDashAtk2)
		{
			HitBox->SetGenerateOverlapEvents(true);
		}
	}
	else if (CurrentTime<Duration)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesDashAtk2)
		{
			HitBox->SetGenerateOverlapEvents(false);
		}
		if(Character->GetInputAtk()>Threshold)
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
	}
	else if(CurrentTime>Duration+.2f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	Super::StateTick(DeltaTime);
}
