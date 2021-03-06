// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Star.h"

#include "Assets/TypeDataAsset.h"
#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/TypeWidget.h"

// Sets default values
AStar::AStar()
{
	IsSelected = false;
	Type = StarTypesEnum::A;
	Speed = 10;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(128.f);
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	MovableComponent = CreateDefaultSubobject<UCMovableComponent>(TEXT("MovableComponent"));
	MovableComponent->SetAutoActivate(false);

	PrimaryActorTick.bCanEverTick = true;
}

void AStar::BeginPlay()
{
	Super::BeginPlay();

	if(TypeDataAsset)
		MeshComponent->SetStaticMesh(TypeDataAsset->GetStarMesh(Type));
}

void AStar::Tick(float DeltaSeconds)
{
	if ((NewLocation - GetActorLocation()).Size() > 0 && !NewLocation.IsZero())
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewLocation, DeltaSeconds, Speed));
}

void AStar::SetSelected(const bool Selected) { IsSelected = Selected; }

void AStar::SetType(const StarTypesEnum NewType) { Type=NewType; }

StarTypesEnum AStar::GetType() { return Type; }

void AStar::SetNewLocation(const FVector& Vector)
{
	NewLocation = Vector;
	NewLocation.Z = MeshComponent->GetComponentLocation().Z;
}
