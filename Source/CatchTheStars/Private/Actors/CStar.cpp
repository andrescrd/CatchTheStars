// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CStar.h"

#include "Components/CMovableComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/CTypeWidget.h"

// Sets default values
ACStar::ACStar()
{
	IsSelected = false;
	Type = CStarTypesEnum::A;
	Speed = 10;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(128.f);
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetClass(UserWidgetClass);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->AddRelativeRotation(FRotator(90, 0, 0));
	WidgetComponent->InitWidget();
	WidgetComponent->SetupAttachment(RootComponent);

	MovableComponent = CreateDefaultSubobject<UCMovableComponent>(TEXT("MovableComponent"));
	MovableComponent->SetAutoActivate(false);

	PrimaryActorTick.bCanEverTick = true;
}

void ACStar::BeginPlay()
{
	Super::BeginPlay();
	CurrentWidget = Cast<UCTypeWidget>(WidgetComponent->GetWidget());
	if(CurrentWidget)
		CurrentWidget->SetOwnParent(this);
}

void ACStar::Tick(float DeltaSeconds)
{
	if ((NewLocation - GetActorLocation()).Size() > 0 && !NewLocation.IsZero())
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewLocation, DeltaSeconds, Speed));
}

void ACStar::SetSelected(const bool Selected) { IsSelected = Selected; }

void ACStar::SetType(const CStarTypesEnum NewType) { Type=NewType; }

CStarTypesEnum ACStar::GetType() { return Type; }

void ACStar::SetNewLocation(const FVector& Vector)
{
	NewLocation = Vector;
	NewLocation.Z = MeshComponent->GetComponentLocation().Z;
}
