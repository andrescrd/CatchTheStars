// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TypeInterface.h"
#include "Support/Enums/CStarTypesEnum.h"
#include "CTypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UCTypeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	CStarTypesEnum CurrentType;
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ITypeInterface* OwnParent;

public:
	void SetOwnParent(ITypeInterface*  NewParent);

	UFUNCTION(BlueprintCallable)
	CStarTypesEnum GetParentType();
};
