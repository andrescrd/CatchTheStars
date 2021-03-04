// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Support/Structures/CLink.h"


#include "CGraph.generated.h"

UCLASS()
class CATCHTHESTARS_API ACGraph : public AActor
{
	GENERATED_BODY()

public:
	ACGraph();

protected:
	int CurrentSuccess;
	int MaxSuccess;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly ,Category=Setup)
	TSet<FString> Links;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly ,Category=Setup)
	TMap<class ACNode*, bool> NodesSuccessMap;	
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly ,Category=Setup)
	TArray<class UNiagaraComponent*> Paths;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly,Category=Setup)
	TArray<FLinkStruct> LinkMap;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly,Category=Setup)
	int NodesCounter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=Setup)
	TSubclassOf<class ACNode> NodeClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=Setup)
	UNiagaraSystem* FXTemplate;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void SuccessAttached(const ACNode* Node, const bool Success);
	
public:
	// virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(CallInEditor,Category=Setup)
	void GenerateGraph();
	UFUNCTION(CallInEditor,Category=Setup)
    void GeneratePaths();
	bool IsAvailableLink(ACNode* From, ACNode* To);
};
