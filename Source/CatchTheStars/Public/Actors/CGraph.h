// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"

#include "CGraph.generated.h"

UCLASS()
class CATCHTHESTARS_API ACGraph : public AActor
{
	GENERATED_BODY()

public:
	ACGraph();

protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TMap<class ACNode*, bool> NodesSucessMap;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int CurrentSuccess;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int MaxSuccess;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<class UNiagaraComponent*> Paths;

	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int NodesCounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ACNode> NodeClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* FXTemplate;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void SuccessAttached(const ACNode* Node, const bool Success);
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor)
	void GenerateGraph();
	UFUNCTION(CallInEditor)
    void GeneratePaths();
};
