// Paradise_NiseMono all rights reserved


#include "AbilitySystem/KlotoAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "KlotoDebugHelper.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/RobotUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

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
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't Implement PawnUIInterface"), *GetNameSafe(Data.Target.GetAvatarActor()));
	
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't Get a UPawnUIComponent from %s"), *GetNameSafe(Data.Target.GetAvatarActor()));
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f,GetMaxRage());

		SetCurrentRage(NewRage);

		if (URobotUIComponent* RobotUIComponent = CachedPawnUIInterface->GetRobotUIComponent())
		{
			RobotUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - Damage, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("OldHealth: %f, Damage: %f, NewCurrentHealth: %f"), OldHealth, Damage, NewCurrentHealth);
		
		Debug::Print(DebugString);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		
		if (GetCurrentHealth() == 0.f)
		{
			UKlotoFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), KlotoGameplayTags::Shared_Status_Dead);
		}
	}
}
