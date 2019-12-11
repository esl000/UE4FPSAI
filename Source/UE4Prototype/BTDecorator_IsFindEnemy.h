// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Prototype.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsFindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROTOTYPE_API UBTDecorator_IsFindEnemy : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsFindEnemy();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
