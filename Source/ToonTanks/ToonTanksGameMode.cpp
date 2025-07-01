// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Turret.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    ABasePawn *DeadPawn = Cast<ABasePawn>(DeadActor);
    if (!DeadPawn)
        return;

    DeadPawn->HandleDestruction();

    if (DeadPawn->IsA(ATank::StaticClass()))
    {
        PlayerController->SetPlayerEnabledState(false);
        GameOver(false);
        return;
    }
    if (DeadPawn->IsA(ATurret::StaticClass()))
    {
        TargetTurrets--;
    }

    if (TargetTurrets <= 0)
    {
        GameOver(true);
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    StartGame();

    TargetTurrets = GetTargetTurretCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate SetPlayerStateDelegate = FTimerDelegate::CreateUObject(
            PlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            SetPlayerStateDelegate,
            StartDelay,
            false);
    }
}

int32 AToonTanksGameMode::GetTargetTurretCount()
{
    TArray<AActor *> Turrets;
    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);

    return Turrets.Num();
}