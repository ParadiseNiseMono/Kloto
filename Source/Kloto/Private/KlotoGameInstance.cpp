// Paradise_NiseMono all rights reserved


#include "KlotoGameInstance.h"

TSoftObjectPtr<UWorld> UKlotoGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FKlotoGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag.MatchesTagExact(InTag))
		{
			return GameLevelSet.SoftLevelObject;
		}
	}
	return nullptr;
}
