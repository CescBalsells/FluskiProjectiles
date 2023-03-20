#include "Components/FluskiProjectileMovementComponent.h"


void UFluskiProjectileMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SavedGravityScale = ProjectileGravityScale;
	ProjectileGravityScale = 0.0f;
	Velocity = FVector::ZeroVector;
}

void UFluskiProjectileMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (bThrown == false)
		return;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsDistanceProjectile)
	{
		if (bDistanceReached == false && GetWorld()->GetTimeSeconds() > DistanceTimer)
		{
			bDistanceReached = true;
			OnProjectileDistanceReached.Broadcast();
		}
	}
}

void UFluskiProjectileMovementComponent::ThrowProjectile(const FVector Direction, const float ProjectileSpeed, USceneComponent* HomingTarget)
{
	bThrown = true;

	Velocity = Direction * ProjectileSpeed;

	// Reassign the gravity scale once the projecile has been thrown
	ProjectileGravityScale = SavedGravityScale;

	if (bIsDistanceProjectile)
	{
		// Calculates the time when the projectile will reach the distance
		DistanceTimer = GetWorld()->GetTimeSeconds() + MaxDistance / ProjectileSpeed;
	}

	if (bIsHomingProjectile && HomingTarget != nullptr)
	{
		HomingTargetComponent = HomingTarget;
	}
}

float UFluskiProjectileMovementComponent::UpdateChargedSpeed(const float ChargedValue)
{
	if (bIsChargedProjectile && SpeedChargeCurveFloat != nullptr)
	{
		ChargedSpeed = MinChargedSpeed + (SpeedChargeCurveFloat->GetFloatValue(ChargedValue) * (MaxChargedSpeed - MinChargedSpeed));
	}

	return ChargedSpeed;
}

FVector UFluskiProjectileMovementComponent::ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const
{
	if (HomingDistance <= 0.0f || (HomingTargetComponent->GetComponentLocation() - UpdatedComponent->GetComponentLocation()).SquaredLength() < (HomingDistance * HomingDistance))
	{
		return ((HomingTargetComponent->GetComponentLocation() - UpdatedComponent->GetComponentLocation()).GetSafeNormal() * HomingAccelerationMagnitude);
	}
	return FVector::ZeroVector;
}
