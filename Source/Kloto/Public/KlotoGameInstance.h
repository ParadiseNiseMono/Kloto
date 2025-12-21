// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "KlotoGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FKlotoGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> SoftLevelObject;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !SoftLevelObject.IsNull();
	}
};

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FKlotoGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

	
};
