// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelecteableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATCHTHESTARS_API USelecteableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USelecteableComponent();

protected:

	UPROPERTY(VisibleInstanceOnly)
	bool bIsSelected;
	UPROPERTY(VisibleInstanceOnly)
	class UMeshComponent* OwnerMeshComponent;
	UPROPERTY(VisibleInstanceOnly)
	class UMaterialInterface* MainMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaterialIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMaterialInterface* SelectedMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UMaterialInterface* HighlightMaterial;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseHighlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USoundBase* HeightLightSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USoundBase* SelectedSound;

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void SetStaticMesh(class UMeshComponent* Mesh);
	UFUNCTION(BlueprintCallable)
	void OnSelected(const bool Selected);
	UFUNCTION(BlueprintCallable)
	void OnHeightLight(const bool Height);

	UFUNCTION()
	void OnCursorOverStartHandle(class AActor* TouchedActor);
	UFUNCTION()
	void OnCursorOverEndHandle(class AActor* TouchedActor);
};
