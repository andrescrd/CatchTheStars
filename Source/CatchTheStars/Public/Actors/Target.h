// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TypeInterface.h"
#include "Support/Enums/StarTypesEnum.h"

#include "Target.generated.h"

UCLASS()
class CATCHTHESTARS_API ATarget : public AActor, public ITypeInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	StarTypesEnum Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;

	virtual void BeginPlay() override;

public:
	void SetSelected(bool Selected);

	// ITypeInterface implementation
	virtual void SetType(const StarTypesEnum NewType) override;
	virtual StarTypesEnum GetType() override;
};
