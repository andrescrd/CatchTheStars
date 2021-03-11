// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Support/Enums/GameStatusEnum.h"
#include "World/GameInstance/OwnGameInstance.h"

#include "GameplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplayGameMode();

protected:
	FTimerHandle CounterTimerHandle;

	// UPROPERTY()
	// class UOwnGameInstance* GameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameStatusEnum GameStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxTime;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// float Time;

	void StartCounter();
	
	void SetGameStatus(EGameStatusEnum CurrentGameStatus);
	void HandleGameStatus(EGameStatusEnum CurrentGameStatus);

	void OnWaiting();
	void OnPlaying();
	void ToggleInput() const;
	void OnFinished();
	
	UFUNCTION(BlueprintImplementableEvent)
    void OnGameStatusChange(EGameStatusEnum CurrentGameStatus);
	
public:
	virtual void StartPlay() override;
	void LevelComplete();
};
