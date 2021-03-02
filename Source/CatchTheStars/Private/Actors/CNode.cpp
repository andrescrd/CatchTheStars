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

void ACNode::BeginPlay() { Super::BeginPlay(); }

void ACNode::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetupChildren();
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

			if(Star)
				Star->Destroy();
		}
	}
}