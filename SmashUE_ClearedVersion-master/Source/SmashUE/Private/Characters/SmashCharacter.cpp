// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacter.h"

#include "EnhancedPlayerInput.h"
#include "MaterialHLSLTree.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LocalMultiplayerSubsystem.h"
#include "Camera/CameraWorldSubsystem.h"
#include "Characters/SmashCharacterInputData.h"
#include "Characters/CommonStates/SmashCharacterStateID.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"
#include "Slate/SGameLayerManager.h"


// Sets default values
ASmashCharacter::ASmashCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASmashCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateStateMachine();
	InitStateMachine();

	GetWorld()->GetSubsystem<UCameraWorldSubsystem>()->AddFollowTarget(this);
}



// Called every frame
void ASmashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine(DeltaTime);
	if(GetCharacterMovement()->IsMovingOnGround()&&CanReorient)
	{
		if(OrientX>0.1)
		{
			SetLastOrientX(1);
		}
		if(OrientX<0.1)
		{
			SetLastOrientX(-1);
		}
		RotateMeshUsingOrientX();
	}
	CurrentPos=GetActorLocation();
}

// Called to bind functionality to input
void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//SetupInputMappingContextIntoController();
	UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent==nullptr)return;
	BindInputMoveAxisAndAction(EnhancedInputComponent);
	BindInputJump(EnhancedInputComponent);
	BindInputAtk(EnhancedInputComponent);
}

float ASmashCharacter::GetOrientX() const
{
	return OrientX;
}

void ASmashCharacter::SetOrientX(float NewOrientX)
{
	
	OrientX = NewOrientX;
}

void ASmashCharacter::SetLastOrientX(float NewOrientX)
{
	LastOrientX=NewOrientX;
}

void ASmashCharacter::RotateMeshUsingOrientX() const
{
	FRotator Rotation=GetMesh()->GetRelativeRotation();
	int X=LastOrientX;

	Rotation.Yaw = -90.f*X;
	GetMesh()->SetRelativeRotation(Rotation);
}

void ASmashCharacter::CreateStateMachine()
{
	StateMachine= NewObject<USmashCharacterStateMachine>(this);
}

void ASmashCharacter::InitStateMachine()
{
	if(StateMachine==nullptr) return;
	StateMachine->Init(this);
}

void ASmashCharacter::TickStateMachine(float DeltaTime) const
{
	if(StateMachine==nullptr) return;
	StateMachine->Tick(DeltaTime);
}

void ASmashCharacter::ChangeSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed=NewSpeed;
}

void ASmashCharacter::MoveForward(float DeltaTime)
{
	/*if(IsJumping)
	{
		FVector CurrentLocation=this->GetActorLocation();
		CurrentLocation.X+=DeltaTime*GetCharacterMovement()->MaxWalkSpeed*GetInputMoveX();
		SetActorLocation(CurrentLocation);
	}
	else*/
	AddMovementInput(GetActorForwardVector(),GetInputMoveX(),true);
	
}

float ASmashCharacter::GetInputMoveX() const
{
	return InputMoveX;
}

void ASmashCharacter::BindInputMoveAxisAndAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData==nullptr) return;
	if(InputData->InputActionMoveX)
	{
		EnhancedInputComponent->BindAction(

		InputData->InputActionMoveX,
		ETriggerEvent::Started,
		this,
		&ASmashCharacter::OnInputMoveX
		);
		EnhancedInputComponent->BindAction(

		InputData->InputActionMoveX,
		ETriggerEvent::Triggered,
		this,
		&ASmashCharacter::OnInputMoveX
		);
		EnhancedInputComponent->BindAction(

		InputData->InputActionMoveX,
		ETriggerEvent::Completed,
		this,
		&ASmashCharacter::OnInputMoveX
		);
	}
	if(InputData->InputActionMoveXFast)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveXFast,
			ETriggerEvent::Triggered,
			this,
			&ASmashCharacter::OnInputMoveXFast
			);
	}
	if(InputData->InputActionMoveY)
	{
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveY,
			ETriggerEvent::Started,
			this,
			&ASmashCharacter::OnInputMoveY
			);
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveY,
			ETriggerEvent::Triggered,
			this,
			&ASmashCharacter::OnInputMoveY
			);
		EnhancedInputComponent->BindAction(
			InputData->InputActionMoveY,
			ETriggerEvent::Completed,
			this,
			&ASmashCharacter::OnInputMoveY
			);
	}
}

