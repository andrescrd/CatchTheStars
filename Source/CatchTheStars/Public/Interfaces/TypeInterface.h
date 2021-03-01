// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Support/Enums/CStarTypesEnum.h"
#include "UObject/Interface.h"
#include "TypeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTypeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CATCHTHESTARS_API ITypeInterface
{
	GENERATED_BODY()

public:
	void SetType(CStarTypesEnum NewType);
	CStarTypesEnum GetType();
};
