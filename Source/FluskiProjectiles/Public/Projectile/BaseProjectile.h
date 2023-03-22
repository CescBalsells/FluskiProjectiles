#pragma once
#include "Components/FluskiProjectileMovementComponent.h"

#include "BaseProjectile.generated.h"

class USphereComponent;
class ABaseProjectileGizmo;
class UProjectileMovementComponent;

UCLASS()
class FLUSKIPROJECTILES_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FluskiProjectile)
	UFluskiProjectileMovementComponent* ProjectileMovement;

public:
	ABaseProjectile(const FObjectInitializer& ObjectInitializer);

	/** Returns true if the projectile has been thrown */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual bool IsThrown() const { return ProjectileMovement->IsThrown(); };

	/** Throws the projectile to the given direction with the desired speed and HomingTarget if needed */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	virtual void ThrowProjectile(const FVector Direction, const float Speed, USceneComponent* HomingTargetComponent = nullptr);
	
	/** Spawns the projectile and returns the projectile spawned */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	static ABaseProjectile* SpawnProjectile(const AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FVector Location, FRotator Rotation);

	/** Spawns the projectile attached to the given socket and returns the projectile spawned */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	static ABaseProjectile* SpawnAttachedProjectile(AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FName SocketName, USkeletalMeshComponent* Mesh);

	/** Spawns the projectile and throws the projectile returning the projectile spawned */
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	static ABaseProjectile* SpawnAndThrowProjectile(const AActor* ProjectileOwner, TSubclassOf<ABaseProjectile> ProjectileClass, FVector StartLocation, FVector EndLocation, float Speed, USceneComponent* HomingTargetComponent = nullptr);
};
