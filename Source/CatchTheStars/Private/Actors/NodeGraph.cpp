// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/NodeGraph.h"


#include "DrawDebugHelpers.h"
#include "Actors/Star.h"
#include "Actors/Target.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

ANodeGraph::ANodeGraph()
{
	bHasStar = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	NiagaraSuccessAttach = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSuccessAttach"));
	NiagaraSuccessAttach->SetAutoActivate(false);
	NiagaraSuccessAttach->SetAsset(FXSuccessTemplate);
	NiagaraSuccessAttach->SetupAttachment(RootComponent);

	NiagaraBlocked = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraBlocked"));
	NiagaraBlocked->SetAutoActivate(false);
	NiagaraBlocked->SetAsset(FXBlockedTemplate);
	NiagaraBlocked->SetupAttachment(RootComponent);

	TargetChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("TargetComponent"));
	TargetChild->SetupAttachment(RootComponent);

	StarChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("StarComponent"));
	StarChild->SetRelativeLocation(FVector(0, 0, 150.f));
	StarChild->SetupAttachment(RootComponent);
}

ATarget* ANodeGraph::GetTarget() const { return Target; }

AStar* ANodeGraph::GetStar() const { return Star; }

TArray<FLinkStruct> ANodeGraph::GetLinks() const { return Links; }

FVector ANodeGraph::GetStarLocation() const { return StarChild->GetComponentLocation(); }

void ANodeGraph::ActivateNiagaraSuccessAttach(const bool Activate) const
{
	if(FXSuccessTemplate)
		Activate ? NiagaraSuccessAttach->Activate() : NiagaraSuccessAttach->Deactivate();
}

void ANodeGraph::PlayAttachSound() const
{
	if (AttachSound)
		UGameplayStatics::PlaySound2D(this, AttachSound);
}

void ANodeGraph::SetStar(AStar* NewStar)
{
	const bool WasSuccess = IsSuccessAttach();

	if (bHasStar && Star)
		return;

	NewStar->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	NewStar->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);

	Star = NewStar;
	bHasStar = true;

	NotifySuccessAttach(WasSuccess);

	if (IsSuccessAttach())
	{
		ActivateNiagaraSuccessAttach(true);
		PlayAttachSound();
	}
}

void ANodeGraph::RemoveStar()
{
	const bool WasSuccess = IsSuccessAttach();

	Star->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Star = nullptr;
	bHasStar = false;

	NotifySuccessAttach(WasSuccess);
	ActivateNiagaraSuccessAttach(IsSuccessAttach());
}

void ANodeGraph::SetIsKey(const bool IsKey) const
{
	if (FXBlockedTemplate)
		IsKey ? NiagaraBlocked->Activate() : NiagaraBlocked->Deactivate();
}

void ANodeGraph::NotifySuccessAttach(const bool WasSuccess) const
{
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
	SetupLinkStruct();
}

void ANodeGraph::SetupTarget()
{
	if (TargetChild && TargetClass)
	{
		TargetChild->SetChildActorClass(TargetClass);
		TargetChild->CreateChildActor();
		Target = Cast<ATarget>(TargetChild->GetChildActor());
		return;
	}

	RemoveChild(TargetChild);
}

void ANodeGraph::SetupStar()
{
	if (StarChild && StarClass && bHasStar)
	{
		StarChild->SetChildActorClass(StarClass);
		StarChild->CreateChildActor();
		Star = Cast<AStar>(StarChild->GetChildActor());
		return;
	}

	RemoveChild(StarChild);
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

void ANodeGraph::SetupLinkStruct()
{
	for (FLinkStruct& Link : Links)
	{
		if (!Link.From)
			Link.From = this;
	}
}

void ANodeGraph::ShowDebugLinks()
{
	for (const auto Link : Links)
	{
		if (!Link.To || !Link.From)
			continue;

		auto Color = Link.HasKey() ? FColor::Red : FColor::Green;
		DrawDebugLine(GetWorld(), GetActorLocation(), Link.To->GetStarLocation(), Color, true, 0, 0, 5);

		if (Link.HasKey())
			DrawDebugSphere(GetWorld(), Link.Key->GetActorLocation(), 128.f, 8, FColor::Red, true, 0, 0, 5);
	}
}
