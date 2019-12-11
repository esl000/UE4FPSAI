// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "UE4PrototypeProjectile.h"
#include "Sound/SoundWave.h"
#include "AIAIController.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_BODY(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_GUN(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> SW_ATTACKSOUND(TEXT("SoundWave'/Game/FirstPerson/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02'"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AI_ANIM(TEXT("AnimBlueprint'/Game/AnimStarterPack/AIAnim.AIAnim_C'"));

	GetMesh()->RelativeLocation = FVector(0.f, 0.f, -87.f);
	GetMesh()->RelativeRotation = FRotator(0.f, -90.f, 0.f);

	if(SM_BODY.Succeeded())
		GetMesh()->SetSkeletalMesh(SM_BODY.Object);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	if (AI_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(AI_ANIM.Class);

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GUN"));
	Gun->SetupAttachment(GetMesh(), TEXT("gun"));
	if (SM_GUN.Succeeded())
		Gun->SetSkeletalMesh(SM_GUN.Object);

	if (SW_ATTACKSOUND.Succeeded())
		FireSound = SW_ATTACKSOUND.Object;

	AIControllerClass = AAIAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::StartFire()
{
	IsFire = true;
}

void AAICharacter::StopFire()
{
	IsFire = false;
}

void AAICharacter::Fire()
{
	FVector dest = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector start = Gun->GetBoneLocation(TEXT("b_gun_muzzleflash")) + Gun->GetBoneQuaternion(TEXT("b_gun_muzzleflash")).Vector() * 30.f;
	FRotator rot = (dest - start).ToOrientationRotator();
	GetWorld()->SpawnActor<AUE4PrototypeProjectile>(AUE4PrototypeProjectile::StaticClass(), 
		start, rot);

	UGameplayStatics::PlaySoundAtLocation(this, FireSound, start);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

