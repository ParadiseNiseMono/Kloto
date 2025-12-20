// Paradise_NiseMono all rights reserved


#include "GameModes/KlotoSurvivalGameMode.h"

#include "KlotoDebugHelper.h"
#include "Characters/KlotoEnemyCharacter.h"
#include "Engine/AssetManager.h"

void AKlotoSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a data table in Survival GameMode"));

	SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
	PreLoadNextWaveEnemies();
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
				PreLoadNextWaveEnemies();
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
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AKlotoSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves()) return;

	for (const FKlotoEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerInfos)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([SpawnerInfo,this]()
			{
				if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
				{
					PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
					Debug::Print(LoadedEnemyClass->GetName() + TEXT("Is Loaded"));
				}
			}
			)
			);
	}
}

FKlotoEnemyWaveSpawnTableRow* AKlotoSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

	FKlotoEnemyWaveSpawnTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FKlotoEnemyWaveSpawnTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find data table row"));

	return FoundRow;
}
