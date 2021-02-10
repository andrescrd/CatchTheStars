// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	class ACNode* SelectedNode;
	UPROPERTY(VisibleInstanceOnly)
	class ACTarget* SelectedTarget;
	UPROPERTY(VisibleInstanceOnly)
	class ACStar* SelectedStar;
	UPROPERTY(VisibleInstanceOnly)	
	class ACCharacter* CurrentCharacter;

	virtual void SetupInputComponent() override;
	ACCharacter* GetCurrentCharacter();
	
	UFUNCTION()
	void OnSelectionStart();
	UFUNCTION()
	void OnSelectionEnd();
};
