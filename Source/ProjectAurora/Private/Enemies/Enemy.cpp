#include "Enemies/Enemy.h"

#include "Components/CapsuleComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::GetHit(const FVector& ImpactPoint)
{
	DrawDebugSphere(GetWorld(), ImpactPoint, 10.f, 24.f, FColor::Red, false, 5.f);
	PlayGettingHitMontage();
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::PlayGettingHitMontage(const FName& SectionName)

{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->GettingHitMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("GettingHitMontage"));
		AnimInstance->Montage_Play(this->GettingHitMontage);
		AnimInstance->Montage_JumpToSection(SectionName, GettingHitMontage);
	};
}
