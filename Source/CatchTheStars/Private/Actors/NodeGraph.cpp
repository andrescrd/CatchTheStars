// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/NodeGraph.h"

#include "Actors/Star.h"
#include "Actors/Target.h"
#include "NiagaraComponent.h"

ANodeGraph::ANodeGraph()
{
	bHasStar = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	TargetChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("TargetComponent"));
	TargetChild->SetupAttachment(RootComponent);

	StarChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("StarComponent"));
	StarChild->SetRelativeLocation(FVector(0, 0, 150.f));
	StarChild->SetupAttachment(RootComponent);
}

ATarget* ANodeGraph::GetTarget() const { return Target; }

AStar* ANodeGraph::GetStar() const { return Star; }

FVector ANodeGraph::	GetStarLocation() const { return StarChild->GetComponentLocation(); }

void ANodeGraph::SetStar(AStar* NewStar)
{
	const bool WasSuccess = IsSuccessAttach();

	if (bHasStar && Star)
		return;

	NewStar->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	NewStar->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

	Star = NewStar;
	bHasStar = true;

	if (WasSuccess && !IsSuccessAttach()) // notify if it was success or not
		OnSuccessAttached.Broadcast(this, false);
	else if (!WasSuccess && IsSuccessAttach())
		OnSuccessAttached.Broadcast(this, true);
}

void ANodeGraph::RemoveStar()
{
	const bool WasSuccess = IsSuccessAttach();

	Star->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Star = nullptr;
	bHasStar = false;

	if (WasSuccess && !IsSuccessAttach()) // notify if it was success or not
		OnSuccessAttached.Broadcast(this, false);
	else if (!WasSuccess && IsSuccessAttach())
		OnSuccessAttached.Broadcast(this, true);
}

bool ANodeGraph::IsSuccessAttach() const { return (Star && Target) && (Star->GetType() == Target->GetType()); }

bool ANodeGraph::HasStar() const { return bHasStar && Star; }

void ANodeGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupTarget();
	SetupStar();
	SetupType();
}

void ANodeGraph::SetupTarget()
{
	if (TargetChild && TargetClass)
	{
		TargetChild->SetChildActorClass(TargetClass);
		TargetChild->CreateChildActor();
		Target = Cast<ATarget>(TargetChild->GetChildActor());
	}
	else
	{
		RemoveChild(TargetChild);
	}
}

void ANodeGraph::SetupStar()
{
	if (StarChild && StarClass)
	{
		if (bHasStar)
		{
			StarChild->SetChildActorClass(StarClass);
			StarChild->CreateChildActor();
			Star = Cast<AStar>(StarChild->GetChildActor());
		}
		else
		{
			RemoveChild(StarChild);;
		}
	}
	else
	{
		RemoveChild(StarChild);
	}
}

void ANodeGraph::SetupType() const
{
	if (IsValid(Star))
		Star->SetType(StarType);

	if (IsValid(Target))
		Target->SetType(TargetType);
}

void ANodeGraph::RemoveChild(UChildActorComponent* Child)
{
	Child->SetChildActorClass(nullptr);
	Child->DestroyChildActor();
}