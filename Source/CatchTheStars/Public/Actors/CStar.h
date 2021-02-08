// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCMovableComponent* MovableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	CStarTypesEnum Type;
	

	void SetupTimeline();
	virtual void BeginPlay() override;

public:
	void SetSelected(bool Selected);
};
