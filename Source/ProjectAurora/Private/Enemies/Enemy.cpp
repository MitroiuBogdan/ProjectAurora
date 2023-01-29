#include "Enemies/Enemy.h"

#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthBarComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Actor Attributes"));
	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBarComponent && Attributes)
	{
		Attributes->SetMaxHealth(100);
		Attributes->SetHealth(100);
		HealthBarComponent->SetHealthPercent(Attributes->GetHealthPercent());
		HealthBarComponent->SetVisibility(false);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CombatTarget)
	{
		double CombatDistance = (CombatTarget->GetActorLocation() - GetActorLocation()).Size();
		if (CombatRadius < CombatDistance)
		{
			CombatTarget = nullptr;
			HealthBarComponent->SetVisibility(false);
		}
	}
}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	DrawDebugSphere(GetWorld(), ImpactPoint, 10.f, 24.f, FColor::Red, false, 5.f);

	if (Attributes && Attributes->IsAlive())
	{
		HealthBarComponent->SetVisibility(true);
		FVector ForwardVector = GetActorForwardVector();
		FVector ImpactPointXY(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
		FVector ToHit = (ImpactPointXY - GetActorLocation()).GetSafeNormal();
		//FORWARD * TOHIT= |FOWARD| * |TOHIT| * COS(Angle)

		double CosAngle = FVector::DotProduct(ForwardVector, ToHit);
		double Angle = FMath::Acos(CosAngle);
		//CONVERT FROM RADIANS TO DEGREES
		Angle = FMath::RadiansToDegrees(Angle);

		FVector CrossProduct = FVector::CrossProduct(ForwardVector, ToHit);
		if (CrossProduct.Z < 0)
		{
			Angle *= -1;
		}

		FName SelectionName("REACT_BACK");
		if (Angle >= -45.f && Angle < 45)
		{
			SelectionName = FName("REACT_FRONT");
		}
		else if (Angle >= 45.f && Angle < 135.f)
		{
			SelectionName = FName("REACT_RIGHT");
		}
		else if (Angle >= -135.f && Angle < -45.f)
		{
			SelectionName = FName("REACT_LEFT");
		}

		PlayGettingHitMontage(SelectionName);

		//DEBUG STUFF
		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 100.f, 5.f,
		                                     FColor::Cyan, 5.f);

		FString debugMessage = FString::Printf(TEXT("Angle - %f"), Angle);
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, debugMessage);
		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ForwardVector * 60.f, 5.f,
		                                     FColor::Magenta, 5.f);
		UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f,
		                                     FColor::Blue, 5.f);
	}
	else
	{
		Die();
		HealthBarComponent->SetVisibility(false);
	}


	if (HitParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), HitParticleSystem, ImpactPoint);
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                         AActor* DamageCauser)
{
	// return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Attributes && HealthBarComponent)
	{
		Attributes->ReceiveDamage(DamageAmount);
		HealthBarComponent->SetHealthPercent(Attributes->GetHealthPercent());
	}

	CombatTarget = EventInstigator->GetPawn();

	return DamageAmount;
}

void AEnemy::PlayGettingHitMontage(const FName& SectionName)

{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->GettingHitMontage)
	{
		// UE_LOG(LogTemp, Warning, TEXT("GettingHitMontage"));
		AnimInstance->Montage_Play(this->GettingHitMontage);
		AnimInstance->Montage_JumpToSection(SectionName, GettingHitMontage);
	};
}

void AEnemy::PlayDeathMontage(const FName& SectionName)

{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->DeathMontage)
	{
		// UE_LOG(LogTemp, Warning, TEXT("GettingHitMontage"));
		AnimInstance->Montage_Play(this->DeathMontage);
		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	};
}

void AEnemy::Die()
{
	PlayDeathMontage(FName("Death"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(2.5f);
}
