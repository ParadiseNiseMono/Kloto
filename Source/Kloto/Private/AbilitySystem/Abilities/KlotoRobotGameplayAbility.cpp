// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoRobotGameplayAbility.h"

#include "KlotoGameplayTags.h"
#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "Characters/KlotoRobotCharacter.h"
#include "Controllers/KlotoRobotController.h"

AKlotoRobotCharacter* UKlotoRobotGameplayAbility::GetRobotCharacterFromActorInfo()
{
	if (!CachedKlotoRobotCharacter.IsValid())
	{
		CachedKlotoRobotCharacter = Cast<AKlotoRobotCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedKlotoRobotCharacter.IsValid() ? CachedKlotoRobotCharacter.Get() : nullptr;
}

AKlotoRobotController* UKlotoRobotGameplayAbility::GetRobotControllerFromActorInfo()
{
	if (!CachedKlotoRobotController.IsValid())
	{
		CachedKlotoRobotController = Cast<AKlotoRobotController>(CurrentActorInfo->PlayerController);
	}

	return CachedKlotoRobotController.IsValid() ? CachedKlotoRobotController.Get() : nullptr;
}

URobotCombatComponent* UKlotoRobotGameplayAbility::GetRobotCombatComponentFromActorInfo()
{
	return GetRobotCharacterFromActorInfo()->GetRobotCombatComponent();
}

FGameplayEffectSpecHandle UKlotoRobotGameplayAbility::MakeRobotDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetKlotoAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetKlotoAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(KlotoGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}
