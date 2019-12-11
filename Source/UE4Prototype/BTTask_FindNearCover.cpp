// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNearCover.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/PrimitiveComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"

UBTTask_FindNearCover::UBTTask_FindNearCover()
{

}

EBTNodeResult::Type UBTTask_FindNearCover::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), actors);
	//= GetWorld()->ActiveGroupActors;

	APawn* enemy = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Enemy")));
	APawn* self = OwnerComp.GetAIOwner()->GetPawn();
	FVector location;
	float lessDistance = 99999.f;
	bool isHit = false;

	ABLOG(Warning, TEXT("%d"), actors.Num());

	for (auto actor : actors)
	{
		if (!Cast<ACharacter>(actor) && actor->GetComponentByClass(UPrimitiveComponent::StaticClass()))
		{

			FVector start = enemy->GetActorLocation() + FVector(0.f, 0.f, 87.f),
				dir = actor->GetActorLocation() - enemy->GetActorLocation();
			dir.Normalize();

			FCollisionQueryParams params(NAME_None, false, enemy);

			FHitResult hit;
			if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir * 10000.f,
				ECC_GameTraceChannel2, params))
			{
				if (hit.Actor == actor)
				{
					FVector hiddenPoint = hit.Location + dir * 500.f;

					if (GetWorld()->LineTraceSingleByChannel(hit, hiddenPoint, hiddenPoint + FVector::DownVector * 5000.f,
						ECC_GameTraceChannel2, params))
					{
						hiddenPoint = hit.Location;

						FNavLocation fixedHiddenPoint;
						//DrawDebugSphere(GetWorld(), hiddenPoint, 100.f, 32, FColor::Red, false, 5.f);

						const FNavAgentProperties& AgentProps = OwnerComp.GetAIOwner()->GetNavAgentPropertiesRef();
						FVector extent = AgentProps.GetExtent();
						ANavigationData* navData = UNavigationSystemV1::GetNavigationSystem(GetWorld())->GetNavDataForProps(AgentProps);
						if (UNavigationSystemV1::GetNavigationSystem(GetWorld())->ProjectPointToNavigation(hiddenPoint, fixedHiddenPoint, AgentProps.GetExtent(), navData))
						{
							//ABLOG(Warning, TEXT("%s is find cover point"), *actor->GetName());
							float distance = (fixedHiddenPoint.Location - self->GetActorLocation()).Size();
							if (distance < lessDistance)
							{
								location = fixedHiddenPoint.Location;
								lessDistance = distance;
								isHit = true;
							}

						}
					}
				}
			}
		}
	}

	if (isHit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("CoverPos"), location);
	}

	return isHit ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
