// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LocalMultiplayerSettings.h"
#include "LocalMultiplayerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API ULocalMultiplayerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CreateAndInitPlayer(ELocalMultiplayerInputMappingType MappingType);

	int GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex);

	int AssignedNewPlayerToKeyboardProfile(int KeyboardProfileIndex);

	void AssignKeyboardMapping(int PlayerIndex,int keyboardProfileIndex,ELocalMultiplayerInputMappingType MappingType )const;

	int GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceIDDeviceID);

	int AssignedNewPlayerToGamepadID(int DeviceIDDeviceID);

	void AssignGamepadInputMapping(int PlayerIndex,ELocalMultiplayerInputMappingType MappingType )const;

protected:
	UPROPERTY()
	uint8 LastAssignedPlayerIndex=0;
	UPROPERTY()
	TMap<int,int>PlayerIndexFromKeyboardProfileIndex;
	UPROPERTY()
	TMap<int,int>PlayerIndexFromGamepadProfileIndex;
};
	