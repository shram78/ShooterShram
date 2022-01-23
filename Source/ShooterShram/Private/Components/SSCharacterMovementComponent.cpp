// ShooterShram Game. All Rights Reserved.

#include "Components/SSCharacterMovementComponent.h"
#include "Player/SSBaseCharacter.h"

float USSCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASSBaseCharacter* Player = Cast<ASSBaseCharacter>(GetPawnOwner()); 
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
