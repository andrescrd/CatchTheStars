// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Support/Enums/StarTypesEnum.h"
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
	virtual void SetType(const StarTypesEnum NewType);
	virtual StarTypesEnum GetType();
};
