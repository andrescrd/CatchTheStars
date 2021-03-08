// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TypeInterface.h"
#include "Support/Enums/StarTypesEnum.h"
#include "TypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHESTARS_API UTypeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	StarTypesEnum CurrentType;
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ITypeInterface* OwnParent;

public:
	void SetOwnParent(ITypeInterface*  NewParent);

	UFUNCTION(BlueprintCallable)
	StarTypesEnum GetParentType() const;	
};
