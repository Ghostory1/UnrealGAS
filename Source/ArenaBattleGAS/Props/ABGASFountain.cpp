// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ABGASFountain.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ArenaBattleGAS.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Tag/ABGameplayTags.h"
#include "Abilities/GameplayAbility.h"
//#include "GA/ABGA_Rotate.h"

AABGASFountain::AABGASFountain()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateMovement"));
	ActionPeriod = 3.0f;
}

UAbilitySystemComponent* AABGASFountain::GetAbilitySystemComponent() const
{
	return ASC;
}

void AABGASFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RotatingMovement->bAutoActivate = false;
	RotatingMovement->Deactivate();

	ASC->InitAbilityActorInfo(this,this);
	
	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec RotateSkillSpec(StartAbility);
		ASC->GiveAbility(RotateSkillSpec);
	}
}

void AABGASFountain::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ActionTimer, this, &AABGASFountain::TimerAction, ActionPeriod, true, 0.0f);
}

void AABGASFountain::TimerAction()
{
	ABGAS_LOG(LogABGAS, Log, TEXT("Begin"));

	FGameplayTagContainer TargetTag;
	TargetTag.AddTag(ABGameplayTags::Actor_Action_Rotate);

	if (!ASC->HasMatchingGameplayTag(ABGameplayTags::Actor_State_IsRotating))
	{
		// ABGA_Rotate 에서 어빌리티가 발동되면 심어지는 태그를 검사해서 굳이 따로 GA를 검사하지않아도 
		// 발동되면 심어지는 태그를 검사하면서 발동되는것을 체크
		ASC->TryActivateAbilitiesByTag(TargetTag);
	}
	else
	{
		ASC->CancelAbilities(&TargetTag);
	}


	/*FGameplayAbilitySpec* RotateGASpec = ASC->FindAbilitySpecFromClass(UABGA_Rotate::StaticClass());
	if (!RotateGASpec)
	{
		ABGAS_LOG(LogABGAS, Log, TEXT("No Rotate Spec Found!"));
		return;
	}

	if (!RotateGASpec->IsActive())
	{
		ASC->TryActivateAbility(RotateGASpec->Handle);
	}
	else
	{
		ASC->CancelAbilityHandle(RotateGASpec->Handle);
	}*/

	/*if (!RotatingMovement->IsActive())
	{
		RotatingMovement->Activate(true);
	}
	else
	{
		RotatingMovement->Deactivate();
	}*/
}
