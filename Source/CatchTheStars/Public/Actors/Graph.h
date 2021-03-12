// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Support/Structures/LinkStruct.h"


#include "Graph.generated.h"

// DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTimelineColor, FLinearColor, Output, FString, Name);

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
	TMap<FString, class UNiagaraComponent*> NiagaraMap;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	FLinearColor LinearColorCurve;
		
	virtual void BeginPlay() override;

	UFUNCTION()
	void SuccessAttached(const class ANodeGraph* Node, const bool Success);

	void SetupLinks(class ANodeGraph* Node);
	void AddNiagaraLink(FString Id, const ANodeGraph* From, const ANodeGraph* To);

	void ShowDebugLinks();
	void ShowSuccessLinks();

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginDestroy() override;
	
	bool IsAvailableLink(class ANodeGraph* From, class ANodeGraph* To);

	UFUNCTION(CallInEditor, Category=Setup)
	void AddSingleNode();
	class ANodeGraph*  CreateNewNode();
	UFUNCTION(CallInEditor, Category=Setup)
	void GenerateGraph();
};
