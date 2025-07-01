// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    bPlayerEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);
    bShowMouseCursor = bPlayerEnabled;
}