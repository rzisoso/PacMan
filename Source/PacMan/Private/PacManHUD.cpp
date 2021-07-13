// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"
#include "..\PacManGameModeBase.h"
#include "..\Public\PacManCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine/Font.h>
#include <Engine/Canvas.h>


APacManHUD::APacManHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));
	if (Font.Succeeded())
	{
		HUDFont = Font.Object;
	}
}

void APacManHUD::DrawHUD()
{
	APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	APacManCharacter* PacMan = nullptr;
	FString LiveString;
	FString Collect;
	switch (GameMode->GetCurrentState())
	{
	case EGameState::EMenu:
		DrawText(TEXT("Welcome to PacMan!\n\nN to start a new game \nP to pause the game"), FColor::White, (Canvas->SizeX / 2.f) - 150.f, (Canvas->SizeY / 2.f) - 100.f, HUDFont, 2.f);
		break;
	case EGameState::EPlaying:
		PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (PacMan)
		{
			LiveString = TEXT("Lives: ") + FString::FromInt(PacMan->GetLives());
			DrawText(LiveString, FColor::Blue, 50, 50, HUDFont);

			Collect = TEXT("Collect: ") + FString::FromInt(PacMan->GetCollect());
			DrawText(Collect, FColor::Blue, Canvas->SizeX - 150, 50, HUDFont);
		}
		break;
	case EGameState::EPause:
		DrawText(TEXT("P to continue the game"), FColor::White, (Canvas->SizeX / 2.f) - 150.f, (Canvas->SizeY / 2.f) - 100.f, HUDFont, 2.f);
		break;
	case EGameState::EWin:
		DrawText(TEXT("You Win!!!\n\nR for another"), FColor::White, (Canvas->SizeX / 2.f) - 150.f, (Canvas->SizeY / 2.f) - 100.f, HUDFont, 2.f);
		break;
	case EGameState::EGameOver:
		DrawText(TEXT("Game Over\n\nR for another"), FColor::White, (Canvas->SizeX / 2.f) - 150.f, (Canvas->SizeY / 2.f) - 100.f, HUDFont, 2.f);
		break;
	default:
		break;
	}
}
