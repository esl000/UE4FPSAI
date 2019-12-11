// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Prototype.h"
#include "AIController.h"
#include "AIAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROTOTYPE_API AAIAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAIAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
	
};
