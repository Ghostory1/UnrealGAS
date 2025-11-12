// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/ABGA_AttackHitCheck.h"
#include "ABGA_AttackHitCheck.h"
#include "ArenaBattleGAS.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GA/AT/ABAT_Trace.h"
#include "GA/TA/ABTA_Trace.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "ArenaBattleGAS.h"
#include "Tag/ABGameplayTags.h"

UABGA_AttackHitCheck::UABGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UABGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	ABGAS_LOG(LogABGAS, Log, TEXT("%s"), *TriggerEventData->EventTag.GetTagName().ToString());

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CurrentLevel = TriggerEventData->EventMagnitude;
	UABAT_Trace* AttackTraceTask = UABAT_Trace::CreateTask(this, TargetActorClass);
	AttackTraceTask->OnComplete.AddDynamic(this, &UABGA_AttackHitCheck::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();

}

void UABGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	// TargetDataHasHitResult -> 단일 타겟 트레이스
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		ABGAS_LOG(LogABGAS, Log, TEXT("Target %s Detected"),*(HitResult.GetActor()->GetName()));

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if (!SourceASC || !TargetASC)
		{
			ABGAS_LOG(LogABGAS, Error, TEXT("SourceASC , TargetASC Not Founded !!"));
			return;
		}
		////SourceAttribute 에서 값을 읽고
		////TargetAttribute의 값을 변경해야하니 const를 제거 해줘야함 -> const_cast
		////하지만 좋은 방법은 아님 const_cast 보다는 다음에 게임플레이 이펙트를 통해 바꿔주는것이 좋음
		const UABCharacterAttributeSet* SourceAttribute = SourceASC->GetSet<UABCharacterAttributeSet>();
		//UABCharacterAttributeSet* TargetAttribute = const_cast<UABCharacterAttributeSet*>(TargetASC->GetSet<UABCharacterAttributeSet>());
		//if (!SourceAttribute || !TargetAttribute)
		//{
		//	ABGAS_LOG(LogABGAS, Error, TEXT("SourceAttribute , TargetAttribute Not Founded !!"));
		//	return;
		//}

		//const float AttackDamage = SourceAttribute->GetAttackRate();
		//TargetAttribute->SetHealth(TargetAttribute->GetHealth() - AttackDamage);

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect,CurrentLevel);
		if (EffectSpecHandle.IsValid())
		{
			//Set-by-Caller 방식
			//EffectSpecHandle.Data->SetSetByCallerMagnitude(ABGameplayTags::Data_Damage, -(SourceAttribute->GetAttackRate()));
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,EffectSpecHandle,TargetDataHandle);

			FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
			CueContextHandle.AddHitResult(HitResult);
			FGameplayCueParameters CueParam;
			CueParam.EffectContext = CueContextHandle;

			TargetASC->ExecuteGameplayCue(ABGameplayTags::GameplayCue_Character_AttackHit, CueParam);
		}

		FGameplayEffectSpecHandle BuffEffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackBuffEffect);
		if (BuffEffectSpecHandle.IsValid())
		{
			// 자기 자신에게 버프를 거는거기때문에 마지막인자에 타겟정보는 안넣어도 됌
			ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, BuffEffectSpecHandle);
		}
	}
	// 멀티 타겟 트레이스
	else if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle,0))
	{
		// TargetDataHasActor는 Actors 정보가 있는지 확인하는 함수 -> 여러개의 액터들이 있는지
		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect, CurrentLevel);
		if (EffectSpecHandle.IsValid())
		{
			//Set-by-Caller 방식
			//EffectSpecHandle.Data->SetSetByCallerMagnitude(ABGameplayTags::Data_Damage, -(SourceAttribute->GetAttackRate()));
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

			FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
			CueContextHandle.AddActors(TargetDataHandle.Data[0].Get()->GetActors(),false);
			FGameplayCueParameters CueParam;
			CueParam.EffectContext = CueContextHandle;

			SourceASC->ExecuteGameplayCue(ABGameplayTags::GameplayCue_Character_AttackHit, CueParam);
		}
	}
	bool bReplicatiedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatiedEndAbility, bWasCancelled);
}
