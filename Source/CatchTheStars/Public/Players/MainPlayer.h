// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API AMainPlayer : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayer();
		
protected:
	
	UPROPERTY(VisibleInstanceOnly)
	class ANodeGraph* SelectedNode;
	UPROPERTY(VisibleInstanceOnly)
	class ATarget* SelectedTarget;
	UPROPERTY(VisibleInstanceOnly)
	class AStar* SelectedStar;
	UPROPERTY(VisibleInstanceOnly)	
	class AGraph* CurrentGraph;
	
	virtual void SetupInputComponent() override;
	class AGraph* GetCurrentGraph();
	void UnSelected();

	void SetSelectedTarget(class ATarget* Target);
	void SetSelectedStar(class AStar* Star);

	UFUNCTION()
	void OnSelected();
};
