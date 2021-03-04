// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CGraph.h"
#include "CollisionDebugDrawingPublic.h"
#include "Actors/CNode.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "World/GameModes/CGameplayGameMode.h"
#include "NiagaraComponent.h"

const FName NiagaraParameterEnd = FName("BeamEnd");
	
// Sets default values
ACGraph::ACGraph()
{
	NodesCounter = 3;
	Links = TMap<FString, FLinkStruct>();

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

	for (auto Link : LinkMap) // add link and niagara
	{
		if (Links.Contains(Link.GetId()) || Links.Contains(Link.GetIdInverted()))
			continue;

		Links.Add(Link.GetId(), Link);
		AddNiagaraLink(Link.From->GetActorLocation(), Link.To->GetActorLocation());
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

void ACGraph::AddNiagaraLink(const FVector& FromVector, const FVector& ToVector) const
{
	if (!FXTemplate)
		return;

	UNiagaraComponent* Niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXTemplate, FromVector);
	Niagara->SetVectorParameter(NiagaraParameterEnd, ToVector);
}