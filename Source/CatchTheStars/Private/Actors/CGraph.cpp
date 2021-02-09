// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CGraph.h"
#include "Components/ChildActorComponent.h"
#include "Actors/CNode.h"

// Sets default values
ACGraph::ACGraph()
{
	NodesCounter = 3;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACGraph::BeginPlay()
{
	Super::BeginPlay();
}

void ACGraph::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (int i = 0; i < Nodes.Num(); ++i)
	{
	}		
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
			AActor* ChildActor = GetWorld()->SpawnActor<ACNode>(NodeClass,GetActorLocation(), FRotator::ZeroRotator,FActorSpawnParameters());
			ChildActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
			
			if (ChildActor)
			{
				ACNode* Node = Cast<ACNode>(ChildActor);			
				
				Nodes.AddUnique(Cast<ACNode>(ChildActor));
			}
		}
	}
}
