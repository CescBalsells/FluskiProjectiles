#pragma once

#include "CoreMinimal.h"
#include "Projectile/ExplosiveProjectile.h"

#include "GrenadeProjectile.generated.h"

class ABaseProjectileGizmo;
class USphereComponent;
class UFluskiProjectileMovementComponent;

UCLASS()
class FLUSKIPROJECTILES_API AGrenadeProjectile : public AExplosiveProjectile
{
	GENERATED_BODY()

public:
	/** Time to charge the max speed at which the grenade will be thrown*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float TimeToChargeSpeed = 2.0f;

	/** Curve that indicates the tick interval of the grenade before the explosion */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<UCurveFloat> TickCurveFloat;

	/** Time it takes the grenade to detonate */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float TimeToDetonate = 5.0f;

protected:
	float DetonationTimer = 0.0f;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void ThrowProjectile(const FVector Direction, const float Speed, USceneComponent* HomingTargetComponent) override;
};
