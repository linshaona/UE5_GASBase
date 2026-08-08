// Make by linshao


#include "GameObjects/CProjectile.h"

#include "Characters/CPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "GameplayTags/CTags.h"

ACProjectile::ACProjectile()
{
	
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);
	
	ParticlePlace = CreateDefaultSubobject<UNiagaraComponent>("ParticlePlace");
	ParticlePlace->SetupAttachment(RootComponent);
	

	
	bReplicates = true;
}

void ACProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	ACPlayerCharacter* PlayerCharacter = Cast<ACPlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->GetAlive()) return;      
	
	
	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)||!HasAuthority()) return;
	
	FGameplayEffectContextHandle ContextHandle  = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect,1.0f,ContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,CTags::SetByCaller::Projectile,Damage);
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	SpawnImpactEffect();
	Destroy();
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ParticlePlace->Activate();
}




