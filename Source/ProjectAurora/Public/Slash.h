#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Slash.generated.h"

UCLASS()
class PROJECTAURORA_API ASlash : public ACharacter
{
	GENERATED_BODY()

public:
	ASlash();
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