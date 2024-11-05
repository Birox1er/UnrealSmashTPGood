// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter
{
#pragma region Unreal Defaults
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASmashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion
#pragma region Orient
public:
	float GetOrientX() const;
	void SetOrientX(float NewOrientX);
protected:
	UPROPERTY(BlueprintReadOnly)
	float OrientX=1.f;
	void RotateMeshUsingOrientX()const;
#pragma endregion
};