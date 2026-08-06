// Make by linshao


#include "GASBase/Public/Characters/CBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "DataWrappers/ChaosVDParticleDataWrapper.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ACBaseCharacter::ACBaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;
	
	//更新和刷新骨骼变化
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	
}

void ACBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,bAlive);
}

UAbilitySystemComponent* ACBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}


void ACBaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability:StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ACBaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect),TEXT("InitializeAttributesEffect is not valid!"));
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect,1.0f,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ACBaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.0f)
	{
		HandleDeath();
	}
}

void ACBaseCharacter::HandleDeath()
{
	bAlive = false;
}
void ACBaseCharacter::HandleRespawn()
{
	bAlive=true;
}
