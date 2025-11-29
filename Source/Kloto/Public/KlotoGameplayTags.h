// Paradise_NiseMono all rights reserved

#pragma once

#include "NativeGameplayTags.h"

namespace KlotoGameplayTags
{
	/*Input tags*/
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);
	
	/*Player Tags*/
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	/*Enemy Tags*/
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	/*Shared Tags*/
	KLOTO_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
}
