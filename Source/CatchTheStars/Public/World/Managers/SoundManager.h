// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SoundManager.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API USoundManager : public UObject
{
	GENERATED_BODY()

public:
	USoundManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float FXVolume;
};
