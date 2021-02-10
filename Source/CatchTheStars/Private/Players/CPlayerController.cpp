// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/CPlayerController.h"

#include "Actors/CNode.h"
#include "Actors/CStar.h"
#include "Actors/CTarget.h"
#include "Characters/CCharacter.h"
#include "Kismet/GameplayStatics.h"

const FName ActionName = "Selection";

ACPlayerController::ACPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(ActionName, IE_Pressed, this, &ACPlayerController::OnSelectionStart);
	InputComponent->BindAction(ActionName, IE_Released, this, &ACPlayerController::OnSelectionEnd);
}

ACCharacter* ACPlayerController::GetCurrentCharacter()
{
	if (!IsValid(CurrentCharacter))
	{
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACCharacter::StaticClass()))
			CurrentCharacter = Cast<ACCharacter>(Actor);
	}

	return CurrentCharacter;
}

void ACPlayerController::OnSelectionStart()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);
	
	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACStar::StaticClass()))
	{		
		if (SelectedStar != nullptr && SelectedStar != HitResult.GetActor())
			SelectedStar->SetSelected(false);
	
		SelectedStar = Cast<ACStar>(HitResult.GetActor());
		SelectedStar->SetSelected(true);
	
		GetCurrentCharacter()->MoveToDestination(SelectedStar->GetActorLocation());
		
		GEngine->AddOnScreenDebugMessage(0,3,FColor::Green, FString::Printf(TEXT("Have a Star")));
	}
	else if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACTarget::StaticClass()))
	{
		if(SelectedStar && SelectedStar->GetParentActor() != HitResult.GetActor()->GetParentActor())
		{
			if (SelectedTarget != nullptr && SelectedTarget != HitResult.GetActor())
				SelectedTarget->SetSelected(false);

			SelectedTarget = Cast<ACTarget>(HitResult.GetActor());
			SelectedTarget->SetSelected(true);

			GEngine->AddOnScreenDebugMessage(0,3,FColor::Green, FString::Printf(TEXT("Have a Target")));

			FVector NewLocation = SelectedTarget->GetActorLocation();
			NewLocation.Z = SelectedStar->GetActorLocation().Z;
			SelectedStar->SetSelected(false);
			SelectedStar->SetActorLocation(NewLocation);

			ACNode* Node = Cast<ACNode>(SelectedTarget->GetParentActor());
			Node->AddStar(SelectedStar);
		}
	}
}

void ACPlayerController::OnSelectionEnd()
{
	// if(SelectedStar)
	// {
	// 	SelectedStar->SetSelected(false);
	// 	SelectedStar= nullptr;
	// }
}
