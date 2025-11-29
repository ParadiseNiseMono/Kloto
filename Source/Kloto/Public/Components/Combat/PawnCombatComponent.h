// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AKlotoWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

/**
 * 
 */
UCLASS()
class KLOTO_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Kloto|Combat")
	void RegisterSpawnedWeapon(const FGameplayTag& InWeaponTagToRegister, AKlotoWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Kloto|Combat")
	AKlotoWeaponBase* GetCharacterCarriedWeaponByTag(const FGameplayTag& InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Kloto|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Kloto|Combat")
	AKlotoWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Kloto|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);
private:
	UPROPERTY()
	TMap<FGameplayTag, AKlotoWeaponBase*> CharacterCarriedWeaponMap;
};
