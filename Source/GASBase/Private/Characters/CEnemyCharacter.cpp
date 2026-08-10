// Make by linshao


#include "Characters/CEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/CAbilitySystemComponent.h"
#include "AbilitySystem/CAttributeSet.h"
#include "GameplayTags/CTags.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/AIModule/Classes/AIController.h"


void ACEnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,bIsBeingLaunched);
}

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

void ACEnemyCharacter::StopMovingUntilLanding()
{
	bIsBeingLaunched = true;
	AAIController* AIController = Cast<AAIController>(GetOwner());
	if (!IsValid(AIController)) return;
	
	AIController->StopMovement();
	if (!LandedDelegate.IsAlreadyBound(this,&ThisClass::EnableMovementOnLanded))
	{
		LandedDelegate.AddDynamic(this,&ThisClass::EnableMovementOnLanded);
	}
}

void ACEnemyCharacter::EnableMovementOnLanded(const FHitResult& Hit)
{
	bIsBeingLaunched = false;
	//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,CTags::Events::Enemy::EndAttack);
	//AAIController* AIController = Cast<AAIController>(GetOwner());
	//AIController->StopMovement();
	LandedDelegate.RemoveDynamic(this,&ThisClass::EnableMovementOnLanded);
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

void ACEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* AIController = Cast<AAIController>(GetOwner());
	if (!IsValid(AIController)) return;
	
	AIController->StopMovement();
}



