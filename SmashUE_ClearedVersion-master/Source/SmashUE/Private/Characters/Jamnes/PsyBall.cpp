// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jamnes/PsyBall.h"

#include "Misc/MapErrors.h"


// Sets default values
APsyBall::APsyBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APsyBall::BeginPlay()
{
	Super::BeginPlay();
	Mesh=FindComponentByTag<UStaticMeshComponent>("PsyBall");
}

// Called every frame
void APsyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APsyBall::MovePsyBallX(float Dir,float Speed,float DeltaTime)
{
	if(Mesh!=nullptr&&CanMove)
	{
		FVector ImpulseVector = FVector(1*Dir*Speed*DeltaTime*2,0,0);
		Mesh->AddImpulse(ImpulseVector);
	}
}

void APsyBall::SetNess(ASmashCharacter* ThisNess)
{
	Ness=ThisNess;
}


