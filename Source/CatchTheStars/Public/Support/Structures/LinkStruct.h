// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "LinkStruct.generated.h"

USTRUCT(BlueprintType)
struct FLinkStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	class ANodeGraph* From;
	UPROPERTY(BlueprintReadWrite)
	class ANodeGraph* To;

	FString GetId() const;
	FString GetIdInverted() const;
};
