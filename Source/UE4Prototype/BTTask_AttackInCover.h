// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Prototype.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackInCover.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROTOTYPE_API UBTTask_AttackInCover : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_AttackInCover();

	FVector DestPoint, StartPoint;
	bool IsOutMovement;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds) override;
	
};
