// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actors/CStar.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPlayerController();
		
protected:
	UPROPERTY(VisibleInstanceOnly)
	ACStar* SelectedStar;
	
	virtual  void SetupInputComponent() override;

	UFUNCTION()
	void OnSelectionStart();
	UFUNCTION()
	void OnSelectionEnd();
};
