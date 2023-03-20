#include "Projectile/GrenadeProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/FluskiProjectileMovementComponent.h"

void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Sets the detonation timer when we spawn the grenade 
	DetonationTimer = GetWorld()->GetTimeSeconds() + TimeToDetonate;
}

void AGrenadeProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bProjectileExploded == false && GetWorld()->GetTimeSeconds() > DetonationTimer)
    {
		OnProjectileExplosion();
    }
    else
    {
    	// Updates the grenade material so it matches with the tick interval and the user gets feedback
    	if (TickCurveFloat != nullptr)
    		MeshComponent->SetCustomPrimitiveDataFloat(0, TickCurveFloat->GetFloatValue(FMath::Min(GetGameTimeSinceCreation() / TimeToDetonate,1.0f)));
    }
}

void AGrenadeProjectile::ThrowProjectile(const FVector Direction, const float Speed, USceneComponent* HomingTargetComponent)
{
	Super::ThrowProjectile(Direction, Speed, HomingTargetComponent);
	
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
}

