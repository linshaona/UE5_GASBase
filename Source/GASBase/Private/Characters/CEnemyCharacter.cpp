// Make by linshao


#include "Characters/CEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAbilitySystemComponent.h"


// Sets default values
ACEnemyCharacter::ACEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

}

UAbilitySystemComponent* ACEnemyCharacter::GetAbilitySystemComponent() const
{
	
	
	return AbilitySystemComponent;
}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(AbilitySystemComponent))return ;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	
}


