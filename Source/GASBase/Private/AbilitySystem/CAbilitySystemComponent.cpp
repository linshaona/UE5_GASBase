// Make by linshao


#include "AbilitySystem/CAbilitySystemComponent.h"

#include "GameplayTags/CTags.h"


// Sets default values for this component's properties
UCAbilitySystemComponent::UCAbilitySystemComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UCAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	HandleAutoActivatedAbility(AbilitySpec);
}

void UCAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const auto&AbilitySpec:GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

void UCAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;
	
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	
	if (AbilitySpec)
	{
		AbilitySpec->Level = Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UCAbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;
	
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	
	if (AbilitySpec)
	{
		AbilitySpec->Level += Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UCAbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;
	
	for (const FGameplayTag Tag:AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(CTags::CAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;  
		}
	}
}


