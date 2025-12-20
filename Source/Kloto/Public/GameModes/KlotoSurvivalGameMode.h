// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameModes/KlotoBaseGameMode.h"
#include "KlotoSurvivalGameMode.generated.h"

class AKlotoEnemyCharacter;

UENUM(BlueprintType)
enum class EKlotoSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FKlotoEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AKlotoEnemyCharacter> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FKlotoEnemyWaveSpawnTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FKlotoEnemyWaveSpawnerInfo> EnemyWaveSpawnerInfos;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeChangedDelegate, EKlotoSurvivalGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoSurvivalGameMode : public AKlotoBaseGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvivalGameModeState(EKlotoSurvivalGameModeState InState);
	
	UPROPERTY()
	EKlotoSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeChangedDelegate OnSurvivalGameModeChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable*	EnemyWaveSpawnerDataTable;
};
