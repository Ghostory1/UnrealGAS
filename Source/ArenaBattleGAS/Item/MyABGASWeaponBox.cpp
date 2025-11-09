// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MyABGASWeaponBox.h"
#include "MyABGASWeaponBox.h"
#include "AbilitySystemBlueprintLibrary.h"

void AMyABGASWeaponBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WeaponEventTag, FGameplayEventData());
}
