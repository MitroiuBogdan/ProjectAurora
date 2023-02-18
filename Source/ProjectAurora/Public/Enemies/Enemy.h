#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECTAURORA_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;
	bool InTargetRange(AActor* Target, double Radius);

private:
	UPROPERTY(EditDefaultsOnly, Category= Montages)
	UAnimMontage* GettingHitMontage;
	UPROPERTY(EditDefaultsOnly, Category= Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* HitParticleSystem;

	UPROPERTY(VisibleAnywhere, Category="Actor Attributes")
	class UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere)
	class UHealthBarComponent* HealthBarComponent;

	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 900;


	// Navigation
	// Current Patrol Target
	UPROPERTY()
	class AAIController* EnemyController;
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	AActor* PatrolTarget;
	UPROPERTY(EditInstanceOnly, Category="AI Navigation")
	TArray<AActor*> PatrolTargets;
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	//Timer
	FTimerHandle PatrolTimerHandle;
	void PatrolTargetFinished();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
	//Montages functions
	void PlayGettingHitMontage(const FName& SectionName);
	void PlayDeathMontage(const FName& SectionName);
	void Die();
	void MoveToTarget(AActor* Target);
};
