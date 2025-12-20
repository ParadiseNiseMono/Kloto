// Paradise_NiseMono all rights reserved


#include "GameModes/KlotoSurvivalGameMode.h"

void AKlotoSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a data table in Survival GameMode"));

	SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
}

void AKlotoSurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSurvivalGameModeState == EKlotoSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassSinceStart += DeltaTime;
		if (TimePassSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvivalGameModeState == EKlotoSurvivalGameModeState::SpawningNewWave)
	{
		TimePassSinceStart += DeltaTime;
		if (TimePassSinceStart >= SpawnNewWaveWaitTime)
		{
			//Handle Spawn New Enemies
			TimePassSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::InProgress);
		}
	}

	if (CurrentSurvivalGameModeState == EKlotoSurvivalGameModeState::WaveCompleted)
	{
		TimePassSinceStart += DeltaTime;
		if (TimePassSinceStart >= WaveCompletedWaitTime)
		{
			TimePassSinceStart = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::WaitSpawnNewWave);
			}
		}
	}
}

void AKlotoSurvivalGameMode::SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;

	OnSurvivalGameModeChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool AKlotoSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount >= TotalWavesToSpawn;
}
