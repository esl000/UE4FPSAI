// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4PrototypeGameMode.h"
#include "UE4PrototypeHUD.h"
#include "UE4PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4PrototypeGameMode::AUE4PrototypeGameMode()
	: Super()
{
	DefaultPawnClass = AUE4PrototypeCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AUE4PrototypeHUD::StaticClass();
}
