// Paradise_NiseMono all rights reserved


#include "Items/PickUps/KlotoStoneBase.h"

#include "KlotoGameplayTags.h"
#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "Characters/KlotoRobotCharacter.h"

void AKlotoStoneBase::Consume(UKlotoAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* Effect = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, ApplyLevel, AbilitySystemComponent->MakeEffectContext());

	BP_OnStoneConsumed();
}

void AKlotoStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickUpCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                           SweepResult);

	if (AKlotoRobotCharacter* OverlappedCharacter = Cast<AKlotoRobotCharacter>(OtherActor))
	{
		OverlappedCharacter->GetKlotoAbilitySystemComponent()->TryActivateAbilityByTag(KlotoGameplayTags::Player_Ability_PickUp_Stones);
	}
}
