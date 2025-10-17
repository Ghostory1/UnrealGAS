// Fill out your copyright notice in the Description page of Project Settings.


#include "Tag/ABGameplayTags.h"

namespace ABGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Actor_Action_Rotate, "Actor.Action.Rotate");
	UE_DEFINE_GAMEPLAY_TAG(Actor_Action_AttackHitCheck, "Actor.Action.AttackHitCheck");

	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsRotating, "Actor.State.IsRotating");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsAttacking, "Actor.State.IsAttacking");
	UE_DEFINE_GAMEPLAY_TAG(Actor_State_IsJumping, "Actor.State.IsJumping");

	UE_DEFINE_GAMEPLAY_TAG(Data_Damage, "Data.Damage");
}