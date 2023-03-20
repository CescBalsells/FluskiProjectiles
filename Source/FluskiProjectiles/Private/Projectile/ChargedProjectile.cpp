#include "Projectile/ChargedProjectile.h"

void AChargedProjectile::UpdateChargedValue(const float ChargeValue)
{
	ChargedValue = FMath::Clamp(ChargeValue, 0, 1);
}

float AChargedProjectile::GetDamage(float ChargeValue) const
{
	if (DamageCurve != nullptr)
	{
		return MinDamage + (DamageCurve->GetFloatValue(ChargedValue) * (MaxDamage - MinDamage));
	}

	return 0.0f;
}
