// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Body")
	class UStaticMeshComponent* EnemyBody;

	void SetVuln();
	void SetInVuln();

	void SetMove(bool bMoveIt);
	void Killed();
	void ReArm();
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	FORCEINLINE bool GetState() { return bIsDead; }

private:
	class UMaterialInterface* DefaultMaterial;
	UMaterialInterface* VulnMaterial;
	FTimerHandle TimeVuln;
	bool bIsVuln;
	bool bIsDead;
};
