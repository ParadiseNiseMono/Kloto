// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AKlotoWeaponBase;
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
private:
	UPROPERTY()
	TMap<FGameplayTag, AKlotoWeaponBase*> CharacterCarriedWeaponMap;
};
