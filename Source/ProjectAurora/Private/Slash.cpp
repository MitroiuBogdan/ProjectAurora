#include "Slash.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASlash::ASlash()
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

void ASlash::BeginPlay()
{
	Super::BeginPlay();
}

void ASlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlash::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("M_F"), this, &ASlash::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("M_R"), this, &ASlash::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &ASlash::ViewYaw);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &ASlash::ViewPitch);

	PlayerInputComponent->BindAction(TEXT("JUMP"), IE_Pressed, this, &ACharacter::Jump);
}

void ASlash::MoveForward(float Value)
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

void ASlash::MoveRight(float Value)
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


void ASlash::ViewYaw(float Value)
{
	AddControllerYawInput(Value);
}

void ASlash::ViewPitch(float Value)
{
	AddControllerPitchInput(Value);
}
