#pragma once
#include "GameFramework/ProjectileMovementComponent.h"

#include "FluskiProjectileMovementComponent.generated.h"

UCLASS(ClassGroup=Movement, meta=(BlueprintSpawnableComponent), ShowCategories=(Velocity))
class FLUSKIPROJECTILES_API UFluskiProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileDistanceReachedDelegate)

public:
	/** If the projectile is charged, the projectile speed used to throw it will be the Charged Speed and not the Initial Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Charged)
	uint8 bIsChargedProjectile:1;

	/** Curve that indicates the min and max speed at which the projectile can be thrown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Charged, meta=(EditCondition="bIsChargedProjectile"))
	TObjectPtr<UCurveFloat> SpeedChargeCurveFloat;

	/** Min speed the projectile can reach without being charged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Charged, meta=(EditCondition="bIsChargedProjectile"))
	float MinChargedSpeed;

	/** Max speed the projectile can reach being full charged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Charged, meta=(EditCondition="bIsChargedProjectile"))
	float MaxChargedSpeed;

	/** At this distance from the target the projectile will start applying homing acceleration. If HomingDistance <= 0 it will apply homing from the beginning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Homing, meta=(EditCondition="bIsHomingProjectile"))
	float HomingDistance;

	/** If it's a distance projectile, the projectile will broadcast the event OnProjectileDistanceReached once the MaxDistance has been reached */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Distance)
	uint8 bIsDistanceProjectile:1;

	/** Max distance that projectile can reach */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Distance, meta=(EditCondition="bIsDistanceProjectile"))
	float MaxDistance;

	/**
	 * If the projectile is a bIsDistanceProjectile it will broadcast this event once the Max distance is reached
	 * @see bIsDistanceProjectile
	 */
	UPROPERTY(BlueprintAssignable)
	FOnProjectileDistanceReachedDelegate OnProjectileDistanceReached;

protected:
	bool bThrown;
	bool bDistanceReached;

	float ChargedSpeed;
	float DistanceTimer;
	float SavedGravityScale;

public:
	UFluskiProjectileMovementComponent() = default;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Throws the projectile at given direction and Speed */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual void ThrowProjectile(const FVector Direction, const float ProjectileSpeed, USceneComponent* HomingTarget = nullptr);

	/** Returns true if the projectile has been thrown */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	bool IsThrown() const { return bThrown; }

	/**
	 *	Set the charged speed depending on the ChargedValue
	 * @param ChargedValue: Value that goes from 0-1, depending on how charged is the projectile
	 */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	float UpdateChargedSpeed(const float ChargedValue);

	/** Returns the Speed depending if it's chargedProjectile or not */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	float GetProjectileSpeed() const { return bIsChargedProjectile ? ChargedSpeed : InitialSpeed; };

	/** Returns the gravity scale depending on the projectile state */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	float GetGravityScale() const { return bThrown ? ProjectileGravityScale : SavedGravityScale; };

	virtual FVector ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const override;
};
