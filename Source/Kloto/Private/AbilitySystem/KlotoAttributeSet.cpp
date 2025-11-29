// Paradise_NiseMono all rights reserved


#include "AbilitySystem/KlotoAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "KlotoDebugHelper.h"

UKlotoAttributeSet::UKlotoAttributeSet()
{
	/*InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);*/
}

void UKlotoAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewHealth);
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f,GetMaxRage());

		SetCurrentRage(NewRage);
	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - Damage, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("OldHealth: %f, Damage: %f, NewCurrentHealth: %f"), OldHealth, Damage, NewCurrentHealth);
		
		Debug::Print(DebugString);

		//TODO: Notify the UI

		//TODO: Handle character death
		if (NewCurrentHealth == 0.f)
		{
			
		}
	}
}
