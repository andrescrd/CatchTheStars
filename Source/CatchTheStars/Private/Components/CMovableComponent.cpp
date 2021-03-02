// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CMovableComponent.h"

#include "Components/TimelineComponent.h"

// Sets default values for this component's properties
UCMovableComponent::UCMovableComponent()
{
	bAutoActivate = false;
	OffsetZ = 50;
	Time = FFloatRange::Inclusive(0.3,2);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	PrimaryComponentTick.bCanEverTick = false;
}

void UCMovableComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();

	if (bAutoActivate)
		PlayTimeline();

	InitialLocation = GetOwner()->GetActorLocation();
}

void UCMovableComponent::SetupTimeline()
{
	if (!Curve)
		return;
	
	FOnTimelineFloat TimelineCallback;
	TimelineCallback.BindUFunction(this, FName("OnTimelineHandler"));
	FOnTimelineEventStatic FinishCallback;
	FinishCallback.BindUFunction(this, FName("OnFinishHandler"));

	TimelineComponent->AddInterpFloat(Curve, TimelineCallback);
	TimelineComponent->SetTimelineFinishedFunc(FinishCallback);

	TimelineComponent->SetLooping(false);
	TimelineComponent->SetIgnoreTimeDilation(true);
}

void UCMovableComponent::GetNewLocation()
{
	if (AActor* Actor = GetOwner())
	{
		StartLocation = Actor->GetActorLocation();
		EndLocation = StartLocation;
		EndLocation.Z += OffsetZ;
		TimelineComponent->SetPlayRate( 1 / FMath::RandRange(Time.GetLowerBoundValue(), Time.GetUpperBoundValue()));
	}
}

void UCMovableComponent::PlayTimeline()
{
	GetNewLocation();
	TimelineComponent->PlayFromStart();
}

void UCMovableComponent::OnTimelineHandler(float Value)
{
	if (AActor* Actor = GetOwner())
		Actor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value), true);
}

void UCMovableComponent::OnFinishHandler()
{
	if (TimelineComponent->GetPlaybackPosition() <= 0)
		TimelineComponent->PlayFromStart();
	else

		TimelineComponent->ReverseFromEnd();
}

void UCMovableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PlayTimeline();
}

void UCMovableComponent::Deactivate()
{
	Super::Deactivate();
	TimelineComponent->Deactivate();

	GetOwner()->SetActorLocation(InitialLocation);
}
