// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace ABGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_Action_Rotate);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_Action_AttackHitCheck);

	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_State_IsDead);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_State_IsInvinsible);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_State_IsRotating);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_State_IsAttacking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Actor_State_IsJumping);

	//GE GameplayTag
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Damage);

	// GameplayCue
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Character_AttackHit);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Chest_Open);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Character_Damage);

	//Event
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_Weapon_Equip);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_Weapon_Unequip);

}