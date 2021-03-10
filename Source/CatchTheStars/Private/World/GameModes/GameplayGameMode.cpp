// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameModes/GameplayGameMode.h"

#include "Players/MainPlayer.h"
#include "World/GameInstance/OwnGameInstance.h"
#include "World/Managers/LevelManager.h"

AGameplayGameMode::AGameplayGameMode()
{
	MaxTime = 99;
	GameStatus = EGameStatusEnum::Unknown;	
	PlayerControllerClass = AMainPlayer::StaticClass();
	DefaultPawnClass = nullptr;
}

void AGameplayGameMode::StartPlay()
{
	Super::StartPlay();

	GameInstance = GetGameInstance<UOwnGameInstance>();
	MaxTime = GameInstance->GetLevelManager()->GetGameplayLevels()[0].MaxTime;
	Time = MaxTime;
	SetGameStatus(EGameStatusEnum::Waiting);
}

void AGameplayGameMode::LevelComplete() { SetGameStatus(EGameStatusEnum::Finished); }

void AGameplayGameMode::StartCounter()
{
	Time--;

	if (Time <= 0)
		SetGameStatus(EGameStatusEnum::Finished);
}

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
	case EGameStatusEnum::Finished:
		OnFinished();
		break;
	default:
		break;
	}
}
