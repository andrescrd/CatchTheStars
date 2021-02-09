// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Support/Enums/CStarTypesEnum.h"

#include "CTarget.generated.h"

UCLASS()
class CATCHTHESTARS_API ACTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACTarget();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> UserWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	CStarTypesEnum Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;

	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	void SetType(const CStarTypesEnum NewType);
	void SetSelected(bool Selected);
};
