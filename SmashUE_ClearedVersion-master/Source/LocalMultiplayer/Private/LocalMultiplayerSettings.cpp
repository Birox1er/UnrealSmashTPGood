// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplayerInputMappingType MappingType) const
{
	UInputMappingContext* MappingContext = GetIMCFromType(MappingType);
	for(FEnhancedActionKeyMapping Mapping : MappingContext->GetMappings())
	{
		if(Mapping.Key == Key) return true;
	}
	return false;
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplayerInputMappingType MappingType) const
{
	if(MappingType==ELocalMultiplayerInputMappingType::Menu)
	{
		return IMCMenu;
	}
	else if(MappingType==ELocalMultiplayerInputMappingType::InGame)
	{
		return IMCInGame;
	}
	return nullptr;
}

int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key,
	ELocalMultiplayerInputMappingType MappingType) const
{
	int i=0;
	for(FLocalMultiplayerProfileData KeyboardProfile: KeyboardProfilesData)
	{
		if(KeyboardProfile.ContainsKey(Key, MappingType))
		{
			return i;
		}
		i++;
	}
	return -1;
}

