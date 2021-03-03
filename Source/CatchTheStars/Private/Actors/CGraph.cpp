// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CGraph.h"
#include "CollisionDebugDrawingPublic.h"
#include "Actors/CNode.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACGraph::ACGraph()
{
	NodesCounter = 3;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PrimaryActorTick.bCanEverTick = true;
}

void ACGraph::BeginPlay()
{
	Super::BeginPlay();

	for (auto Node : NodesSucessMap)
	{
		Node.Key->OnSuccessAttached.AddDynamic(this, &ACGraph::SuccessAttached);
		NodesSucessMap[Node.Key] = Node.Key->IsSuccessAttach();

		if (Node.Key->HasStar())
			MaxSuccess++;

		if(NodesSucessMap[Node.Key])
			CurrentSuccess++;
	}	
}

void ACGraph::SuccessAttached(const ACNode* Node, const bool Success)
{
	UE_LOG(LogTemp,Warning, TEXT("i am the node %s - success is: %s"), *Node->GetActorLabel(), Success ? TEXT("True"):TEXT("False"));
	NodesSucessMap[Node] = Success;

	if (Success)
	{
		CurrentSuccess++;
	}
	else
	{
		CurrentSuccess--;
	}	
	
	// CurrentSuccess = 0;
	// for (auto Node2 : NodesSucessMap)
	// {		
	// 	if(NodesSucessMap[Node2.Key])
	// 		CurrentSuccess++;
	// }	
}

void ACGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACGraph::GenerateGraph()
{	
	for (auto It = NodesSucessMap.CreateConstIterator(); It; ++It)
	{
		if(IsValid(It.Key()))
			It.Key()->Destroy();

		NodesSucessMap.Remove(It.Key());
	}
	
	if (!NodeClass)
		return;
	
	for (int i = 0; i < NodesCounter; ++i)
	{
		AActor* ChildActor = GetWorld()->SpawnActor<ACNode>(NodeClass, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
		ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		if (ACNode* Node = Cast<ACNode>(ChildActor))
		{
			// Node->OnSuccessAttached.AddDynamic(this, &ACGraph::SuccessAttached);
			NodesSucessMap.Add(Node,Node->IsSuccessAttach());
		}
	}
}

void ACGraph::GeneratePaths()
{
	while (Paths.Num() > 0)
	{
		if(UNiagaraComponent* Node = Paths.Pop())
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
