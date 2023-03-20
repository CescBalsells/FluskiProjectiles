#pragma once
#include "BaseProjectile.h"

#include "DamageProjectile.generated.h"

UCLASS()
class FLUSKIPROJECTILES_API ADamageProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	/** Damage of the projectile */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	float Damage = 0.0f;

public:
	/** Returns the damage of the projectile */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual float GetDamage() const { return Damage; }
};
