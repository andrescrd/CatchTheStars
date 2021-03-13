// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Graph.h"


#include "CollisionDebugDrawingPublic.h"
#include "Actors/NodeGraph.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Assets/LinkDataAsset.h"
#include "World/GameModes/GameplayGameMode.h"

const FName NiagaraParameterEnd = FName("BeamEnd");
const FName NiagaraParameterColor = FName("ColorEnd");

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

	for (auto Node : NodesMap)
	{
		if (IsValid(Node.Key))
		{
			Node.Key->OnSuccessAttached.AddDynamic(this, &AGraph::SetSuccessAttached); // bind to event
			NodesMap[Node.Key] = Node.Key->IsSuccessAttach(); // setup initial values

			if (Node.Key->HasStar())
				MaxSuccess++;

			if (NodesMap[Node.Key])
				CurrentSuccess++;

			SetupLinks(Node.Key);
		}
	}
}

void AGraph::SetSuccessAttached(const ANodeGraph* Node, const bool Success)
{
	NodesMap[Node] = Success;
	Success ? CurrentSuccess++ : CurrentSuccess--;

	for (auto &Link : Links)
	{
		if(Link.Value.Key == nullptr || Link.Value.Key != Node)
			continue;
		
		Link.Value.Key->SetIsKey(false);
		Link.Value.Key = nullptr;
		Link.Value.NiagaraComponent->SetColorParameter(NiagaraParameterColor, LinkDataAsset->PrimaryColor);
	}

	if (CurrentSuccess == MaxSuccess)
	{
		ShowSuccessLinks();
		GetWorld()->GetAuthGameMode<AGameplayGameMode>()->LevelComplete();
	}
}

bool AGraph::IsAvailableLink(ANodeGraph* From, ANodeGraph* To)
{
	const FString Name = From->GetName() + To->GetName();
	const FString InvertedName = To->GetName() + From->GetName();

	return (Links.Find(Name) && !Links.Find(Name)->IsBlocked()) ||
		(Links.Find(InvertedName) && !Links.Find(InvertedName)->IsBlocked());
}

void AGraph::SetupLinks(ANodeGraph* Node)
{
	if (!LinkDataAsset)
		return;

	auto NodeLinks = Node->GetLinks();

	for (FLinkStruct NodeLink : NodeLinks)
	{
		if (Links.Contains(NodeLink.GetId()) || Links.Contains(NodeLink.GetIdInverted()))
			continue;

		auto CurrentLinkNiagara = GetNiagaraForLink(NodeLink.From->GetActorLocation(),
		                                            NodeLink.To->GetActorLocation());

		const auto Color = NodeLink.IsBlocked() ? LinkDataAsset->BlockedColor : LinkDataAsset->PrimaryColor;

		if(NodeLink.HasKey())
			NodeLink.Key->SetIsKey(true);
		
		CurrentLinkNiagara->SetColorParameter(NiagaraParameterColor, Color);
		NodeLink.NiagaraComponent = CurrentLinkNiagara;

		Links.Add(NodeLink.GetId(), NodeLink);
	}
}

UNiagaraComponent* AGraph::GetNiagaraForLink(const FVector From, const FVector To) const
{
	if (!FXTemplate)
		return nullptr;

	UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXTemplate, From);
	Niagara->SetVectorParameter(NiagaraParameterEnd, To);

	return Niagara;
}

void AGraph::ShowSuccessLinks() const
{
	for (auto It = Links.CreateConstIterator(); It; ++It)
	{
		if (It.Value().NiagaraComponent == nullptr)
			continue;

		if (!It.Value().From->HasStar() || !It.Value().To->HasStar())
			It.Value().NiagaraComponent->Deactivate();
		else
			It.Value().NiagaraComponent->SetColorParameter(NiagaraParameterColor, LinkDataAsset->SuccessColor);
	}
}

void AGraph::AttachStarToTarget(AStar* Star, ATarget* Target)
{
	ANodeGraph* ParentTarget = Cast<ANodeGraph>(Target->GetAttachParentActor());
	ANodeGraph* ParentStar = Cast<ANodeGraph>(Star->GetAttachParentActor());
	
	if (ParentTarget == ParentStar || ParentTarget->HasStar())
		return;

	if(!IsAvailableLink(ParentStar, ParentTarget)) // validate if graph  has valid link
		return;	
		
	ParentStar->RemoveStar();
	ParentTarget->SetStar(Star);
	
	Star->SetSelected(false);
	Star->SetNewLocation(ParentTarget->GetStarLocation());
}

void AGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	if (GEngine)
	{
		GEngine->Exec(GetWorld(),TEXT("flushpersistentdebuglines")); // exec command to clean debug lines on editor
	}

	if (bShowLinks == true)
	{
		ShowDebugLinks();
	}
#endif
}

void AGraph::BeginDestroy()
{
	Super::BeginDestroy();

	for (auto It = Links.CreateConstIterator(); It; ++It)
	{
		if (It.Value().NiagaraComponent)
			It.Value().NiagaraComponent->DestroyInstance();

		Links.Remove(It.Key());
	}
}

// ****************************************************
// EDITOR
void AGraph::ShowDebugLinks()
{
	for (auto Node : NodesMap)
		if (IsValid(Node.Key)) Node.Key->ShowDebugLinks();
}

void AGraph::AddSingleNode()
{
	if (!NodeClass)
		return;

	const auto Node = CreateNewNode();
	NodesMap.Add(Node, Node->IsSuccessAttach());
	NodesCounter++;
}

void AGraph::GenerateGraph()
{
	CleanNodeMap();

	if (!NodeClass)
		return;

	for (int i = 0; i < NodesCounter; ++i)
	{
		const auto Node = CreateNewNode();
		NodesMap.Add(Node, Node->IsSuccessAttach());
	}
}

void AGraph::CleanNodeMap()
{
	for (auto It = NodesMap.CreateConstIterator(); It; ++It)
	{
		if (IsValid(It.Key()))
			It.Key()->Destroy();

		NodesMap.Remove(It.Key());
	}
}

ANodeGraph* AGraph::CreateNewNode()
{
	AActor* ChildActor = GetWorld()->SpawnActor<ANodeGraph>(NodeClass, GetActorLocation(), FRotator::ZeroRotator,
	                                                        FActorSpawnParameters());
	ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	return Cast<ANodeGraph>(ChildActor);
}
