// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor *DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent) // Blueprint implementable event
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class AToonTanksPlayerController *PlayerController;
	class ATank *Tank;
	float StartDelay = 3.f;
	int32 TargetTurrets = 0;

	void HandleGameStart();
	int32 GetTargetTurretCount();
};
