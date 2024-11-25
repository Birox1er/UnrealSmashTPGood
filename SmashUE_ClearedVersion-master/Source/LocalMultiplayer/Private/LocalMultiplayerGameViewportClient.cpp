// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"
#include "LocalMultiplayerSettings.h"
#include"Engine/GameViewportClient.h"
#include "Engine/Console.h"
#include "GameFramework/PlayerInput.h"
#include "LocalMultiplayerSubsystem.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	MaxSplitscreenPlayers=8;
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if(GameInstance == nullptr)
		return false;
    
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
    
	if (LocalMultiplayerSettings == nullptr || LocalMultiplayerSubsystem == nullptr) return false;
	int PlayerIndex =-1;
    if(!EventArgs.IsGamepad())
    {
    	int KeyboardProfileIndex = LocalMultiplayerSettings->FindKeyboardProfileIndexFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);
    
    	 PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(KeyboardProfileIndex);
    }
	else
	{
		 PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(EventArgs.InputDevice.GetId());;
	}
	if(PlayerIndex < 0)
	{
		GEngine->AddOnScreenDebugMessage(1,1,FColor::Red,"Player index is invalid");
		LocalMultiplayerSubsystem->CreateAndInitPlayer(ELocalMultiplayerInputMappingType::InGame,EventArgs.IsGamepad(),EventArgs.Key,EventArgs.InputDevice.GetId());
		return false;
	}
	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
	if (LocalPlayer == nullptr)
		return false;
    
	APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
	if (PlayerController == nullptr)
		return false;
    
	return PlayerController->InputKey(EventArgs.Key, EventArgs.Event, EventArgs.AmountDepressed, EventArgs.IsGamepad());

}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* InViewport, FInputDeviceId InputDevice, FKey Key,
	float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if(GameInstance == nullptr)
		return false;
    
	const ULocalMultiplayerSettings* LocalMultiplayerSettings = GetDefault<ULocalMultiplayerSettings>();
	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
    
	if (LocalMultiplayerSettings == nullptr || LocalMultiplayerSubsystem == nullptr) return false;
    
	int PlayerIndex = LocalMultiplayerSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId());

	if(PlayerIndex < 0) return false;
    
	ULocalPlayer* LocalPlayer = GameInstance->GetLocalPlayerByIndex(PlayerIndex);
	if (LocalPlayer == nullptr)	return false;
	
	APlayerController* PlayerController = LocalPlayer->GetPlayerController(GameInstance->GetWorld());
	if (PlayerController == nullptr)return false;
		
	return PlayerController->InputAxis(Key, Delta, DeltaTime,NumSamples, bGamepad);
}
