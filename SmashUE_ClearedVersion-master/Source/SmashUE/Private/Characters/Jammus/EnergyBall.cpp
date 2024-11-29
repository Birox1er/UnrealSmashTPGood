// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jammus/EnergyBall.h"


// Sets default values
AEnergyBall::AEnergyBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AEnergyBall::SetOrientX(FVector Dir)
{
	OrientX=Dir;
}

void AEnergyBall::Charge()
{
	
}

void AEnergyBall::Shoot()
{
	IsMoving=true;
}

// Called when the game starts or when spawned
void AEnergyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnergyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsMoving)
	{
		Timer+=DeltaTime;
		FVector Pos=GetActorLocation();
		SetActorLocation(Pos+OrientX*DeltaTime*Range/Duration);
	}
}

