#pragma once
#include "BaseProjectile.h"

#include "ChargedProjectile.generated.h"

UCLASS()
class FLUSKIPROJECTILES_API AChargedProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	/** Min damage depending on how charged is the projectile */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FluskiProjectile)
	float MinDamage;

	/** Max damage depending on how charged is the projectile */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FluskiProjectile)
	float MaxDamage;

	/** Damage indicator that goes from 1 to 0 and indicates the amount of damage received depending on the charged value */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FluskiProjectile)
	TObjectPtr<UCurveFloat> DamageCurve = nullptr;

	UPROPERTY(BlueprintReadWrite, Category=FluskiProjectile)
	float ChargedValue;
	
public:
	
	/** Updates the charged value */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual void UpdateChargedValue(const float ChargeValue);

	/** Returns the damage that should deal the projectile depending on how charged it is*/
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual float GetDamage(float ChargeValue) const;
};
