// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KlotoRobotGameplayAbility.h"
#include "RobotGA_PickUpStones.generated.h"

class AKlotoStoneBase;
/**
 * 
 */
UCLASS()
class KLOTO_API URobotGA_PickUpStones : public UKlotoRobotGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameAbilityInterface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameAbilityInterface

	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(200.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<	EObjectTypeQuery> > BoxTraceTypes;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false;

	UPROPERTY()
	TArray<AKlotoStoneBase*> CollectedStones;
};
