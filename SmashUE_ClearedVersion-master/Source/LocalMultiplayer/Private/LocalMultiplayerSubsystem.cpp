// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalMultiplayerSettings.h"
#include "GameFramework/PlayerController.h"
#include "LocalMultiplayerSubsystem.h"

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
		AssignKeyboardMapping(AssignNewPlayerToKeyboardProfile(i),i,ELocalMultiplayerInputMappingType::InGame);
	}

	for (int i = 0; i < Settings->NbMaxPlayer; ++i)
	{
		AssignNewPlayerToGamepadDeviceID(i);
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
	APlayerController* PlayerController=GetGameInstance()->GetLocalPlayers()[PlayerIndex]->PlayerController;
	if (PlayerController==nullptr)
	{
		return;
	}
	UInputMappingContext* IMC=Settings->KeyboardProfilesData[keyboardProfileIndex].GetIMCFromType(MappingType);
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(IMC, 1);
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceIDDeviceID)
{
	if(!PlayerIndexFromKeyboardProfileIndex.Contains(DeviceIDDeviceID))
	{
		return -1;
	}
	return PlayerIndexFromKeyboardProfileIndex[DeviceIDDeviceID];
}

int ULocalMultiplayerSubsystem::AssignedNewPlayerToGamepadID(int DeviceIDDeviceID)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return-1;
	}
	PlayerIndexFromKeyboardProfileIndex.Add( DeviceIDDeviceID,LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	if(LastAssignedPlayerIndex >= Settings->NbMaxPlayer) LastAssignedPlayerIndex = 0;
	return PlayerIndexFromKeyboardProfileIndex[DeviceIDDeviceID];
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,
	ELocalMultiplayerInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if (!Settings)
	{
		return;
	}
	APlayerController* PlayerController=GetGameInstance()->GetLocalPlayers()[PlayerIndex]->PlayerController;
	if (PlayerController==nullptr)
	{
		return;
	}
	UInputMappingContext* IMC=Settings->GamepadProfileData.GetIMCFromType(MappingType);
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(IMC, 1);
	}
}

