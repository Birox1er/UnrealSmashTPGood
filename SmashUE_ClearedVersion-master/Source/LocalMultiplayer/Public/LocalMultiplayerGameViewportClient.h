// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "LocalMultiplayerGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class LOCALMULTIPLAYER_API ULocalMultiplayerGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;
	virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;
	virtual bool InputAxis(FViewport* Viewport, FInputDeviceId InputDevice, FKey Key, float Delta, float DeltaTime, int32 NumSamples=1, bool bGamepad=false) override;
};
