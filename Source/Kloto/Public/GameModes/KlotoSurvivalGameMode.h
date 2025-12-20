// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameModes/KlotoBaseGameMode.h"
#include "KlotoSurvivalGameMode.generated.h"

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
};
