// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Support/Enums/StarTypesEnum.h"

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
	TMap<StarTypesEnum,class UStaticMesh*> Meshes;
	
	class UStaticMesh* GetMesh(StarTypesEnum Type);
};
