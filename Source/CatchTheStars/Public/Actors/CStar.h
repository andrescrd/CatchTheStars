// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
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
	bool IsSelected;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	CStarTypesEnum Type;


	virtual void BeginPlay() override;

public:

	virtual void NotifyActorBeginCursorOver() override;
	virtual  void NotifyActorEndCursorOver() override;
};
