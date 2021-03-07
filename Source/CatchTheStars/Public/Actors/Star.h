// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/MovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TypeInterface.h"
#include "Support/Enums/StarTypesEnum.h"

#include "Star.generated.h"

UCLASS()
class CATCHTHESTARS_API AStar : public AActor, public ITypeInterface
{
	GENERATED_BODY()

public:
	AStar();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class USelecteableComponent* SelectableComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	class UMovableComponent* MovableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
	FVector NewLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Setup)
    bool IsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Setup)
	float Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UTypeDataAsset* TypeDataAsset;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Setup)
	StarTypesEnum Type;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	void SetSelected(bool Selected);
	
	// ITypeInterface implementation
	virtual void SetType(const StarTypesEnum NewType) override;
	virtual StarTypesEnum GetType() override;
	
	void SetNewLocation(const FVector& Vector);
};
