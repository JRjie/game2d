// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "AZDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;

UCLASS()
class GAME2D_API AAZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	AAZDCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityY;

protected:

	UPROPERTY(EditAnywhere, Category = "Input|Keyboard|Move")
	UInputMappingContext* IM_MoveContext;

	UPROPERTY(EditAnywhere, Category = "Input|Keyboard|Move")
	UInputAction* IA_MoveUpAnDown;

	UPROPERTY(EditAnywhere, Category = "Input|Keyboard|Move")
	UInputAction* IA_MoveLeftAndRight;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveUpAndDown(const FInputActionValue& InputValue);
	void MoveLeftAndRight(const FInputActionValue& InputValue);
};
