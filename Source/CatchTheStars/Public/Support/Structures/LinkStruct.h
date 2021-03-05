// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Actors/NodeGraph.h"
#include "LinkStruct.generated.h"

USTRUCT(BlueprintType)
struct FLinkStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANodeGraph* From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANodeGraph* To;

	FString GetId() const { return From->GetName() + To->GetName(); }
	FString GetIdInverted() const { return To->GetName() + From->GetName(); }
};
