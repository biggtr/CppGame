#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "SMagicProjectile.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ShpereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(ShpereComponent);
	ShpereComponent->SetCollisionProfileName("Projectile");
	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComponent->SetupAttachment(ShpereComponent);

	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

