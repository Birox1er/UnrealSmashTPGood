// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/MatchGameMode.h"
#include "Arena/ArenaPlayerStart.h"
#include "Arena/ArenaSettings.h"
#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterSettings.h"
//#include "Characters/SmashCharacterInputData.h"
#include "LocalMultiplayerSubsystem.h"
#include "Kismet/GameplayStatics.h"
void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AArenaPlayerStart*> PlayerStartPoints;
	FindPlayerStartActorsInArena(PlayerStartPoints);
	SpawnCharacter(PlayerStartPoints);
}
void AMatchGameMode::FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AArenaPlayerStart::StaticClass(),FoundActors);
	for(int i = 0; i < FoundActors.Num(); ++i)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if(ArenaPlayerStartActor==nullptr)
		{
			continue;
		}
		ResultsActors.Add(ArenaPlayerStartActor);
	}
}
void AMatchGameMode::SpawnCharacter(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	USmashCharacterInputData* InputData = LoadInputDataFromConfig();
	UInputMappingContext* InputMappingContext = LoadInputMappingContextFromConfig();
	for(AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{
		EAutoReceiveInput::Type InputType=SpawnPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ASmashCharacter> SmashCharacterClass=GetSmashCharacterClassFromInputType(InputType);
		if(SmashCharacterClass == nullptr)
		{
			continue;
		}
		ASmashCharacter* NewCharacter = GetWorld()->SpawnActorDeferred<ASmashCharacter>(
		SmashCharacterClass,
		SpawnPoint->GetTransform()
		);
		if(NewCharacter == nullptr)
		{
			continue;
		}
		NewCharacter->InputData = InputData;
		NewCharacter->InputMappingContext = InputMappingContext;
		NewCharacter->AutoPossessPlayer=SpawnPoint->AutoReceiveInput;
		NewCharacter->SetOrientX(SpawnPoint->GetStartOrientX());
		NewCharacter->FinishSpawning(SpawnPoint->GetTransform());
		CharactersInsideArena.Add(NewCharacter);
	}
}

TSubclassOf<ASmashCharacter> AMatchGameMode::GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const
{
	const UArenaSettings* ArenaSettings = GetDefault<UArenaSettings>();
	switch(InputType)
	{
	case EAutoReceiveInput::Player0:
		return ArenaSettings->SmashCharacterClassP0;
	case EAutoReceiveInput::Player1:
		return ArenaSettings->SmashCharacterClassP1;
	case EAutoReceiveInput::Player2:
		return ArenaSettings->SmashCharacterClassP2;
	case EAutoReceiveInput::Player3:
		return ArenaSettings->SmashCharacterClassP3;
	default:
		return nullptr;
	}
	
}
USmashCharacterInputData* AMatchGameMode::LoadInputDataFromConfig()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	if(CharacterSettings == nullptr) return nullptr;
	return CharacterSettings->InputData.LoadSynchronous();
}
UInputMappingContext* AMatchGameMode::LoadInputMappingContextFromConfig()
{
	const USmashCharacterSettings* CharacterSettings = GetDefault<USmashCharacterSettings>();
	if(CharacterSettings == nullptr) return nullptr;
	return  CharacterSettings->InputMappingContext.LoadSynchronous();
}



