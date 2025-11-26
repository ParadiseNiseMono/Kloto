// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "KlotoBaseCharacter.generated.h"

class UKlotoAttributeSet;
class UKlotoAbilitySystemComponent;

UCLASS()
class KLOTO_API AKlotoBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKlotoBaseCharacter();
	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface
protected:

	//~ Begin APawn	Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UKlotoAbilitySystemComponent* KlotoAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UKlotoAttributeSet* KlotoAttributeSet;

public:
	FORCEINLINE UKlotoAbilitySystemComponent* GetKlotoAbilitySystemComponent() const { return KlotoAbilitySystemComponent; }

	FORCEINLINE UKlotoAttributeSet* GetKlotoAttributeSet() const { return KlotoAttributeSet; }
};
