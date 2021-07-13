// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine\StaticMesh.h>

// Sets default values
ACollectables::ACollectables()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);
	//MaterialSuper = nullptr;

	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = BaseCollisionComponent;
	
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	CollectableMesh->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (Mesh.Succeeded())
	{
		CollectableMesh->SetStaticMesh(Mesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>Material0(TEXT("Material'/Game/Materials/M_Enemy_Orange.M_Enemy_Orange'"));
	if (Material0.Succeeded())
	{
		CollectableMesh->GetStaticMesh()->SetMaterial(0, Material0.Object);
	}
	/*static ConstructorHelpers::FObjectFinder<UMaterialInterface>Material1(TEXT("Material'/Game/Materials/M_Enemy_Red.M_Enemy_Red'"));
	if (Material1.Succeeded())
	{
		MaterialSuper = Material1.Object;
	}*/
	
	CollectableMesh->SetWorldScale3D(FVector(0.3f));
	BaseCollisionComponent->SetSphereRadius(16);

	bIsSuperCollectable = false;
}

// Called when the game starts or when spawned
void ACollectables::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACollectables::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

