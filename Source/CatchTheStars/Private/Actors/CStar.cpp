// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CStar.h"

#include <iostream>


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

	PrimaryActorTick.bCanEverTick = false;
}

void ACStar::BeginPlay() { Super::BeginPlay(); }

void ACStar::NotifyActorBeginCursorOver()
{
	std::cout << "cursor is over ";
}

void ACStar::NotifyActorEndCursorOver()
{
	std::cout << "cursor is not over ";
}

void ACStar::SetSelected(const bool Selected)
{
	IsSelected = Selected;

	const FVector NewLocation = !IsSelected ? FVector(0, 0, -50) : FVector(0, 0, 50);
	AddActorLocalOffset(NewLocation, true);
}
