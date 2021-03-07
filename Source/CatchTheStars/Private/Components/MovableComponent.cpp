// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MovableComponent.h"

#include "Components/TimelineComponent.h"

// Sets default values for this component's properties
UMovableComponent::UMovableComponent()
{
	bAutoActivate = false;
	OffsetZ = 50;
	Time = FFloatRange::Inclusive(0.3,2);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	PrimaryComponentTick.bCanEverTick = false;
}

void UMovableComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupTimeline();

	if (bAutoActivate)
		PlayTimeline();

	InitialLocation = GetOwner()->GetActorLocation();
}

void UMovableComponent::SetupTimeline()
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

void UMovableComponent::GetNewLocation()
{
	if (AActor* Actor = GetOwner())
	{
		StartLocation = Actor->GetActorLocation();
		EndLocation = StartLocation;
		EndLocation.Z += OffsetZ;
		TimelineComponent->SetPlayRate( 1 / FMath::RandRange(Time.GetLowerBoundValue(), Time.GetUpperBoundValue()));
	}
}

void UMovableComponent::PlayTimeline()
{
	GetNewLocation();
	TimelineComponent->PlayFromStart();
}

void UMovableComponent::OnTimelineHandler(float Value)
{
	if (AActor* Actor = GetOwner())
		Actor->SetActorLocation(FMath::Lerp(StartLocation, EndLocation, Value), true);
}

void UMovableComponent::OnFinishHandler()
{
	if (TimelineComponent->GetPlaybackPosition() <= 0)
		TimelineComponent->PlayFromStart();
	else

		TimelineComponent->ReverseFromEnd();
}

void UMovableComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	PlayTimeline();
}

void UMovableComponent::Deactivate()
{
	Super::Deactivate();
	TimelineComponent->Deactivate();

	GetOwner()->SetActorLocation(InitialLocation);
}
