// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Support/Structures/LinkStruct.h"


#include "Graph.generated.h"

UCLASS()
class CATCHTHESTARS_API AGraph : public AActor
{
	GENERATED_BODY()

public:
	AGraph();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	int CurrentSuccess;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	int MaxSuccess;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	TMap<FString, FLinkStruct> Links;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	TMap<class ANodeGraph*, bool> NodesSuccessMap;

	UPROPERTY(VisibleInstanceOnly)
	USceneComponent* Root;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=Setup)
	bool bShowLinks;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=Setup)
	int NodesCounter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	TSubclassOf<class ANodeGraph> NodeClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UNiagaraSystem* FXTemplate;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SuccessAttached(const ANodeGraph* Node, const bool Success);

	void SetupLinks(ANodeGraph* Node);	
	void AddNiagaraLink(const FVector& FromVector, const FVector& ToVector) const;

	void ShowLinks();

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	bool IsAvailableLink(ANodeGraph* From, ANodeGraph* To);

	UFUNCTION(CallInEditor, Category=Setup)
	void GenerateGraph();
};
