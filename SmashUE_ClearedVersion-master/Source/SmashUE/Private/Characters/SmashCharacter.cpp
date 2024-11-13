// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmashCharacter.h"

#include "EnhancedPlayerInput.h"
#include "MaterialHLSLTree.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraWorldSubsystem.h"
#include "Characters/SmashCharacterInputData.h"
#include "Characters/SmashCharacterStateID.h"
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
	MoveForward(DeltaTime);
	RotateMeshUsingOrientX();
	CurrentPos=GetActorLocation();
}

// Called to bind functionality to input
void ASmashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	SetupInputMappingContextIntoController();
	UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent==nullptr)return;
	BindInputMoveAxisAndAction(EnhancedInputComponent);
	BindInputJump(EnhancedInputComponent);
}

float ASmashCharacter::GetOrientX() const
{
	return OrientX;
}

void ASmashCharacter::SetOrientX(float NewOrientX)
{
	OrientX = NewOrientX;
}

void ASmashCharacter::RotateMeshUsingOrientX() const
{
	FRotator Rotarion=GetMesh()->GetRelativeRotation();
	Rotarion.Yaw = -90.f*OrientX;
	GetMesh()->SetRelativeRotation(Rotarion);
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

void ASmashCharacter::ChangeAnimation(UAnimMontage* Anim,float I)
{
		PlayAnimMontage(Anim,I);
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
		AddMovementInput(GetActorForwardVector(),OrientX);
	
}
void ASmashCharacter::SetupInputMappingContextIntoController() const
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController==nullptr) return;
	ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if(Player==nullptr) return;
	UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(InputSystem==nullptr) return;
	InputSystem->AddMappingContext(InputMappingContext,0);
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
	if(!IsJumping)
	{
		return InputJump;
	}
	return 0;
}

void ASmashCharacter::BindInputJump(UEnhancedInputComponent* EnhancedInputComponent)
{
	if(InputData==nullptr) return;
	if(InputData->InputActionMoveX)
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

void ASmashCharacter::Jump(float Duration, float JumpMaxHeight,float Timer)
{
	float vel0= JumpMaxHeight/Duration;
	GetCharacterMovement()->JumpZVelocity=vel0;
	//CurrentPos.Z+=GetCharacterMovement()->GetGravityZ()*Timer*Timer/2+Timer*JumpMaxHeight/Duration;
	//SetActorLocation(CurrentPos);
	ACharacter::Jump();
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
