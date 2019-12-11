// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFindEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.h"
#include "AIController.h"

UBTDecorator_IsFindEnemy::UBTDecorator_IsFindEnemy()
{

}

bool UBTDecorator_IsFindEnemy::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* self = OwnerComp.GetAIOwner()->GetPawn(),
		*enemy = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector start = self->GetActorLocation() + FVector(0.f, 0.f, 87.f), 
		dir = enemy->GetActorLocation() - self->GetActorLocation();
	dir.Normalize();

	float range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("DetachRange"));
	FCollisionQueryParams params(NAME_None, false, self);

	if (FVector::DotProduct(dir, self->GetActorForwardVector()) < FMath::Cos(FMath::DegreesToRadians(
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("DetachAngle")))))
		return false;

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir * range,
		ECC_GameTraceChannel2, params))
	{
		if (hit.Actor == enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Enemy"), enemy);
			return bResult;
		}
	}

	return false;
}
