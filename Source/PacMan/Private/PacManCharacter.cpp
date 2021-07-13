// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include "..\Public\Collectables.h"
#include <EngineUtils.h>

// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentVelocity = FVector(0.f);
	Speed = 100.f;

	CollectablesToEat = 0;
	Lives = 3;

	//Arrays = 0;
}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	StartPoint = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("StartPoint: %s"), *StartPoint.ToString());
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()))->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);
	/*TArray<AActor*> Array;
	UGameplayStatics::GetAllActorsOfClass(this, ACollectables::StaticClass(), Array);
	Arrays = Array.Num();*/

	for (TActorIterator<ACollectables> CollectablesIterator(GetWorld()); CollectablesIterator; ++CollectablesIterator)
	{
		++CollectablesToEat;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Total Collectables is %d"), CollectablesToEat);
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		AddMovementInput(CurrentVelocity * Speed * DeltaTime);
	}
	
}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveXAxis"), this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis(TEXT("MoveYAxis"), this, &APacManCharacter::MoveYAxis);
	PlayerInputComponent->BindAction(TEXT("NewGame"), EInputEvent::IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction(TEXT("ReStart"), EInputEvent::IE_Pressed, this, &APacManCharacter::ReStart);
	PlayerInputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &APacManCharacter::Pause);

}

void APacManCharacter::MoveXAxis(float XValue)
{
	
	CurrentVelocity.X = XValue;
}

void APacManCharacter::MoveYAxis(float YValue)
{
	CurrentVelocity.Y = YValue;
}

void APacManCharacter::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if(GameMode->GetCurrentState() == EGameState::EPause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Killed()
{
	//UE_LOG(LogTemp, Warning, TEXT("Killed!!!"));
	if (--Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(StartPoint);
	}
}

void APacManCharacter::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACollectables::StaticClass()))
		{
			ACollectables* Collectable = Cast<ACollectables>(OtherActor);
			if (Collectable->bIsSuperCollectable)
			{
				GameMode->SetEnemyVuln();
			}
			OtherActor->Destroy();
			if (--CollectablesToEat == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
			//UE_LOG(LogTemp, Warning, TEXT("Remain Collectables is %d"), CollectablesToEat);
			/*--Arrays;
			if (Arrays == 90)
			{
				GameMode->SetCurrentState(EGameState::EGameOver);
				UE_LOG(LogTemp, Warning, TEXT("Win!!!!!!!!!!!!"));

			}*/
		}
	}
}

