// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoEnemyGameplayAbility.h"

#include "KlotoGameplayTags.h"
#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "Characters/KlotoEnemyCharacter.h"

AKlotoEnemyCharacter* UKlotoEnemyGameplayAbility::GetKlotoEnemyCharacterFromActorInfo()
{
	if (!CachedKlotoEnemyCharacter.IsValid())
	{
		CachedKlotoEnemyCharacter = Cast<AKlotoEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedKlotoEnemyCharacter.IsValid() ? CachedKlotoEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UKlotoEnemyGameplayAbility::GetEnemyCombatComponentFormActorInfo()
{
	return GetKlotoEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UKlotoEnemyGameplayAbility::MakeEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetKlotoAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetKlotoAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		KlotoGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}
