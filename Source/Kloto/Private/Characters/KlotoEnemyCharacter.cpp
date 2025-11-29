// Paradise_NiseMono all rights reserved


#include "Characters/KlotoEnemyCharacter.h"

#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "KlotoDebugHelper.h"

AKlotoEnemyCharacter::AKlotoEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
}

void AKlotoEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

UPawnCombatComponent* AKlotoEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

void AKlotoEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
		{
			LoadedData->GiveToAbilitySystemComponent(KlotoAbilitySystemComponent);

			Debug::Print(TEXT("Enemy Start"));
		}
	}));
}
