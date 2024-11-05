// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MatchGameMode.generated.h"

class AArenaPlayerStart;
/**
 * 
 */
UCLASS()
class SMASHUE_API AMatchGameMode : public AGameStateBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
private:
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>&ResultActors);
};


