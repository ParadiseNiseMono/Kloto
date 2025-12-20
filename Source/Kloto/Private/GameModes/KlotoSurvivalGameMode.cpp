// Paradise_NiseMono all rights reserved


#include "GameModes/KlotoSurvivalGameMode.h"

#include "KlotoDebugHelper.h"
#include "NavigationSystem.h"
#include "Characters/KlotoEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

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
		if (TimePassSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
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

	PreLoadedEnemyClassMap.Empty();

	for (const FKlotoEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerInfos)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([SpawnerInfo,this]()
			{
				if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
				{
					PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
				}
			}
			)
			);
	}
}

int32 AKlotoSurvivalGameMode::TrySpawnWaveEnemies()
{
	if (SpawnTargetPoints.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), SpawnTargetPoints);
	}

	//checkf(!SpawnTargetPoints.IsEmpty(), TEXT("No valid target point to spawn enemies in %s Level"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FKlotoEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerInfos)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (int i = 0; i < NumToSpawn; ++i)
		{
			const int32 RandomTargetPointToSpawn = FMath::RandRange(0, SpawnTargetPoints.Num() - 1);
			const FVector SpawnLocation = SpawnTargetPoints[RandomTargetPointToSpawn]->GetActorLocation();
			const FRotator SpawnRotation = SpawnTargetPoints[RandomTargetPointToSpawn]->GetActorForwardVector().ToOrientationRotator();

			FVector RandomSpawnLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), SpawnLocation, RandomSpawnLocation, 500.f);

			RandomSpawnLocation += FVector(0.f, 0.f, 150.f);

			AKlotoEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AKlotoEnemyCharacter>(LoadedClass, RandomSpawnLocation, SpawnRotation, SpawnParameters);

			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
				
				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawnEnemies()) return EnemiesSpawnedThisTime;
		}
	}
	return EnemiesSpawnedThisTime;
}

bool AKlotoSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AKlotoSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;
	
	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;

		SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState::WaveCompleted);
	}
}

FKlotoEnemyWaveSpawnTableRow* AKlotoSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

	FKlotoEnemyWaveSpawnTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FKlotoEnemyWaveSpawnTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find data table row"));

	
	return FoundRow;
}

void AKlotoSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AKlotoEnemyCharacter*>& InEnemiesToRegister)
{
	for (AKlotoEnemyCharacter* SpawnedEnemy : InEnemiesToRegister)
	{
		if (SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;
			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}
	}
}
