// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CGraph.generated.h"

UCLASS()
class CATCHTHESTARS_API ACGraph : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACGraph();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class ACNode*> Nodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int NodesCounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ACNode> NodeClass;

	virtual void BeginPlay() override;

public:

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor)
	void GenerateGraph();
};
