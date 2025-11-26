// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KlotoGameplayAbility.generated.h"

class UKlotoAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EKlotoAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility	Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category = "KlotoAbility")
	EKlotoAbilityActivationPolicy ActivationPolicy = EKlotoAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Kloto|Ability")
	UKlotoAbilitySystemComponent* GetKlotoAbilitySystemComponentFromActorInfo() const;
};
