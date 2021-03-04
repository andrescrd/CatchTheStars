// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CStarDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CATCHTHESTARS_API UCStarDataAsset : public UDataAsset
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Texture;
};
