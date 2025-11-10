// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ABGA_Skill.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API UABGA_Skill : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UABGA_Skill();
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


protected:
// 몽타주 관련 콜백함수 2가지
	UFUNCTION()
	void OnCompleteCallback();
	UFUNCTION()
	void OnInterruptedCallback();

protected:
	//몽타주 관련 값 가져옴
	UPROPERTY()
	TObjectPtr<class UAnimMontage> ActiveSkillActionMontage;

};
