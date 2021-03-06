﻿// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "LinkStruct.generated.h"

USTRUCT(BlueprintType)
struct FLinkStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	class ANodeGraph* From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ANodeGraph* To;	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ANodeGraph* Key;
	UPROPERTY(BlueprintReadOnly)
	class UNiagaraComponent* NiagaraComponent;

	FString GetId() const;
	FString GetIdInverted() const;
	bool HasKey() const;
	bool IsBlocked() const;

	FLinkStruct(): From(nullptr), To(nullptr), Key(nullptr), NiagaraComponent(nullptr)
	{
	}
};
