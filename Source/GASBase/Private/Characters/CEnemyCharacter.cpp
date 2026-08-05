// Make by linshao


#include "Characters/CEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAbilitySystemComponent.h"
#include "AbilitySystem/C_AttributeSet.h"


// Sets default values
ACEnemyCharacter::ACEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UC_AttributeSet>("AttributeSet");
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


