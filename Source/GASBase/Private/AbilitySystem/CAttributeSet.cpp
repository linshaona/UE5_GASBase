// Make by linshao


#include "AbilitySystem/CAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UCAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass,Mano,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass,MaxMano,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME(ThisClass,bAttributesInitialized);
}

void UCAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributeSetInitialized.Broadcast();
	}
	
}

void UCAttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized)
	{
		OnAttributeSetInitialized.Broadcast();
	}
}

void UCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Health,OldValue);
}

void UCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxHealth,OldValue);
}

void UCAttributeSet::OnRep_Mano(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,Mano,OldValue);
}

void UCAttributeSet::OnRep_MaxMano(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass,MaxMano,OldValue);
}

