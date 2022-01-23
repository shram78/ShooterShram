// ShooterShram Game. All Rights Reserved.

#include "Player/SSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SSCharacterMovementComponent.h"

ASSBaseCharacter::ASSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASSBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASSBaseCharacter::OnStopRunning);
}

void ASSBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    
    if (Amount == 0.0f) return;

    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;

    AddMovementInput(GetActorRightVector(), Amount);
}

void ASSBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ASSBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}

bool ASSBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degress = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degress : Degress * FMath::Sign(CrossProduct.Z);
}
