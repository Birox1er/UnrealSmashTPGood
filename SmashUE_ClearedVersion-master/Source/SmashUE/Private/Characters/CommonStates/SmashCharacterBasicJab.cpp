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
}

void USmashCharacterBasicJab::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	switch(CurrentJab)
	{
		case 0:
			Jab1(DeltaTime);
		break;
		case 1:
			Jab2(DeltaTime);
		break;
		default: ;
	}
	
}

void USmashCharacterBasicJab::Jab2(float DeltaTime)
{
	CurrentTime+=DeltaTime;
	if(CurrentTime<Duration*5/15)
	{
		return;
	}
	if(CurrentTime<Duration*10/15)
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
	}
	else if(CurrentTime<Duration+.2f&&Character->GetInputAtk()>Threshold)
	{
		CurrentJab=0;
		StateMachine->ChangeState(ESmashCharacterStateID::NAtk);
	}
	else if(CurrentTime>Duration+.2f)
	{
		CurrentJab=0;
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}

void USmashCharacterBasicJab::Jab1(float DeltaTime)
{
	CurrentTime+=DeltaTime;
	if(CurrentTime<Duration*5/15)
	{
		return;
	}
	if(CurrentTime<Duration*10/15)
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
	}
	else if(CurrentTime<Duration+.2f&&Character->GetInputAtk()>Threshold)
	{
		CurrentJab++;
		StateMachine->ChangeState(ESmashCharacterStateID::NAtk);
	}
	else if(CurrentTime>Duration+.2f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}


