// ShooterShram Game. All Rights Reserved.

#include "SSGameModeBase.h"
#include "Player/SSBaseCharacter.h"
#include "Player/SSPlayerController.h"

ASSGameModeBase::ASSGameModeBase()
{
    DefaultPawnClass = ASSBaseCharacter::StaticClass();
    PlayerControllerClass = ASSPlayerController::StaticClass();



}
