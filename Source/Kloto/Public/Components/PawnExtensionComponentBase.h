// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KLOTO_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'GetOwningPawn' must be a TClass of 'APawn'");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'GetOwningController' must be a TClass of 'AController'");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
		
};
