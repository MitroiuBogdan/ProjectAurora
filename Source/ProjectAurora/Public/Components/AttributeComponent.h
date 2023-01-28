#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTAURORA_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category= "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category= "Actor Attributes")
	float MaxHealth;

public:
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetMaxHealth(float Value) { this->MaxHealth = Value; }
	FORCEINLINE void SetHealth(float Value) { this->Health = Value; }

	void ReceiveDamage(float Damage);
	float GetHealthPercent();
};
