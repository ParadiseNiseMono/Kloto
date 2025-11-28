// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UKlotoEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class KLOTO_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKlotoEnemyGameplayAbility>> EnemyStartUpAbilitySets;
	
};
