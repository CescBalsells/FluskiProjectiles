#pragma once
#include "BaseProjectile.h"

#include "ExplosiveProjectile.generated.h"

UCLASS()
class FLUSKIPROJECTILES_API AExplosiveProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	/** Radius of the epxlosion */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float ExplosionRadius = 200.0f;

	/** Min damage the grenade depending on the distance of the actor from the center of the grenade */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float MinDamage = 0;

	/** Max damage the grenade depending on the distance of the actor from the center of the grenade */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float MaxDamage = 0.0f;

	/** Damage indicator that goes from 1 to 0 and indicates the amount of damage received depending on the distance and the min max values */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<UCurveFloat> DamageCurve = nullptr;

	/** Objects that can overlap with the explosion */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionExplosionTypes;

	/** Event called when the projectile explodes */
	UFUNCTION(BlueprintNativeEvent, Category=FluskiProjectile)
	void OnProjectileExplosion();

public:
	/** Event called when the grenade explodes */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	TArray<AActor*> ProjectileExplosion();

	/** Returns the explosion damage depending on how far the damaged actor is from the explosion center */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	float GetDamage(const FVector GrenadeLocation, const FVector DamagedActorLocation) const;
};
