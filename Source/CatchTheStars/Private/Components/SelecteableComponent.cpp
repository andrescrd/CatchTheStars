// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SelecteableComponent.h"

// Sets default values for this component's properties
USelecteableComponent::USelecteableComponent()
{
	bUseHeightlight = true;	
	PrimaryComponentTick.bCanEverTick = false;
}

void USelecteableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerMeshComponent)
		MainMaterial = OwnerMeshComponent->GetMaterial(MaterialIndex);

	if(bUseHeightlight)
	{
		 GetOwner()->OnBeginCursorOver.AddDynamic(this, &USelecteableComponent::OnCursorOverStartHandle);
		 GetOwner()->OnEndCursorOver.AddDynamic(this, &USelecteableComponent::OnCursorOverEndHandle);
	}
}

void USelecteableComponent::SetStaticMesh(UMeshComponent* Mesh)
{
	OwnerMeshComponent = Mesh;
}

void USelecteableComponent::OnSelected(const bool Selected)
{
	bIsSelected =Selected;  
	if (OwnerMeshComponent && SelectedMaterial)
		OwnerMeshComponent->SetMaterial(MaterialIndex, Selected ? SelectedMaterial : MainMaterial);
}

void USelecteableComponent::OnHeightLight(const bool Height)
{
	if (OwnerMeshComponent && HighlightMaterial && !bIsSelected)
		OwnerMeshComponent->SetMaterial(MaterialIndex, Height ? HighlightMaterial : MainMaterial);
}

void USelecteableComponent::OnCursorOverStartHandle(AActor* TouchedActor) { OnHeightLight(true); }

void USelecteableComponent::OnCursorOverEndHandle(AActor* TouchedActor) { OnHeightLight(false); }