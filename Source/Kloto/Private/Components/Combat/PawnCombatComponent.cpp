// Paradise_NiseMono all rights reserved


#include "Components/Combat/PawnCombatComponent.h"

#include "Items/Weapons/KlotoWeaponBase.h"
#include "KlotoDebugHelper.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister,
                                                 AKlotoWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

AKlotoWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AKlotoWeaponBase* const* WeaponBase = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *WeaponBase;
		}
	}

	return nullptr;
}

AKlotoWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AKlotoWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		check(WeaponToToggle);

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Enabled"));
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Disabled"));
		}
	}
}
