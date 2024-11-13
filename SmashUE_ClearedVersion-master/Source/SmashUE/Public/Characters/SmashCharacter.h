// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraFollowTarget.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class USmashCharacterStateMachine;
class UInputMappingContext;
class USmashCharacterInputData;

UCLASS()
class SMASHUE_API ASmashCharacter : public ACharacter
									//public ICameraFollowTarget
{
	GENERATED_BODY()
	
#pragma region Unreal Defaults
public:
	// Sets default values for this character's properties
	ASmashCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
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
	void ChangeAnimation(UAnimMontage* Anim,float I=1);
#pragma endregion
#pragma region Movement
public:
	void ChangeSpeed(float NewSpeed);
	void MoveForward(float deltaTime);
	
#pragma endregion
#pragma region Input Data / Mapping Context
public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY()
	TObjectPtr<USmashCharacterInputData> InputData;
protected:
	void SetupInputMappingContextIntoController() const;
#pragma endregion
#pragma region Input Move X

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveXEvent, float,InputMoveX);
public:
	float GetInputMoveX() const;
	UPROPERTY()
	FInputMoveXEvent InputMoveXFastEvent;
protected:
	UPROPERTY()
	float InputMoveX=0.f;
private:
	
	void BindInputMoveAxisAndAction(UEnhancedInputComponent* EnhancedInputComponent);

	void OnInputMoveX(const FInputActionValue& InputActionValue);
	void OnInputMoveXFast(const ::FInputActionValue& InputActionValue);
#pragma endregion
#pragma region Jump/Fall
public:
	float GetInputJump() const;
	bool IsJumping=false;
	void BindInputJump(UEnhancedInputComponent* EnhancedInputComponent);
	void Jump(float Duration,float JumpMaxHeight,float DeltaTime);
	void OnInputJump(const FInputActionValue& InputActionValue);
protected:
	UPROPERTY()
	float InputJump=0.f;

#pragma endregion
#pragma region Input Move Y
	public:
	float GetInputMoveY() const;

protected:
	FVector CurrentPos=this->GetActorLocation();
	float InputMoveY;
private:
	
	void OnInputMoveY(const FInputActionValue& InputActionValue);
#pragma endregion
	
};
