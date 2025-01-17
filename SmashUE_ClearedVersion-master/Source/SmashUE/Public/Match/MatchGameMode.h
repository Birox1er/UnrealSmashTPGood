// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"


class USmashCharacterInputData;
class UInputMappingContext;
class ASmashCharacter;
class AArenaPlayerStart;

/**
 * 
 */
UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
	TArray<ASmashCharacter*>CharactersInsideArena;
private:
	USmashCharacterInputData* LoadInputDataFromConfig();
	UInputMappingContext* LoadInputMappingContextFromConfig();
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>&ResultActors);
	void SpawnCharacter(const TArray<AArenaPlayerStart*>&SpawnPoints);
	TSubclassOf<ASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;

};


