// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KlotoRobotGameplayAbility.h"
#include "KlotoRobotGA_TargetLock.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoRobotGA_TargetLock : public UKlotoRobotGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameAbilityInterface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameAbilityInterface
};
