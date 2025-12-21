// Paradise_NiseMono all rights reserved


#include "KlotoGameInstance.h"

#include "MoviePlayer.h"

void UKlotoGameInstance::Init()
{
	Super::Init();
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);
}

void UKlotoGameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;

	LoadingScreenAttributes.MoviePaths.Add(TEXT("LoadVideo"));

	LoadingScreenAttributes.bAllowEngineTick = false;
	LoadingScreenAttributes.bWaitForManualStop = false;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 7.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UKlotoGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

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
