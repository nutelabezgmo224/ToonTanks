// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	SmokeTrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke trail"));

	MovementComponent->MaxSpeed = 600;
	MovementComponent->InitialSpeed = 500;
	RootComponent = BaseMesh;
	SmokeTrailComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(
	UPrimitiveComponent *HitComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	FVector NormalImpulse,
	const FHitResult &Hit)
{
	AActor *ProjectileOwner = GetOwner();
	if (!ProjectileOwner || !OtherActor || OtherActor == this || OtherActor == ProjectileOwner)
	{
		Destroy();
		return;
	}
	auto OwnerInstigator = ProjectileOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation());
	}
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	if (HitCameraShakeClass) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	Destroy();
}
