// Fill out your copyright notice in the Description page of Project Settings.


#include "Tag/ABGameplayTags.h"

namespace ABGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Actor_Action_Rotate, "Actor.Action.Rotate");

	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsDead, "Actor.State.IsDead");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsInvinsible, "Actor.State.IsInvinsible");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsRotating, "Actor.State.IsRotating");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsAttacking, "Actor.State.IsAttacking");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsJumping, "Actor.State.IsJumping");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsSkilling, "Actor.State.IsSkilling");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_Cooldown, "Actor.State.Cooldown");

	UE_DEFINE_GAMEPLAY_TAG(Data_Damage, "Data.Damage");

	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Character_AttackHit, "GameplayCue.Character.AttackHit");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Chest_Open, "GameplayCue.Chest.Open");
	UE_DEFINE_GAMEPLAY_TAG(GameplayCue_Character_Damage, "GameplayCue.Character.Damage");

	UE_DEFINE_GAMEPLAY_TAG(Event_Character_Weapon_Equip, "Event.Character.Weapon.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Event_Character_Weapon_Unequip, "Event.Character.Weapon.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(Event_Actor_Action_AttackHitCheck, "Event.Actor.Action.AttackHitCheck");
	UE_DEFINE_GAMEPLAY_TAG(Event_Actor_Action_SkillHitCheck, "Event.Actor.Action.SkillHitCheck");
}