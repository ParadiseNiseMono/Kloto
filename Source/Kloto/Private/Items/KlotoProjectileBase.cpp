// Paradise_NiseMono all rights reserved


#include "Items/KlotoProjectileBase.h"

#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AKlotoProjectileBase::AKlotoProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>("ProjectileCollisionBox");
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("ProjectileNiagaraComponent");
	ProjectileNiagaraComponent->SetupAttachment(ProjectileCollisionBox);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 600;
	ProjectileMovementComponent->MaxSpeed = 900;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileNiagaraComponent->ComponentVelocity = FVector(1.f, 0.f, 0.f);

	InitialLifeSpan = 5.f;
}

void AKlotoProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}


