// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TypeInterface.h"
#include "Support/Enums/CStarTypesEnum.h"

#include "CStar.generated.h"

UCLASS()
class CATCHTHESTARS_API ACStar : public AActor, public ITypeInterface
{
	GENERATED_BODY()

public:
	ACStar();

protected:
	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly)
	class UCTypeWidget* CurrentWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCMovableComponent* MovableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector NewLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSelected;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	CStarTypesEnum Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UCTypeWidget> UserWidgetClass;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void SetSelected(bool Selected);
	
	// ITypeInterface implementation
	virtual void SetType(const CStarTypesEnum NewType) override;
	virtual CStarTypesEnum GetType() override;
	
	void SetNewLocation(const FVector& Vector);
};
