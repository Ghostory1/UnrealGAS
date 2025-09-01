// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/AT/ABAT_JumpAndWaitForLanding.h"
#include "ABAT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"
#include "ABAT_Trace.h"

UABAT_JumpAndWaitForLanding::UABAT_JumpAndWaitForLanding()
{

}



UABAT_JumpAndWaitForLanding* UABAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UABAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UABAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}


void UABAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &UABAT_JumpAndWaitForLanding::OnLandedCallback);
	Character->Jump();

	//점프가 언제 끝날지 모름 ( 높이에 따라 점프가 다르니까)
	// SetWaitingOnAvatar 함수 호출로 AT의 상태를 Waiting 으로 바꿔줌
	SetWaitingOnAvatar();

	// ACharacter 에서 착지한것을 알려주는 delegate가 있음 -> LandedDelegate
}

void UABAT_JumpAndWaitForLanding::OnDestroy(bool AbilityEnded)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &UABAT_JumpAndWaitForLanding::OnLandedCallback);
	Super::OnDestroy(AbilityEnded);
}

void UABAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& Hit)
{
	// 알려줄지 안알려줄지 설정 가능 -> ShouldBroadcastAbilityTaskDelegates
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast();
	}
}