#include "Projectile/BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseProjectile::ABaseProjectile(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (CollisionComponent != nullptr)
	{
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
		CollisionComponent->SetNotifyRigidBodyCollision(false);
		CollisionComponent->SetSimulatePhysics(false);
		CollisionComponent->InitSphereRadius(9.0f);
		RootComponent = CollisionComponent;
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (MeshComponent != nullptr)
	{
		MeshComponent->SetCollisionProfileName("NoCollision");
		MeshComponent->SetupAttachment(RootComponent);
	}

	ProjectileMovement = CreateDefaultSubobject<UFluskiProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	if (ProjectileMovement != nullptr)
	{
		ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	}

	AActor::SetLifeSpan(0.0f);
}

void ABaseProjectile::ThrowProjectile(const FVector Direction, const float Speed, USceneComponent* HomingTargetComponent)
{
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

	ProjectileMovement->ThrowProjectile(Direction, Speed, HomingTargetComponent);
}

ABaseProjectile* ABaseProjectile::SpawnProjectile(const AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FVector Location, FRotator Rotation)
{
	if (ProjectileOwner != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABaseProjectile* Projectile = ProjectileOwner->GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, Location, Rotation, ActorSpawnParams);

		return Projectile;
	}

	return nullptr;
}

ABaseProjectile* ABaseProjectile::SpawnAttachedProjectile(AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FName SocketName, USkeletalMeshComponent* Mesh)
{
	if (ProjectileOwner != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FRotator Rotation = ProjectileOwner->GetActorRotation();

		ABaseProjectile* Projectile = ProjectileOwner->GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, Mesh->GetSocketLocation(SocketName), Rotation, ActorSpawnParams);

		if (Projectile != nullptr)
		{
			const FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			Projectile->AttachToComponent(Mesh, AttachRules, SocketName);
		}

		return Projectile;
	}

	return nullptr;
}

ABaseProjectile* ABaseProjectile::SpawnAndThrowProjectile(const AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FVector StartLocation, FVector EndLocation, float Speed, USceneComponent* HomingTargetComponent)
{
	if (ProjectileOwner != nullptr)
	{
		const FVector Direction = (EndLocation - StartLocation).GetSafeNormal();

		ABaseProjectile* Projectile = SpawnProjectile(ProjectileOwner, ProjectileClass, StartLocation, Direction.Rotation());

		if (Projectile != nullptr)
		{

			Projectile->ProjectileMovement->ThrowProjectile(Direction, Speed, HomingTargetComponent);
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTargetComponent;
		}

		return Projectile;
	}

	return nullptr;
}
