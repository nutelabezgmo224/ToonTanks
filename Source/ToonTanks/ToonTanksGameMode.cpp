// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "BasePawn.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    ABasePawn *DeadPawn = Cast<ABasePawn>(DeadActor);
    DeadPawn->HandleDestruction();
}