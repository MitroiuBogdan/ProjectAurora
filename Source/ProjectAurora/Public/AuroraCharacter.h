#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuroraCharacter.generated.h"

UCLASS()
class PROJECTAURORA_API AAuroraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAuroraCharacter();
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void ViewYaw(float Value);
	virtual void ViewPitch(float Value);
};
