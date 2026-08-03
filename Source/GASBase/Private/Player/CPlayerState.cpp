// Make by linshao


#include "GASBase/Public/Player/CPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAbilitySystemComponent.h"

ACPlayerState::ACPlayerState()
{
	SetNetUpdateFrequency(100.0f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent -> SetIsReplicated(true);
	
	//客户端的表现形式设置
	AbilitySystemComponent -> SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

