// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "Enemy.h"
#include <NavigationSystem.h>
#include <TimerManager.h>
#include <Kismet/GameplayStatics.h>
#include "..\PacManGameModeBase.h"

void AAIEnemy::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Bot = Cast<AEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	SearchNewPoint();
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!Bot->GetState() && GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		SearchNewPoint();
	}
}

void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* Nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	if (Nav)
	{
		const float SearchRadius = 10000.f;
		FNavLocation RandomPt;

		const bool bFound = Nav->GetRandomReachablePointInRadius(Bot->GetActorLocation(), SearchRadius, RandomPt);
		if (bFound)
		{
			MoveToLocation(RandomPt);
		}
	}
}

void AAIEnemy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime, this, &AAIEnemy::ReArm, 5.f, false);
}

void AAIEnemy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEnemy::StopMove()
{
	//StopMovement();
	MoveToLocation(Bot->GetActorLocation());
}
