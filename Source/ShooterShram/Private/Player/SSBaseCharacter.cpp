// ShooterShram Game. All Rights Reserved.

#include "Player/SSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASSBaseCharacter::ASSBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASSBaseCharacter::AddControllerYawInput);
}

void ASSBaseCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASSBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}
