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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Setup)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Setup)
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Setup)
	class UWidgetComponent* WidgetComponent;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)	
	TSubclassOf<class UTypeWidget> TypeWidgetClass;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UTypeDataAsset* TypeDataAsset;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category=Setup)
	EStarTypesEnum Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category=Setup)
	bool IsSelected;

	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	void SetSelected(bool Selected);

	// ITypeInterface implementation
	virtual void SetType(const EStarTypesEnum NewType) override;
	virtual EStarTypesEnum GetType() override;
};
