// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CStar.h"
#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACStar::ACStar()
{
	IsSelected = false;
	Type = CStarTypesEnum::A;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(128.f);
	SphereComponent->SetupAttachment(RootComponent);

	MovableComponent = CreateDefaultSubobject<UCMovableComponent>(TEXT("MovableComponent"));
	MovableComponent->SetAutoActivate(false);

	PrimaryActorTick.bCanEverTick = false;
}

void ACStar::BeginPlay()
{
	Super::BeginPlay();
}

void ACStar::SetSelected(const bool Selected)
{
	IsSelected = Selected;

	if (IsSelected)
		MovableComponent->Activate(true);
	else
		MovableComponent->Deactivate();
}
