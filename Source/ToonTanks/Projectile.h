// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem *HitParticles;
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent *SmokeTrailComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent *MovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 40.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent *HitComp,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		FVector NormalImpulse,
		const FHitResult &Hit);
};
