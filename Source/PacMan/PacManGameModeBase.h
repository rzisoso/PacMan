// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameModeBase.generated.h"

/**
 * 
 */

enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};
UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	EGameState CurrentState;
	TArray<class AEnemy*> Enemys;
public:
	virtual void BeginPlay() override;
	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState Value);

	void SetEnemyVuln();
};

FORCEINLINE EGameState APacManGameModeBase::GetCurrentState() const
{
	return CurrentState;
}




