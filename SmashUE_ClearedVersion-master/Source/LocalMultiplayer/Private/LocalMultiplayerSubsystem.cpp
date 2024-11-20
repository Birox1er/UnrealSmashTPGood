// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalMultiplayerSettings.h"
#include "GameFramework/PlayerController.h"
#include "LocalMultiplayerSubsystem.h"

void ULocalMultiplayerSubsystem::CreateAndInitPlayer(ELocalMultiplayerInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* MultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	if(MultiplayerSettings==nullptr)return;
	int j=0;
	for(int i =0;i<MultiplayerSettings->NbMaxPlayer;i++)
	{
		if(i<MultiplayerSettings->GetNbKeyboardProfiles())
		{
			APlayerController
		}
		else
		{
			PlayerIndexFromGamepadProfileIndex.Emplace(i-j,i);
		}
	}
}
