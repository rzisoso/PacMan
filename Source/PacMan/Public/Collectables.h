// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectables.generated.h"

UCLASS()
class PACMAN_API ACollectables : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectables();

	UPROPERTY(VisibleAnywhere, Category  = "Collectable")
	class UStaticMeshComponent* CollectableMesh;
	UPROPERTY(VisibleAnywhere, Category = "Collectable")
	class USphereComponent* BaseCollisionComponent;
	UPROPERTY(EditAnywhere, Category = "Collectable")
	bool bIsSuperCollectable;

	//class UMaterialInterface* MaterialSuper;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
