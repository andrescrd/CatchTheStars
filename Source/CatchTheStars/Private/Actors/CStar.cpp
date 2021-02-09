// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CStar.h"
#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

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

	WidgetComponent =  CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetClass(UserWidgetClass);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->AddRelativeRotation(FRotator(90,0,0));
	WidgetComponent->InitWidget();
	WidgetComponent->SetupAttachment(RootComponent);	

	MovableComponent = CreateDefaultSubobject<UCMovableComponent>(TEXT("MovableComponent"));
	MovableComponent->SetAutoActivate(false);

	PrimaryActorTick.bCanEverTick = false;
}

void ACStar::BeginPlay()
{
	Super::BeginPlay();
}

void ACStar::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(WidgetComponent && UserWidgetClass)
		WidgetComponent->SetWidgetClass(UserWidgetClass);
}

void ACStar::SetSelected(const bool Selected)
{
	IsSelected = Selected;

	if (IsSelected)
		MovableComponent->Activate(true);
	else
		MovableComponent->Deactivate();
}

void ACStar::AddRelation(ACStar* Relation)
{
	if(Relation != this)
		Relations.AddUnique(Relation);
}
