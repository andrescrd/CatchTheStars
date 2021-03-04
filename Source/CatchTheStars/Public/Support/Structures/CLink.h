// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Actors/CNode.h"
#include "CLink.generated.h"

USTRUCT(BlueprintType)
struct FLinkStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACNode* From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACNode* To;

	FString GetId() const { return From->GetName() + To->GetName(); }
	FString GetIdInverted() const { return To->GetName() + From->GetName(); }
};
