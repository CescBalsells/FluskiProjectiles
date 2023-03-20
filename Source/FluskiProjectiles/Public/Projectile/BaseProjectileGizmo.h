#pragma once
#include "GrenadeProjectile.h"
#include "Engine/SplineMeshActor.h"
#include "Components/SplineComponent.h"

#include "BaseProjectileGizmo.generated.h"

UCLASS()
class FLUSKIPROJECTILES_API ABaseProjectileGizmo : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<UStaticMesh> VisualMesh;

	UPROPERTY(BlueprintReadWrite, Category=FluskiProjectile)
	TArray<TObjectPtr<USplineMeshComponent>> SplineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FluskiProjectile)
	TSubclassOf<AActor> HitPointActorClass;

	UPROPERTY(BlueprintReadWrite, Category=FluskiProjectile)
	TObjectPtr<UChildActorComponent> HitPointActor;

public:
	ABaseProjectileGizmo();
	
	void UpdateSplinePoints(TArray<FVector> Points) const;
	void UpdateSplineMeshes();
	void ClearSplineMeshes();

	FVector GetSplinePos(const int Index) const;
	FVector GetSplineTan(const int Index) const;
	
	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	void DrawHitPoint(FVector Location);

	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	void HideHitPoint();

	UFUNCTION(BlueprintCallable, Category=FluskiProjectile)
	void UpdateGizmo(AActor* GrenadeOwner, UFluskiProjectileMovementComponent* Projectile, const float Radius, const FVector Direction);
};