// Fill out your copyright notice in the Description page of Project Settings.
#include "LocalMultiplayerSubsystem.h"
#include "LocalMultiplayerSettings.h"
#include "GameFramework/PlayerController.h"

#include "EnhancedInputSubsystems.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayer(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return;
	}

	for (int i = 0; i < Settings->KeyboardProfilesData.Num(); ++i)
	{
		AssignKeyboardMapping(AssignNewPlayerToKeyboardProfile(i),i,MappingType);
	}

	for (int i = 0; i < Settings->NbMaxPlayer; ++i)
	{
		AssignGamepadInputMapping(AssignedNewPlayerToGamepadID(i),MappingType);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if(!PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		return -1;
	}
	return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return-1;
	}
	PlayerIndexFromKeyboardProfileIndex.Add( KeyboardProfileIndex,LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	if(LastAssignedPlayerIndex >= Settings->KeyboardProfilesData.Num()) LastAssignedPlayerIndex = 0;
	return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int keyboardProfileIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return;
	}
	if(GetGameInstance()->GetLocalPlayerByIndex(PlayerIndex)==nullptr)
	{
		FString OutError;
		GetGameInstance()->CreateLocalPlayer(PlayerIndex,OutError,true);
	}
	APlayerController* PlayerController=GetGameInstance()->GetLocalPlayers()[PlayerIndex]->PlayerController;
	if (PlayerController==nullptr)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystem==nullptr)
	{
		return;
	}
	UInputMappingContext* IMC=Settings->KeyboardProfilesData[keyboardProfileIndex].GetIMCFromType(MappingType);
	
	InputSubsystem->AddMappingContext(IMC, 1);

}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceIDDeviceID)
{
	if(!PlayerIndexFromGamepadProfileIndex.Contains(DeviceIDDeviceID))
	{
		return -1;
	}
	return PlayerIndexFromGamepadProfileIndex[DeviceIDDeviceID];
}

int ULocalMultiplayerSubsystem::AssignedNewPlayerToGamepadID(int DeviceIDDeviceID)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return-1;
	}
	PlayerIndexFromGamepadProfileIndex.Add( DeviceIDDeviceID,LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	if(LastAssignedPlayerIndex >= Settings->NbMaxPlayer) LastAssignedPlayerIndex = 0;
	return PlayerIndexFromGamepadProfileIndex[DeviceIDDeviceID];
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
    
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (Settings == nullptr)
	{
		return;
	}

	const FLocalMultiplayerProfileData& ProfileData = Settings->GamepadProfileData;

	UInputMappingContext* IMC = ProfileData.GetIMCFromType(MappingType);
	if (!IMC)
	{
		return;
	}

	UGameInstance* GameInstance = GetGameInstance();
	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);

	if(LocalPlayer == nullptr)
	{
		FString OutError;
		LocalPlayer = GameInstance->CreateLocalPlayer(PlayerIndex,  OutError, true);
	}
    
	APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
	if (!PlayerController)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystem == nullptr)
	{
		return;
	}

	InputSubsystem->AddMappingContext(IMC, 1);
}

