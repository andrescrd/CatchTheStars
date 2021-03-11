// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/MainPlayer.h"


#include "Actors/Graph.h"
#include "Actors/NodeGraph.h"
#include "Actors/Star.h"
#include "Actors/Target.h"
#include "Kismet/GameplayStatics.h"

const FName SelectActionName = "Selection";

AMainPlayer::AMainPlayer()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMainPlayer::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(SelectActionName, IE_Pressed, this, &AMainPlayer::OnSelected);
}

AGraph* AMainPlayer::GetCurrentGraph()
{
	if (!IsValid(CurrentGraph))
	{
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AGraph::StaticClass()))
			CurrentGraph = Cast<AGraph>(Actor);
	}

	return CurrentGraph;
}

void AMainPlayer::OnSelected()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);

	if(HitResult.GetActor())
		GEngine->AddOnScreenDebugMessage(1,3,FColor::Green,FString::Printf(TEXT("Actor: %s"), *HitResult.GetActor()->GetName()));
	
	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(AStar::StaticClass()))
	{
		AStar* Star = Cast<AStar>(HitResult.GetActor());
		SetSelectedStar(Star);
	}
	else if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ATarget::StaticClass()) && SelectedStar != nullptr)
	{
		ATarget* Target = Cast<ATarget>(HitResult.GetActor());
		SetSelectedTarget(Target);
	}
	else
	{
		if (SelectedStar)
			SelectedStar->SetSelected(false);

		if (SelectedTarget)
			SelectedTarget->SetSelected(false);

		SelectedStar = nullptr;
		SelectedTarget = nullptr;
	}
}

void AMainPlayer::SetSelectedStar(AStar* Star)
{
	if (SelectedStar != nullptr && SelectedStar != Star)
		SelectedStar->SetSelected(false);

	SelectedStar = Star;
	SelectedStar->SetSelected(true);
}

void AMainPlayer::SetSelectedTarget(ATarget* Target)
{
	if (SelectedTarget != nullptr && SelectedTarget != Target)
		SelectedTarget->SetSelected(false);

	SelectedTarget = Target;
	SelectedTarget->SetSelected(true);

	ANodeGraph* ParentTarget = Cast<ANodeGraph>(SelectedTarget->GetAttachParentActor());
	ANodeGraph* ParentStar = Cast<ANodeGraph>(SelectedStar->GetAttachParentActor());
	
	if (ParentTarget == ParentStar || ParentTarget->HasStar())
		return;

	if(!GetCurrentGraph()->IsAvailableLink(ParentStar, ParentTarget)) // validate if graph  has valid link
		return;
		
	ParentStar->RemoveStar();
	ParentTarget->SetStar(SelectedStar);
	
	SelectedStar->SetSelected(false);
	SelectedStar->SetNewLocation(ParentTarget->GetStarLocation());

	SelectedTarget = nullptr;
	SelectedStar = nullptr;
}