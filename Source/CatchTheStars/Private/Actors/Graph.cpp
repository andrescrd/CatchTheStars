// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Graph.h"
#include "CollisionDebugDrawingPublic.h"
#include "Actors/NodeGraph.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "World/GameModes/GameplayGameMode.h"

const FName NiagaraParameterEnd = FName("BeamEnd");

// Sets default values
AGraph::AGraph()
{
	bShowLinks = false;
	NodesCounter = 3;
	Links = TMap<FString, FLinkStruct>();

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PrimaryActorTick.bCanEverTick = false;
}

void AGraph::BeginPlay()
{
	Super::BeginPlay();

	for (auto Node : NodesSuccessMap)
	{
		if (IsValid(Node.Key))
		{
			Node.Key->OnSuccessAttached.AddDynamic(this, &AGraph::SuccessAttached); // bind to event
			NodesSuccessMap[Node.Key] = Node.Key->IsSuccessAttach(); // setup initial values

			if (Node.Key->HasStar())
				MaxSuccess++;

			if (NodesSuccessMap[Node.Key])
				CurrentSuccess++;

			SetupLinks(Node.Key);
		}
	}
}

void AGraph::SuccessAttached(const ANodeGraph* Node, const bool Success)
{
	NodesSuccessMap[Node] = Success;
	Success ? CurrentSuccess++ : CurrentSuccess--;

	if (CurrentSuccess == MaxSuccess)
		GetWorld()->GetAuthGameMode<AGameplayGameMode>()->Finish();
}

bool AGraph::IsAvailableLink(ANodeGraph* From, ANodeGraph* To)
{
	const FString Name = From->GetName() + To->GetName();
	const FString InvertedName = To->GetName() + From->GetName();
	return Links.Find(Name) || Links.Find(InvertedName);
}

void AGraph::GenerateGraph()
{
	for (auto It = NodesSuccessMap.CreateConstIterator(); It; ++It)
	{
		if (IsValid(It.Key()))
			It.Key()->Destroy();

		NodesSuccessMap.Remove(It.Key());
	}

	if (!NodeClass)
		return;

	for (int i = 0; i < NodesCounter; ++i)
	{
		AActor* ChildActor = GetWorld()->SpawnActor<ANodeGraph>(NodeClass, GetActorLocation(), FRotator::ZeroRotator,
		                                                        FActorSpawnParameters());
		ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		if (ANodeGraph* Node = Cast<ANodeGraph>(ChildActor))
			NodesSuccessMap.Add(Node, Node->IsSuccessAttach());
	}
}

void AGraph::SetupLinks(ANodeGraph* Node)
{
	auto NodeLinks = Node->GetLinks();

	FLinkStruct LinkStruct = FLinkStruct();
	LinkStruct.From = Node;

	for (auto NodeLink : NodeLinks)
	{
		LinkStruct.To = NodeLink;

		if (Links.Contains(LinkStruct.GetId()) || Links.Contains(LinkStruct.GetIdInverted()))
			continue;

		Links.Add(LinkStruct.GetId(), LinkStruct);
		AddNiagaraLink(LinkStruct.From->GetActorLocation(), LinkStruct.To->GetActorLocation());
	}
}

void AGraph::AddNiagaraLink(const FVector& FromVector, const FVector& ToVector) const
{
	if (!FXTemplate)
		return;

	UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXTemplate, FromVector);
	Niagara->SetVectorParameter(NiagaraParameterEnd, ToVector);
}

void AGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GEngine->Exec(GetWorld(),TEXT("flushpersistentdebuglines"));
	if (bShowLinks)
		ShowLinks();
}

void AGraph::ShowLinks()
{
	for (auto Node : NodesSuccessMap)
		if (IsValid(Node.Key)) Node.Key->ShowLinks();
}
