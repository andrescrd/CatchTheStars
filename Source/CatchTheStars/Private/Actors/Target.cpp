// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Target.h"

#include "Assets/TypeDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "UI/TypeWidget.h"

// Sets default values
ATarget::ATarget()
{
	Type = StarTypesEnum::A;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(128.f));
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	RootComponent = BoxComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TypeWidget"));
	WidgetComponent->SetRelativeRotation(FRotator(90,0,180));
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = false;
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
	if(auto Widget =  Cast<UTypeWidget>(WidgetComponent->GetWidget()))
		Widget->SetOwnParent(this);
	
	// if(TypeDataAsset)
		// StaticMeshComponent->SetStaticMesh(TypeDataAsset->GetTargetMesh(Type));	
}

void ATarget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(TypeWidgetClass)
		WidgetComponent->SetWidgetClass(TypeWidgetClass);
}

void ATarget::SetSelected(const bool Selected) { IsSelected = Selected; }

void ATarget::SetType(const StarTypesEnum NewType) { Type = NewType; }

StarTypesEnum ATarget::GetType() { return Type; }
