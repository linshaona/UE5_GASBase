// Make by linshao


#include "Characters/CEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAbilitySystemComponent.h"
#include "AbilitySystem/CAttributeSet.h"


// Sets default values
ACEnemyCharacter::ACEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UCAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ACEnemyCharacter::GetAbilitySystemComponent() const
{
	
	
	return AbilitySystemComponent;
}

UAttributeSet* ACEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(AbilitySystemComponent))return ;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	InitializeAttributes();  
	
	UCAttributeSet* CAttributeSet = Cast<UCAttributeSet>(GetAttributeSet());
	if (!IsValid(CAttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(CAttributeSet->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHealthChanged);
}


