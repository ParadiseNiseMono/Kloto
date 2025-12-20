// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KlotoTypes/KlotoEnumTypes.h"
#include "KlotoBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AKlotoBaseGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameSettings")
	EKlotoGameDifficulty CurrentGameplayDifficulty;

public:
	FORCEINLINE EKlotoGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameplayDifficulty; }
};
