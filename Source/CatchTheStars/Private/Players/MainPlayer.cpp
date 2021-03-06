// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/MainPlayer.h"


#include "Actors/Graph.h"
#include "Actors/NodeGraph.h"
#include "Actors/Star.h"
#include "Actors/Target.h"
#include "Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

const FName ActionName = "Selection";

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
	InputComponent->BindAction(ActionName, IE_Pressed, this, &AMainPlayer::OnSelected);
}

AMainCharacter* AMainPlayer::GetCurrentCharacter()
{
	if (!IsValid(CurrentCharacter))
	{
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMainCharacter::StaticClass()))
			CurrentCharacter = Cast<AMainCharacter>(Actor);
	}

	return CurrentCharacter;
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

	MoveCharacterTo(SelectedStar->GetActorLocation()); // move character to star location
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
	
	MoveCharacterTo(SelectedTarget->GetActorLocation()); // move character to target location
	
	ParentStar->RemoveStar();
	ParentTarget->SetStar(SelectedStar);
	
	// SelectedStar->SetSelected(false);
	SelectedStar->SetNewLocation(SelectedTarget->GetActorLocation());

	SelectedTarget = nullptr;
	SelectedStar = nullptr;
}

void AMainPlayer::MoveCharacterTo(const FVector Location) { GetCurrentCharacter() ? GetCurrentCharacter()->MoveToDestination(Location) : NULL; }
