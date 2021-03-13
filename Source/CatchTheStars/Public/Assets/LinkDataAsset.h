// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LinkDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API ULinkDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor PrimaryColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor SuccessColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor BlockedColor;
};
