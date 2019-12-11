// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackInCover.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AIController.h"
#include "AICharacter.h"

UBTTask_AttackInCover::UBTTask_AttackInCover()
{
	bNotifyTick = true;
	IsOutMovement = false;
}

EBTNodeResult::Type UBTTask_AttackInCover::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	DestPoint = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("LastFocusEnemyPos"));
	StartPoint = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	DestPoint = DestPoint + (DestPoint - StartPoint).GetUnsafeNormal2D() * 180.f;
	OwnerComp.GetAIOwner()->MoveToLocation(DestPoint, 0.f,
		true, true, false, false);
	IsOutMovement = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_AttackInCover::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* self = OwnerComp.GetAIOwner()->GetPawn(),
		*enemy = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector start = self->GetActorLocation() + FVector(0.f, 0.f, 87.f),
		dir = enemy->GetActorLocation() - self->GetActorLocation();
	dir.Normalize();

	float range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("DetachRange"));
	FCollisionQueryParams params(NAME_None, false, self);

	bool isFire = false;
	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir * range,
		ECC_GameTraceChannel2, params))
	{
		if (hit.Actor == enemy)
		{
			isFire = true;
			OwnerComp.GetAIOwner()->SetFocalPoint(enemy->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("LastEnemyPos"), enemy->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("LastFocusEnemyPos"), self->GetActorLocation());
			if (AAICharacter* aichar = Cast<AAICharacter>(self))
			{
				if (!aichar->IsFire)
				{
					aichar->StartFire();
				}
			}
		}
	}

	if (AAICharacter* aichar = Cast<AAICharacter>(self))
	{
		if (!isFire && aichar->IsFire)
		{
			aichar->StopFire();
		}
	}

	if ((DestPoint - self->GetActorLocation()).Size2D() < 80.f)
	{
		if ((!isFire && IsOutMovement) || (isFire && !IsOutMovement))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		ABLOG(Warning, TEXT("Pass2"));

		FVector tempStartPoint = DestPoint;
		DestPoint = StartPoint;
		StartPoint = tempStartPoint;
		OwnerComp.GetAIOwner()->StopMovement();
		OwnerComp.GetAIOwner()->MoveToLocation(DestPoint, 0.f,
			true, true, false, false);

		IsOutMovement = !IsOutMovement;
	}


}
