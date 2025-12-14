// Paradise_NiseMono all rights reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwingAbility,
	FGameplayTag EventTag, TSoftObjectPtr<AKlotoEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn,
	const FVector& SpawnLocation, float RandomSpawnRadius, const FRotator& SpawnRotation)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwingAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedSpawnLocation = SpawnLocation;
	Node->CachedSpawnRotation = SpawnRotation;

	return Node;
}
