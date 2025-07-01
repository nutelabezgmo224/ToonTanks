// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent *SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction *IA_Fire;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction *IA_MoveForward;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction *IA_Turn;

	UPROPERTY(EditAnywhere)
	float Speed = 300.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 36.0f;

	void Move(const FInputActionValue &Value);
	void Rotate(const FInputActionValue &Value);

	APlayerController *TankPlayerController;
};
