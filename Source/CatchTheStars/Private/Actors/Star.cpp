// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Star.h"

#include "Assets/TypeDataAsset.h"
#include "Components/BoxComponent.h"
#include "Components/MovableComponent.h"
#include "Components/SelecteableComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/TypeWidget.h"

// Sets default values
AStar::AStar()
{
	IsSelected = false;
	Type = EStarTypesEnum::A;
	Speed = 10;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(128.f));
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MovableComponent = CreateDefaultSubobject<UMovableComponent>(TEXT("MovableComponent"));
	MovableComponent->SetAutoActivate(false);

	SelectableComponent = CreateDefaultSubobject<USelecteableComponent>(TEXT("SelecteableComponent"));
	SelectableComponent->SetStaticMesh(MeshComponent);
	
	PrimaryActorTick.bCanEverTick = true;
}

void AStar::BeginPlay()
{
	Super::BeginPlay();

	if(TypeDataAsset)
		MeshComponent->SetStaticMesh(TypeDataAsset->GetStarMesh(Type));

	// SelectableComponent->SetStaticMesh(MeshComponent);
}

void AStar::Tick(float DeltaSeconds)
{
	if ((NewLocation - GetActorLocation()).Size() > 0 && !NewLocation.IsZero())
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewLocation, DeltaSeconds, Speed));
}

void AStar::SetSelected(const bool Selected)
{
	IsSelected = Selected;
	SelectableComponent->OnSelected(Selected);
}

void AStar::SetType(const EStarTypesEnum NewType) { Type=NewType; }

EStarTypesEnum AStar::GetType() { return Type; }

void AStar::SetNewLocation(const FVector& Vector)
{
	NewLocation = Vector;

	if(MoveStarSound)
		UGameplayStatics::PlaySound2D(this,MoveStarSound);

	// MeshComponent->GetRelativeLocation();
	// NewLocation.Z = MeshComponent->GetComponentLocation().Z;	
}