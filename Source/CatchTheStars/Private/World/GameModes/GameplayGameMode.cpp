// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameModes/GameplayGameMode.h"

#include "Players/MainPlayer.h"

AGameplayGameMode::AGameplayGameMode()
{
	PlayerControllerClass = AMainPlayer::StaticClass();
	DefaultPawnClass = nullptr;
}

void AGameplayGameMode::Finish()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->DisableInput(nullptr);
	
	OnGameFinish();
}

void AGameplayGameMode::Restart()
{
	
}
