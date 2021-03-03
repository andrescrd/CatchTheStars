// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CNode.h"

#include "Actors/CStar.h"
#include "Actors/CTarget.h"
#include "NiagaraComponent.h"

ACNode::ACNode()
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

ACTarget* ACNode::GetTarget() const { return Target; }

ACStar* ACNode::GetStar() const { return Star; }

void ACNode::SetStar(ACStar* NewStar)
{
	const bool WasSuccess = IsSuccessAttach();

	if (bHasStar && Star)
		return;

	NewStar->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	NewStar->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

	Star = NewStar;
	bHasStar = true;

	// notify if it was success or not
	if (WasSuccess && !IsSuccessAttach())
	{
		OnSuccessAttached.Broadcast(this, false);
	}
	else if (!WasSuccess && IsSuccessAttach())
	{
		OnSuccessAttached.Broadcast(this, true);
	}
}

void ACNode::RemoveStar()
{
	const bool WasSuccess = IsSuccessAttach();

	Star->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Star = nullptr;
	bHasStar = false;

	// notify if it was success or not
	if (WasSuccess && !IsSuccessAttach())
	{
		OnSuccessAttached.Broadcast(this, false);
	}
	else if (!WasSuccess && IsSuccessAttach())
	{
		OnSuccessAttached.Broadcast(this, true);
	}
}

bool ACNode::IsSuccessAttach() const { return (Star && Target) && (Star->GetType() == Target->GetType()); }

bool ACNode::HasStar() const { return bHasStar && Star; }

void ACNode::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetupChildren();
	SetupType();
}

void ACNode::SetupChildren()
{
	if (TargetChild && TargetClass)
	{
		TargetChild->SetChildActorClass(TargetClass);
		TargetChild->CreateChildActor();
		Target = Cast<ACTarget>(TargetChild->GetChildActor());
	}

	if (StarChild && StarClass)
	{
		if (bHasStar)
		{
			StarChild->SetChildActorClass(StarClass);
			StarChild->CreateChildActor();
			Star = Cast<ACStar>(StarChild->GetChildActor());
		}
		else
		{
			StarChild->SetChildActorClass(nullptr);
			StarChild->DestroyChildActor();

			if (Star)
				Star->Destroy();
		}
	}
}

void ACNode::SetupType() const
{
	if (IsValid(Star))
		Star->SetType(StarType);

	if (IsValid(Target))
		Target->SetType(TargetType);
}
