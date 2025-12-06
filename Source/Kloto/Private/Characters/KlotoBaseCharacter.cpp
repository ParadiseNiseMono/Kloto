// Paradise_NiseMono all rights reserved


#include "Characters/KlotoBaseCharacter.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystem/KlotoAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
AKlotoBaseCharacter::AKlotoBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	KlotoAbilitySystemComponent = CreateDefaultSubobject<UKlotoAbilitySystemComponent>("KlotoAbilitySystemComponent");

	KlotoAttributeSet = CreateDefaultSubobject<UKlotoAttributeSet>("KlotoAttributeSet");

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}

UAbilitySystemComponent* AKlotoBaseCharacter::GetAbilitySystemComponent() const
{
	return GetKlotoAbilitySystemComponent();
}

UPawnCombatComponent* AKlotoBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AKlotoBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AKlotoBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (KlotoAbilitySystemComponent)
	{
		KlotoAbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}



