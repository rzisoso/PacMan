// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "..\PacManGameModeBase.h"
#include "PacManCharacter.generated.h"

UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveXAxis(float XValue);
	void MoveYAxis(float YValue);

	void ReStart();
	void NewGame();
	void Pause();

	void Killed();
	FORCEINLINE int GetLives() { return Lives; }
	FORCEINLINE int GetCollect() { return CollectablesToEat; }

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	APacManGameModeBase* GameMode;
	FVector CurrentVelocity;
	float Speed;

	int CollectablesToEat;
	int Lives;

	FVector StartPoint;

	//TArray<AActor*> Array;
	//int Arrays;
};
