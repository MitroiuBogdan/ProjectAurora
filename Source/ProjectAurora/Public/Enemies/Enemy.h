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

private:
	UPROPERTY(EditDefaultsOnly, Category= Montages)
	UAnimMontage* GettingHitMontage;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit(const FVector& ImpactPoint) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Montages functions
	void PlayGettingHitMontage(const FName& SectionName);
};