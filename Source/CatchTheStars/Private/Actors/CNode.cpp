// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CNode.h"
#include "Actors/CStar.h"
#include "Actors/CTarget.h"
#include "NiagaraComponent.h"

ACNode::ACNode()
{
	bHasStar = true;
	Relations = TArray<ACNode*>(); 

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	TargetChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("TargetComponent"));
	TargetChild->SetupAttachment(RootComponent);
	StarChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("StarComponent"));
	StarChild->SetRelativeLocation(FVector(0, 0, 150.f));
	StarChild->SetupAttachment(RootComponent);	
}

void ACNode::BeginPlay()
{
	Super::BeginPlay();
	DisplayStar();
}

void ACNode::DisplayStar()
{
	if (bHasStar)
	{
		StarChild->CreateChildActor();
		Star = Cast<ACStar>(StarChild->GetChildActor());
	}
	else
	{
		if (StarChild->GetChildActor())
		{
			StarChild->DestroyChildActor();
			Star = nullptr;
		}
	}
}

void ACNode::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (TargetChild && TargetClass)
	{
		TargetChild->SetChildActorClass(TargetClass);
		TargetChild->CreateChildActor();
		Target = Cast<ACTarget>(TargetChild->GetChildActor());
	}

	if (StarChild && StarClass)
	{
		StarChild->SetChildActorClass(StarClass);
		DisplayStar();
	}	
}

#if WITH_EDITOR
void ACNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	DisplayStar();
}
#endif

void ACNode::SetTargetType(const CStarTypesEnum Type) const
{
	if (Target)
		Target->SetType(Type);
}

void ACNode::AddRelation(ACNode* Relation)
{
	if (Relation != this)
		Relations.AddUnique(Relation);	
}

void ACNode::AddStar(ACStar* NewStar)
{
	if(StarChild && StarChild->GetChildActor())
	{
		USceneComponent* CurrentStarChild = StarChild->GetChildActor()->GetRootComponent();
		CurrentStarChild->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,false));
	}

	USceneComponent* ChildRoot = NewStar->GetRootComponent();
	ChildRoot->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,false));
	ChildRoot->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

FVector ACNode::GetStartLocation() const { return Target ? Target->GetActorLocation() : FVector::ZeroVector; }

TArray<FVector> ACNode::GetRelationLocations()
{
	TArray<FVector> Locations;

	for (int i = 0; i < Relations.Num(); ++i)
		Locations.AddUnique(Relations[i]->GetActorLocation());

	return Locations;
}

ACTarget* ACNode::GetTarget() const { return Target; }

ACStar* ACNode::GetStar() const { return Star; }
