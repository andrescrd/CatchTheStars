// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/CTarget.h"

#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/CTypeWidget.h"

// Sets default values
ACTarget::ACTarget()
{
	Type = CStarTypesEnum::A;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(128.f));
	RootComponent = BoxComponent;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	WidgetComponent =  CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetClass(UserWidgetClass);
	WidgetComponent->SetDrawAtDesiredSize(true);
	WidgetComponent->AddRelativeRotation(FRotator(90,0,0));
	WidgetComponent->InitWidget();
	WidgetComponent->SetupAttachment(RootComponent);	
	
	PrimaryActorTick.bCanEverTick = false;
}

void ACTarget::BeginPlay()
{
	Super::BeginPlay();
	CurrentWidget = Cast<UCTypeWidget>(WidgetComponent->GetWidget());
	if(CurrentWidget)
		CurrentWidget->SetOwnParent(this);
}

void ACTarget::SetSelected(const bool Selected) { IsSelected = Selected; }

void ACTarget::SetType(const CStarTypesEnum NewType) { Type = NewType; }

CStarTypesEnum ACTarget::GetType() { return Type; }
