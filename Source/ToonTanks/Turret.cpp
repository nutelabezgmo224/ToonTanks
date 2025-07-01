// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (TankInRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition()
{
    if (TankInRange())
    {
        Fire();
    }
}

bool ATurret::TankInRange()
{
    if (!Tank)
        return false;

    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    return Distance <= CallRadius;
}