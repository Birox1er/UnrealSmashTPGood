// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class USmashCharacterStateMachine;

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
#pragma region State Machine
public:
	void CreateStateMachine();
	void InitStateMachine();
	void TickStateMachine(float DeltaTime) const;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USmashCharacterStateMachine> StateMachine;
	
#pragma endregion
#pragma region Animation
public:
	void ChangeAnimation(UAnimMontage* Anim);
protected:
	UAnimMontage* YourAnimations;
#pragma endregion
#pragma region Movement
public:
	void ChangeSpeed(float NewSpeed);
	void MoveForward();
protected:
	float Speed=0.f;
	
};
