// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIAIController::AAIAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/AIBB.AIBB'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/AIBT.AIBT'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	bAllowStrafe = false;
}

void AAIAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsFloat(FName("DetachAngle"), 120.f);
		Blackboard->SetValueAsFloat(FName("DetachRange"), 1200.f);
		RunBehaviorTree(BTAsset);
	}
}

void AAIAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
