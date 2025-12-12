// Paradise_NiseMono all rights reserved


#include "Items/KlotoProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "KlotoDebugHelper.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
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
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);
	
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

	if (DamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AKlotoProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn || !UKlotoFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UKlotoFunctionLibrary::NativeDoesActorHasTag(HitPawn, KlotoGameplayTags::Player_Status_Blocking);

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UKlotoFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			KlotoGameplayTags::Player_Event_SuccessfulBlock,
			Data);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void AKlotoProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AKlotoProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayLoad)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Invalid ProjectileDamageEffectSpecHandle!"));

	const bool bWasApplied = UKlotoFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);

	if (bWasApplied)
	{
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			KlotoGameplayTags::Shared_Event_HitReact,
			InPayLoad
			);
	}
}


