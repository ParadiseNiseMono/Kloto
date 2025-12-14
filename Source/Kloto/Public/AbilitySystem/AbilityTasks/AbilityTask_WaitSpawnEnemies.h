// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

class AKlotoEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AKlotoEnemyCharacter*>&, SpawnedEnemies);

/**
 * 
 */
UCLASS()
class KLOTO_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Kloto|AbilityTasks", meta=(DisplayName = "Wait Gameplay Event And Spawn Enemies"
		, HidePin = OwingAbility, DefaultToSelf = OwingAbility, BlueprintInternalUseOnly = "true", NumToSpawn = "1", RandomSpawnRadius = "200"))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* OwingAbility,
		FGameplayTag EventTag,
		TSoftClassPtr<AKlotoEnemyCharacter> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnLocation,
		float RandomSpawnRadius,
		const FRotator& SpawnRotation);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

//~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
//~ End UGameplayTask Interface

private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<AKlotoEnemyCharacter> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	float CachedRandomSpawnRadius;
	FVector CachedSpawnLocation;
	FRotator CachedSpawnRotation;
	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayLoad);
	void OnEnemyClassLoaded();
};
