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
	NodesCounter = 3;
	Links = TMap<FString, FLinkStruct>();
	LinkMap = TArray<FLinkStruct>();

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PrimaryActorTick.bCanEverTick = false;
}

void AGraph::BeginPlay()
{
	Super::BeginPlay();

	for (auto Node : NodesSuccessMap)
	{
		if(IsValid(Node.Key))
		{
			Node.Key->OnSuccessAttached.AddDynamic(this, &AGraph::SuccessAttached); // bind to event
			NodesSuccessMap[Node.Key] = Node.Key->IsSuccessAttach(); // setup initial values

			if (Node.Key->HasStar())
				MaxSuccess++;

			if (NodesSuccessMap[Node.Key])
				CurrentSuccess++;
		}
	}

	for (auto Link : LinkMap) // add link and niagara
	{
		if (Links.Contains(Link.GetId()) || Links.Contains(Link.GetIdInverted()))
			continue;

		Links.Add(Link.GetId(), Link);
		AddNiagaraLink(Link.From->GetActorLocation(), Link.To->GetActorLocation());
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

void AGraph::AddNiagaraLink(const FVector& FromVector, const FVector& ToVector) const
{
	if (!FXTemplate)
		return;

	UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXTemplate, FromVector);
	Niagara->SetVectorParameter(NiagaraParameterEnd, ToVector);
}