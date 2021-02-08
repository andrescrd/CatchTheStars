// Fill out your copyright notice in the Description page of Project Settings.


#include "World/GameModes/CGameplayGameMode.h"

#include "Players/CPlayerController.h"

ACGameplayGameMode::ACGameplayGameMode()
{
	PlayerControllerClass = ACPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}