void ASmashCharacter::OnInputMoveX(const FInputActionValue& InputActionValue)
{
	InputMoveX=InputActionValue.Get<float>();
}

void ASmashCharacter::OnInputMoveXFast(const FInputActionValue& InputActionValue)
{
	InputMoveX=InputActionValue.Get<float>();
	InputMoveXFastEvent.Broadcast(InputMoveX);
}

float ASmashCharacter::GetInputJump() const
{
	return InputJump;
}

void ASmashCharacter::BindInputJump(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData==nullptr) return;
	if(InputData->InputActionJump)
	{
		EnhancedInputComponent->BindAction(

		InputData->InputActionJump,
		ETriggerEvent::Started,
		this,
		&ASmashCharacter::OnInputJump
		);
		EnhancedInputComponent->BindAction(
		InputData->InputActionJump,
		ETriggerEvent::Completed,
		this,
		&ASmashCharacter::OnInputJump
		);
	}
}

void ASmashCharacter::OnInputJump(const FInputActionValue& InputActionValue)
{
	InputJump=InputActionValue.Get<float>();
}

float ASmashCharacter::GetInputMoveY() const
{
	return  InputMoveY;
}

void ASmashCharacter::OnInputMoveY(const FInputActionValue& InputActionValue)
{
	InputMoveY=InputActionValue.Get<float>();
}

FVector ASmashCharacter::GetFollowPosition()
{
	return CurrentPos;
}

bool ASmashCharacter::IsFollowing()
{
	return IsFollowable;
}
float ASmashCharacter::GetInputSpecial() const
{
	return InputSpecial;
}
void ASmashCharacter::BindInputSpecialAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData==nullptr) return;
	if(InputData->InputActionSpecial)
	{
		EnhancedInputComponent->BindAction(

		InputData->InputActionSpecial,
		ETriggerEvent::Started,
		this,
		&ASmashCharacter::OnInputSpecial
		);
		EnhancedInputComponent->BindAction(
		InputData->InputActionSpecial,
		ETriggerEvent::Completed,
		this,
		&ASmashCharacter::OnInputSpecial
		);
	}
}
void ASmashCharacter::OnInputSpecial(const FInputActionValue& InputActionValue)
{
	InputSpecial=InputActionValue.Get<float>();
}

float ASmashCharacter::GetInputAtk() const
{
	return InputAtk;
}

void ASmashCharacter::BindInputAtk(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(
	InputData->InputAtk,
	ETriggerEvent::Started,
	this,
	&ASmashCharacter::OnInputAtk
	);
	EnhancedInputComponent->BindAction(
	InputData->InputAtk,
	ETriggerEvent::Completed,
	this,
	&ASmashCharacter::OnInputAtk
	);
}

void ASmashCharacter::OnInputAtk(const FInputActionValue& InputActionValue)
{
	InputAtk=InputActionValue.Get<float>();
}

float ASmashCharacter::GetDamageAmount() const
{
	return DamageTaken;
}

FVector ASmashCharacter::GetEjectionVector() const
{
	return EjectionVector;
}

void ASmashCharacter::AddDamageAmount(float NewDamageAmount)
{
	DamageTaken+=NewDamageAmount;
}

void ASmashCharacter::OnDamageTaken(FVector NewEjectionVector,float Damage)
{
	AddDamageAmount(Damage);
	EjectionVector=NewEjectionVector;
	StateMachine->ChangeState(ESmashCharacterStateID::TakeDmg);
}



