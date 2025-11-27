// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "KlotoTypes/KlotoStructTypes.h"
#include "KlotoAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "Kloto|Ability", meta = (ApplyLevel = "1"))
	void GrantRobotWeaponAbilities(const TArray<FKlotoRobotAbilitySet>& InDefaultWeaponAbilities, int32 InApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Kloto|Ability")
	void RemoveGrantedRobotWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandleToRemove);
};
