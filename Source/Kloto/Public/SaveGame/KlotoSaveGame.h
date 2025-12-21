// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "KlotoTypes/KlotoEnumTypes.h"
#include "KlotoSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EKlotoGameDifficulty SavedCurrentGameDifficulty;
};
