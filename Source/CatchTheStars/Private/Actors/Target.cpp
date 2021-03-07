// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Target.h"


#include "Assets/TypeDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"

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

	PrimaryActorTick.bCanEverTick = false;
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();

	// if(TypeDataAsset)
		// StaticMeshComponent->SetStaticMesh(TypeDataAsset->GetTargetMesh(Type));
}

void ATarget::SetSelected(const bool Selected) { IsSelected = Selected; }

void ATarget::SetType(const StarTypesEnum NewType) { Type = NewType; }

StarTypesEnum ATarget::GetType() { return Type; }
