#include "BreakableActor.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableActor::GetHit(const FVector& ImpactPoint)
{
	DrawDebugSphere(GetWorld(), ImpactPoint, 10.f, 24.f, FColor::Red, false, 5.f);
}
