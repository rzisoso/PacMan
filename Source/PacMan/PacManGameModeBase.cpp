// Copyright Epic Games, Inc. All Rights Reserved.


#include "PacManGameModeBase.h"
#include "Public\Enemy.h"
#include <EngineUtils.h>


void APacManGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EGameState::EMenu);
	for (TActorIterator<AEnemy> EnemyIterator(GetWorld()); EnemyIterator; ++EnemyIterator)
	{
		AEnemy* Enemy = Cast<AEnemy>(*EnemyIterator);
		if (Enemy)
		{
			Enemys.Add(Enemy);
		}
	}
}

void APacManGameModeBase::SetCurrentState(EGameState Value)
{
	CurrentState = Value;
	switch (Value)
	{
	case EGameState::EMenu:
		break;
	case EGameState::EPlaying:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->SetMove(true);
		}
		break;
	case EGameState::EPause:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->SetMove(false);
		}
		break;
	case EGameState::EWin:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	case EGameState::EGameOver:
		for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
		{
			(*Iter)->Destroy();
		}
		break;
	default:
		break;
	}
}

void APacManGameModeBase::SetEnemyVuln()
{
	for (AEnemy* x : Enemys)
	{
		x->SetVuln();
	}

	/*for (auto Iter(Enemys.CreateIterator()); Iter; ++Iter)
	{
		(*Iter)->SetVuln();
	}*/
}
