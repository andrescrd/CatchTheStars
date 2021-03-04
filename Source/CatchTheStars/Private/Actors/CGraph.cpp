// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CGraph.h"
#include "CollisionDebugDrawingPublic.h"
#include "Actors/CNode.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "World/GameModes/CGameplayGameMode.h"

// Sets default values
ACGraph::ACGraph()
{
	NodesCounter = 3;
	Links = TSet<FString>();
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PrimaryActorTick.bCanEverTick = false;
}

void ACGraph::BeginPlay()
{
	Super::BeginPlay();

	for (auto Node : NodesSuccessMap)
	{
		Node.Key->OnSuccessAttached.AddDynamic(this, &ACGraph::SuccessAttached); // bind to event
		NodesSuccessMap[Node.Key] = Node.Key->IsSuccessAttach(); // setup initial values

		if (Node.Key->HasStar())
			MaxSuccess++;

		if (NodesSuccessMap[Node.Key])
			CurrentSuccess++;
	}

	for (auto Link : LinkMap)
	{
		Links.Add(Link.GetId());
		Links.Add(Link.GetIdInverted());
	}
}

void ACGraph::SuccessAttached(const ACNode* Node, const bool Success)
{
	NodesSuccessMap[Node] = Success;
	Success ? CurrentSuccess++ : CurrentSuccess--;

	if (CurrentSuccess == MaxSuccess)
		GetWorld()->GetAuthGameMode<ACGameplayGameMode>()->Finish();
}


bool ACGraph::IsAvailableLink(ACNode* From, ACNode* To)
{
	const FString Name = From->GetName() + To->GetName();
	const FString InvertedName = To->GetName() + From->GetName();
	return Links.Find(Name) || Links.Find(InvertedName);
}

void ACGraph::GenerateGraph()
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
		AActor* ChildActor = GetWorld()->SpawnActor<ACNode>(NodeClass, GetActorLocation(), FRotator::ZeroRotator,
		                                                    FActorSpawnParameters());
		ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		if (ACNode* Node = Cast<ACNode>(ChildActor))
			NodesSuccessMap.Add(Node, Node->IsSuccessAttach());
	}
}

void ACGraph::GeneratePaths()
{
	while (Paths.Num() > 0)
	{
		if (UNiagaraComponent* Node = Paths.Pop())
			Node->DestroyComponent(true);
	}

	if (FXTemplate)
	{
		// for (int i = 0; i < Nodes.Num(); ++i)
		// {
		// 	ACNode* Node = Nodes[i];
		//
		//
		// 	const TArray<FVector> Locations = Node->GetRelationLocations();
		// 	for (int x = 0; x < Locations.Num(); ++x)
		// 	{
		// 		// UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXTemplate,  Node->GetStartLocation(), FRotator::ZeroRotator);
		// 		UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(FXTemplate, Node->GetRootComponent(), NAME_None,
		// 		                                                                          Node->GetStartLocation(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,
		// 		                                                                          true);
		// 		Niagara->SetRelativeLocation(FVector(0));
		// 		Niagara->AttachToComponent(Node->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		//
		// 		Niagara->SetVectorParameter(FName("BeamEnd"), Locations[x]);
		// 		Paths.AddUnique(Niagara);
		// 	}
		// }
	}
}
