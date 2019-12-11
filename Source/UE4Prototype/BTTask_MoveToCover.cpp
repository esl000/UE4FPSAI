// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToCover.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AIController.h"
#include "AICharacter.h"

UBTTask_MoveToCover::UBTTask_MoveToCover()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToCover::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetAIOwner()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("CoverPos")), 50.f,
		true, true, false, false);
	return EBTNodeResult::InProgress;
}

void UBTTask_MoveToCover::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* self = OwnerComp.GetAIOwner()->GetPawn(),
		*enemy = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector start = self->GetActorLocation() + FVector(0.f, 0.f, 87.f),
		dir = enemy->GetActorLocation() - self->GetActorLocation();
	dir.Normalize();

	float range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("DetachRange"));
	FCollisionQueryParams params(NAME_None, false, self);

	if ((OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("CoverPos")) - self->GetActorLocation()).Size2D() < 100.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir * range,
		ECC_GameTraceChannel2, params))
	{
		if (hit.Actor == enemy)
		{
			OwnerComp.GetAIOwner()->SetFocalPoint(enemy->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("LastEnemyPos"), enemy->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("LastFocusEnemyPos"), self->GetActorLocation());
			if (AAICharacter* aichar = Cast<AAICharacter>(self))
			{
				if (!aichar->IsFire)
				{
					aichar->StartFire();
					return;
				}
			}
		}
	}

	if (AAICharacter* aichar = Cast<AAICharacter>(self))
	{
		if (aichar->IsFire)
		{
			aichar->StopFire();
			return;
		}
	}
}
