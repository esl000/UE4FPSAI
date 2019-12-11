// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UE4PrototypeHUD.generated.h"

UCLASS()
class AUE4PrototypeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUE4PrototypeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

