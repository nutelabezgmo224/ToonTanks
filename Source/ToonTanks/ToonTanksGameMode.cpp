// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (Tank == Cast<ATank>(DeadActor))
    {
        Tank->HandleDestruction();
        PlayerController->SetPlayerEnabledState(false);
        return;
    }
    ABasePawn *DeadPawn = Cast<ABasePawn>(DeadActor);
    DeadPawn->HandleDestruction();
}

void AToonTanksGameMode::HandleGameStart()
{
    StartGame();

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