// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CProjectile.generated.h"

UCLASS()
class GASBASE_API ACProjectile : public AActor
{
	GENERATED_BODY()

public:

	ACProjectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|Damage",meta =(ExposeOnSpawn,ClampMin = "0.0"))
	float Damage{-10.0f};
	
	UFUNCTION(BlueprintImplementableEvent,Category="GASBase|Projectile")
	void SpawnImpactEffect();
private:
	UPROPERTY(VisibleAnywhere,Category="GASBase|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditAnywhere,Category="GASBase|Projectile")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(VisibleAnywhere,Category="GASBase|Projectile")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere,Category="GASBase|Projectile")
	TObjectPtr<UNiagaraComponent> ParticlePlace;
	
	UPROPERTY(EditAnywhere,Category="GASBase|Projectile")
	TObjectPtr<UNiagaraSystem> ShootingParticle;
	
	
protected:
	
	void BeginPlay() override;
};
