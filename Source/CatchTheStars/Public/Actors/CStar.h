// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Support/Enums/CStarTypesEnum.h"

#include "CStar.generated.h"

UCLASS()
class CATCHTHESTARS_API ACStar : public AActor
{
	GENERATED_BODY()

public:
	ACStar();

protected:
	TArray<class ACStar*> Relations;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCMovableComponent* MovableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	CStarTypesEnum Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> UserWidgetClass;

	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	void SetSelected(bool Selected);
	void AddRelation(class ACStar* Relation);
};
