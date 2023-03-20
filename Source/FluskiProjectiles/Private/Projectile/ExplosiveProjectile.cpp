#include "Projectile/ExplosiveProjectile.h"

#include "Kismet/KismetSystemLibrary.h"

void AExplosiveProjectile::OnProjectileExplosion_Implementation()
{
	bProjectileExploded = true;
}

TArray<AActor*> AExplosiveProjectile::ProjectileExplosion()
{
	TArray<AActor*> HitActors;
	const TArray<AActor*> IgnoredActors{this};

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), ExplosionRadius, CollisionExplosionTypes, AActor::StaticClass(), IgnoredActors, HitActors);
	
	return HitActors;
}

float AExplosiveProjectile::GetDamage(const FVector GrenadeLocation, const FVector DamagedActorLocation) const
{
	if (DamageCurve != nullptr)
	{
		const float Distance = FVector::Distance(DamagedActorLocation, GrenadeLocation) / ExplosionRadius;
		return MinDamage + (DamageCurve->GetFloatValue(Distance) * (MaxDamage - MinDamage));
	}

	return 0.0f;
}
