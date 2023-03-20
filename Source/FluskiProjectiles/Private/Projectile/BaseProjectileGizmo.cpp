#include "Projectile/BaseProjectileGizmo.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SplineMeshComponent.h"

ABaseProjectileGizmo::ABaseProjectileGizmo()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline Component");
	SetRootComponent(SplineComponent);

	SetActorEnableCollision(false);
}

void ABaseProjectileGizmo::UpdateSplinePoints(TArray<FVector> Points) const
{
	SplineComponent->ClearSplinePoints();
	SplineComponent->SetSplinePoints(Points, ESplineCoordinateSpace::World);
}

void ABaseProjectileGizmo::UpdateSplineMeshes()
{
	ClearSplineMeshes();
	
	for (int i = 0; i < SplineComponent->GetNumberOfSplinePoints()-1; i++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		SplineMeshComponent->SetStaticMesh(VisualMesh);
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		SplineMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SplineMeshComponent->SetCastShadow(false);
		SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::X, true);
		SplineMeshComponent->SetStartAndEnd(GetSplinePos(i), GetSplineTan(i), GetSplinePos(i+1), GetSplineTan(i+1));
		
		SplineMesh.Add(SplineMeshComponent);
	}
}

void ABaseProjectileGizmo::ClearSplineMeshes()
{
	for(int i = 0; i < SplineMesh.Num(); i++)
	{
		SplineMesh[i]->DestroyComponent();
	}

	SplineMesh.Empty();
}

FVector ABaseProjectileGizmo::GetSplinePos(const int Index) const
{
	return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::Local);
}

FVector ABaseProjectileGizmo::GetSplineTan(const int Index) const
{
	return SplineComponent->GetTangentAtSplinePoint(Index, ESplineCoordinateSpace::Local);

}

void ABaseProjectileGizmo::DrawHitPoint(const FVector Location)
{
	if (HitPointActor == nullptr)
	{
		HitPointActor = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass());
		HitPointActor->SetChildActorClass(HitPointActorClass);
		HitPointActor->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		HitPointActor->RegisterComponentWithWorld(GetWorld());
	}

	HitPointActor->SetWorldLocation(Location, true);
}

void ABaseProjectileGizmo::HideHitPoint()
{
	if (HitPointActor != nullptr)
	{
		HitPointActor->DestroyComponent();
		HitPointActor = nullptr;
	}
}

void ABaseProjectileGizmo::UpdateGizmo(AActor* GrenadeOwner, UFluskiProjectileMovementComponent* Projectile, const float Radius, const FVector Direction)
{
	if (Projectile == nullptr)
		return;
	
	const FVector Location = Projectile->GetOwner()->GetActorLocation();
	const FVector Velocity = Direction * Projectile->GetProjectileSpeed();
	
	FPredictProjectilePathParams PredictParams = FPredictProjectilePathParams(Radius, Location, Velocity, 5);
	PredictParams.OverrideGravityZ = GetWorld()->GetGravityZ() * Projectile->GetGravityScale();

	PredictParams.ActorsToIgnore.Add(Projectile->GetOwner());
	PredictParams.ActorsToIgnore.Add(GrenadeOwner);

	PredictParams.bTraceWithCollision = true;

	PredictParams.ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	PredictParams.ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));


	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);

	TArray<FVector> ParabolePoints;
	for(int i = 0; i < PredictResult.PathData.Num(); ++i)
	{
		ParabolePoints.Add(PredictResult.PathData[i].Location);
	}

	if (PredictResult.HitResult.ImpactPoint != FVector::ZeroVector && Projectile != nullptr)
	{
		DrawHitPoint(PredictResult.HitResult.ImpactPoint);
	}
	else
	{
		HideHitPoint();
	}

	UpdateSplinePoints(ParabolePoints);
	UpdateSplineMeshes();
}
