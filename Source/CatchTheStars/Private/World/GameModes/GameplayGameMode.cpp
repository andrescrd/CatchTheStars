// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameModes/GameplayGameMode.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Players/MainPlayer.h"
#include "World/GameInstance/OwnGameInstance.h"
#include "World/Managers/LevelManager.h"

AGameplayGameMode::AGameplayGameMode()
{
	MaxTime = 0;
	GameStatus = EGameStatusEnum::Unknown;	
	PlayerControllerClass = AMainPlayer::StaticClass();
	DefaultPawnClass = nullptr;
}

void AGameplayGameMode::StartPlay()
{
	Super::StartPlay();
	
	// MaxTime = GameInstance->GetLevelManager()->GetGameplayLevels()[0].MaxTime;
	SetGameStatus(EGameStatusEnum::Waiting);
}

void AGameplayGameMode::LevelComplete() { SetGameStatus(EGameStatusEnum::Completed); }

void AGameplayGameMode::StartCounter() { MaxTime++; }

void AGameplayGameMode::SetGameStatus(const EGameStatusEnum CurrentGameStatus)
{
	if (GameStatus == CurrentGameStatus)
		return;

	GameStatus = CurrentGameStatus;
	HandleGameStatus(GameStatus);

	OnGameStatusChange(GameStatus); // call bp implementation
}

void AGameplayGameMode::OnWaiting()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode: WAITING"));
	SetGameStatus(EGameStatusEnum::Playing);
}

void AGameplayGameMode::OnPlaying()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode: PLAYING"));
	GetWorld()->GetTimerManager().SetTimer(CounterTimerHandle, this, &AGameplayGameMode::StartCounter, 1, true);
}

void AGameplayGameMode::OnFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode: FINISHED"));
	GetWorld()->GetTimerManager().ClearTimer(CounterTimerHandle);
	ToggleInput();
}

void AGameplayGameMode::ToggleInput() const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	(PC->InputEnabled()) ? PC->DisableInput(nullptr) : PC->EnableInput(nullptr);
}

void AGameplayGameMode::HandleGameStatus(const EGameStatusEnum CurrentGameStatus)
{
	switch (CurrentGameStatus)
	{
	case EGameStatusEnum::Waiting:
		OnWaiting();
		break;
	case EGameStatusEnum::Playing:
		OnPlaying();
		break;
	case EGameStatusEnum::Completed:		
	case EGameStatusEnum::GameOver:
		OnFinished();
		break;
	default:
		break;
	}
}
