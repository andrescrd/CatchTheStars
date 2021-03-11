// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Support/Enums/GameStatusEnum.h"

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameStatusEnum GameStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxTime;

	void StartCounter();
	
	void SetGameStatus(EGameStatusEnum CurrentGameStatus);
	void HandleGameStatus(EGameStatusEnum CurrentGameStatus);

	void OnWaiting();
	void OnPlaying();
	void ToggleInput(bool Enable) const;
	void OnFinished();
	
	UFUNCTION(BlueprintImplementableEvent)
    void OnGameStatusChange(EGameStatusEnum CurrentGameStatus);
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void LevelComplete();
	UFUNCTION(BlueprintCallable)
	void NextLevel();
};
