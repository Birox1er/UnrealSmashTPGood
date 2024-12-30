// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CommonStates/SmashCharacterBasicJab.h"

#include <filesystem>

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterBasicJab::GetStateID()
{
	return ESmashCharacterStateID::NAtk;
}

void USmashCharacterBasicJab::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	HitBoxesJab.Empty();
	for(UActorComponent* Comp : Character->GetComponents())
	{
		if(CurrentJab==0)
		{
			if(Comp->ComponentHasTag(HitBoxesJab1Tags))
			{
				HitBoxesJab.Add(Cast<USphereComponent>(Comp));
			}
		}
		if(CurrentJab==1)
		{
			if(Comp->ComponentHasTag(HitBoxesJab2Tags))
			{
				HitBoxesJab.Add(Cast<USphereComponent>(Comp));
			}
		}
	}
	CurrentTime=0;
	if(CurrentJab==0)
	{
		Duration=Character->PlayAnimMontage(Montage);
	}
	else if(CurrentJab==1)
	{
		Duration=Character->PlayAnimMontage(SecondJab);
	}
}

void USmashCharacterBasicJab::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	if(NextStateID!=ESmashCharacterStateID::NAtk||CurrentJab>1)
	{
		CurrentJab=0;
	}
	for(UPrimitiveComponent* HitBox : HitBoxesJab)
	{
		HitBox->SetGenerateOverlapEvents(true);
	}
}

void USmashCharacterBasicJab::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	CurrentTime+=DeltaTime;
	if((CurrentTime<Duration*5/15&&CurrentJab==0)||(CurrentJab==1&&CurrentTime<Duration*10/26))
	{
		return;
	}
	if((CurrentTime<Duration*10/15&&CurrentJab==0)||(CurrentJab==1&&CurrentTime<Duration*16/26))
	{
		for(UPrimitiveComponent* HitBox : HitBoxesJab)
		{
			HitBox->SetGenerateOverlapEvents(true);
		}
	}
	else if(CurrentTime<Duration)
	{
		for(UPrimitiveComponent* HitBox : HitBoxesJab)
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
				CurrentJab++;
				StateMachine->ChangeState(ESmashCharacterStateID::NAtk);
			}
		}
	}
	else
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	
}