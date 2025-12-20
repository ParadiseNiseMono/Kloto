// Paradise_NiseMono all rights reserved


#include "GameModes/KlotoSurvivalGameMode.h"

void AKlotoSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKlotoSurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AKlotoSurvivalGameMode::SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;

	OnSurvivalGameModeChanged.Broadcast(CurrentSurvivalGameModeState);
}
