// Make by linshao


#include "AbilitySystem/Abilities/CGameplayAbility.h"

void UCGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	
	if (bDrawDebug && IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f, FColor::Green,FString::Printf(TEXT("%s Activated"),*GetName()));
	}
}
