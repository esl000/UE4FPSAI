// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Prototype.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNearCover.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROTOTYPE_API UBTTask_FindNearCover : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindNearCover();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
