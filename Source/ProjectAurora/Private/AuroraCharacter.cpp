#include "AuroraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAuroraCharacter::AAuroraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ViewCamera->SetupAttachment(CameraBoom);

	ViewCamera->bUsePawnControlRotation = true;
}

void AAuroraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuroraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAuroraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("M_F"), this, &AAuroraCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("M_R"), this, &AAuroraCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AAuroraCharacter::ViewYaw);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AAuroraCharacter::ViewPitch);

	PlayerInputComponent->BindAction(TEXT("JUMP"), IE_Pressed, this, &ACharacter::Jump);
}

void AAuroraCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0)
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	UE_LOG(LogTemp, Warning, TEXT("M_F - %f"), Value);
}

void AAuroraCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0)
	{
		{
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("M_F - %f"), Value);
}


void AAuroraCharacter::ViewYaw(float Value)
{
	AddControllerYawInput(Value);
}

void AAuroraCharacter::ViewPitch(float Value)
{
	AddControllerPitchInput(Value);
}
