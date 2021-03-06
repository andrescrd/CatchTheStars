// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Actors/NodeGraph.h"
#include "AssetTypeStruct.generated.h"

USTRUCT(BlueprintType)
struct FAssetTypeStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* StartMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMesh* TargetMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	StarTypesEnum Type;

	FAssetTypeStruct(): StartMesh(nullptr), TargetMesh(nullptr), Type(StarTypesEnum::NONE)
	{
	}
};
