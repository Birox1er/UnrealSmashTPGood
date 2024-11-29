// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Jamnes/PsyBall.h"


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
	
}

// Called every frame
void APsyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APsyBall::Explode()
{
	
}
void APsyBall::MovePsyBall()
{
	
}


