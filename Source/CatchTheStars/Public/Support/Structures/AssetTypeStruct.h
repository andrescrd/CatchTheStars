// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Actors/NodeGraph.h"
#include "AssetTypeStruct.generated.h"

USTRUCT(BlueprintType)
struct FAssetTypeStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* StartMesh;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStarTypesEnum Type;

	FAssetTypeStruct(): StartMesh(nullptr), Type(EStarTypesEnum::NONE)
	{
	}
};
