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

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance<UOwnGameInstance>()->LoadMap(this);
	SetGameStatus(EGameStatusEnum::Waiting);
}

void AGameplayGameMode::LevelComplete() { SetGameStatus(EGameStatusEnum::Completed); }

void AGameplayGameMode::NextLevel()
{
	GetGameInstance<UOwnGameInstance>()->LoadNextGameplayLevel(this);
	SetGameStatus(EGameStatusEnum::Waiting);
}

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
	MaxTime = 0;
	SetGameStatus(EGameStatusEnum::Playing);
}

void AGameplayGameMode::OnPlaying()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode: PLAYING"));
	ToggleInput(true);
	GetWorld()->GetTimerManager().SetTimer(CounterTimerHandle, this, &AGameplayGameMode::StartCounter, 1, true);
}

void AGameplayGameMode::OnFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode: FINISHED"));
	GetWorld()->GetTimerManager().ClearTimer(CounterTimerHandle);
	ToggleInput(false);
}

void AGameplayGameMode::ToggleInput(const bool Enable) const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (Enable)
		PC->EnableInput(nullptr);
	else
		PC->DisableInput(nullptr);
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
