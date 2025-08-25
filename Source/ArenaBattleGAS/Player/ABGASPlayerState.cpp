// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABGASPlayerState.h"
#include "AbilitySystemComponent.h"
AABGASPlayerState::AABGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* AABGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
