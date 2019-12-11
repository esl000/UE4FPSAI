// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Prototype.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class UE4PROTOTYPE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USoundWave* FireSound;


	// Sets default values for this character's properties
	AAICharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartFire();
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void Fire();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
