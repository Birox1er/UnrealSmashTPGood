// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SmashCharacterInputData.generated.h"

/**
 * 
 */
UCLASS()
class SMASHUE_API USmashCharacterInputData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputActionMoveX;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputActionMoveXFast;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputActionJump;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputActionMoveY;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputActionSpecial;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAtk;
};
