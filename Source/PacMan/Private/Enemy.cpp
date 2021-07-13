// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include <UObject/ConstructorHelpers.h>
#include <Components/StaticMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <TimerManager.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "..\Public\PacManCharacter.h"
#include "AIEnemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyBody"));
	EnemyBody->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	if (EnemyMesh.Succeeded())
	{
		EnemyBody->SetStaticMesh(EnemyMesh.Object);
	}
	EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.f));

	GetCapsuleComponent()->SetCapsuleRadius(40.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	EnemyBody->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
	VulnMaterial = nullptr;
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> EnemyMaterial(TEXT("Material'/Game/Materials/M_Enemy_Vuln.M_Enemy_Vuln'"));
	if (EnemyMaterial.Succeeded())
	{
		
		VulnMaterial = EnemyMaterial.Object;
		/*if (VulnMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found!!!!!!!!!!!!!!!!"));
		}*/
	}
	bIsDead = false;

	AIControllerClass = AAIEnemy::StaticClass();
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
	//SetVuln();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::SetVuln()
{
	GetWorldTimerManager().SetTimer(TimeVuln, this, &AEnemy::SetInVuln, 10.f, false);
	if (bIsVuln)
	{
		return;
	}
	bIsVuln = true;
	EnemyBody->SetMaterial(0, VulnMaterial);
	
	GetCharacterMovement()->MaxWalkSpeed = 50.f;
}

void AEnemy::SetInVuln()
{
	GetWorldTimerManager().ClearTimer(TimeVuln);
	bIsVuln = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void AEnemy::SetMove(bool bMoveIt)
{
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	if (bMoveIt)
	{
		AI->SearchNewPoint();
	}
	else
	{
		AI->StopMove();
	}
}

void AEnemy::Killed()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	AI->GoHome();
}

void AEnemy::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	if (bIsVuln)
	{
		SetInVuln();
	}
	SetMove(true);
}

void AEnemy::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Collision!!!"));
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsVuln)
		{
			Killed();
		}
		else
		{
			Cast<APacManCharacter>(OtherActor)->Killed();
		}
	}
}

