// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Rotate(const FInputActionValue &Value)
{
    float Side = Value.Get<float>();
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    FVector RotationAxis = FVector(0, 0, 1 * Side);
    AddActorLocalRotation(FQuat(RotationAxis, FMath::DegreesToRadians(RotationSpeed * DeltaTime)));

    // FRotator DeltaRotation = FRotator::ZeroRotator;
    // DeltaRotation.Yaw = Side * RotationSpeed * DeltaTime;
    // AddActorLocalRotation(DeltaRotation, true);
}

void ATank::Move(const FInputActionValue &Value)
{
    float Movement = Value.Get<float>();
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    AddActorLocalOffset(FVector(Movement * DeltaTime * Speed, 0, 0));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent *EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    if (EnhancedInput != nullptr)
    {
        EnhancedInput->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ATank::Rotate);
        EnhancedInput->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ATank::Fire);
    }
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!TankPlayerController)
        return;

    FHitResult HitResult;
    bool HasHit = TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

    if (HasHit)
    {
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 24, 8, FColor::Emerald);
        this->RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction() {
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}