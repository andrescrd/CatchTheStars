// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Support/Enums/StarTypesEnum.h"
#include "Support/Structures/AssetTypeStruct.h"


#include "TypeDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UTypeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAssetTypeStruct> AssetTypes;
	
	class UStaticMesh* GetStarMesh(StarTypesEnum Type);
	class UStaticMesh* GetTargetMesh(StarTypesEnum Type);
};
