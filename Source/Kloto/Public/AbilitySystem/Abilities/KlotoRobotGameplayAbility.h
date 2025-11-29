// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"
#include "KlotoRobotGameplayAbility.generated.h"

class URobotCombatComponent;
class AKlotoRobotController;
class AKlotoRobotCharacter;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoRobotGameplayAbility : public UKlotoGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	AKlotoRobotCharacter* GetRobotCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	AKlotoRobotController* GetRobotControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	URobotCombatComponent* GetRobotCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	FGameplayEffectSpecHandle MakeRobotDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
		float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
private:
	TWeakObjectPtr<AKlotoRobotCharacter> CachedKlotoRobotCharacter;
	TWeakObjectPtr<AKlotoRobotController> CachedKlotoRobotController;
};
