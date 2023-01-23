#include "Enemies/Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialExpressionChannelMaskParameter.h"


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

	FVector ForwardVector = GetActorForwardVector();
	FVector ImpactPointXY(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	FVector ToHit = (ImpactPointXY - GetActorLocation()).GetSafeNormal();

	//FORWARD * TOHIT= |FOWARD| * |TOHIT| * COS(Angle)
	double CosAngle = FVector::DotProduct(ForwardVector, ToHit);
	double Angle = FMath::Acos(CosAngle);
	//CONVERT FROM RADIANS TO DEGREES
	Angle = FMath::RadiansToDegrees(Angle);
	PlayGettingHitMontage(FName("REACT_BACK"));


	FString debugMessage = FString::Printf(TEXT("Angle - %f"), Angle);
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, debugMessage);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ForwardVector * 60.f, 5.f,
	                                     FColor::Magenta, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f,
	                                     FColor::Blue, 5.f);
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
