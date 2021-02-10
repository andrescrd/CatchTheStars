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

// Called when the game starts or when spawned
void ACGraph::BeginPlay()
{
	Super::BeginPlay();
	GeneratePaths();
}

void ACGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACGraph::GenerateGraph()
{
	while (Nodes.Num() > 0)
	{
		ACNode* Node = Nodes.Pop();
		Node->Destroy(true);
	}

	if (NodeClass)
	{
		for (int i = 0; i < NodesCounter; ++i)
		{
			AActor* ChildActor = GetWorld()->SpawnActor<ACNode>(NodeClass, GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
			ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

			if (ChildActor)
			{
				ACNode* Node = Cast<ACNode>(ChildActor);
				Nodes.AddUnique(Node);
			}
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
		for (int i = 0; i < Nodes.Num(); ++i)
		{
			ACNode* Node = Nodes[i];


			const TArray<FVector> Locations = Node->GetRelationLocations();
			for (int x = 0; x < Locations.Num(); ++x)
			{
				// UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXTemplate,  Node->GetStartLocation(), FRotator::ZeroRotator);
				UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(FXTemplate, Node->GetRootComponent(), NAME_None,
				                                                                          Node->GetStartLocation(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,
				                                                                          true);
				Niagara->SetRelativeLocation(FVector(0));
				Niagara->AttachToComponent(Node->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

				Niagara->SetVectorParameter(FName("BeamEnd"), Locations[x]);
				Paths.AddUnique(Niagara);
			}
		}
	}
}
