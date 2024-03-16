// Fill out your copyright notice in the Description page of Project Settings.


#include "AZDCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"
#include "APlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"


AAZDCharacter::AAZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	VelocityX = 0;
	VelocityY = 0;
}


void AAZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AAPlayerController* PlayerController = Cast<AAPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IM_MoveContext, 0);
		}
	}
}

void AAZDCharacter::MoveUpAndDown(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();

	if (Controller != nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
		FVector velocity_ = this->GetVelocity();
		VelocityX = velocity_.X;
		VelocityY = velocity_.Y;
	}
}

void AAZDCharacter::MoveLeftAndRight(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();

	if (Controller != nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
		FVector velocity_ = this->GetVelocity();
		VelocityX = velocity_.X;
		VelocityY = velocity_.Y;
	}
}

void AAZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAZDCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveUpAnDown, ETriggerEvent::Triggered, this, &AAZDCharacter::MoveUpAndDown);
		EnhancedInputComponent->BindAction(IA_MoveLeftAndRight, ETriggerEvent::Triggered, this, &AAZDCharacter::MoveLeftAndRight);
	}
}