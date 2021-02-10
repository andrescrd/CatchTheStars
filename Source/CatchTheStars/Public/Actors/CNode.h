#pragma once

#include "NiagaraComponent.h"
#include "Support/Enums/CStarTypesEnum.h"

#include "CNode.generated.h"

UCLASS()
class CATCHTHESTARS_API ACNode : public AActor

{
	GENERATED_BODY()

public:
	ACNode();

protected:
	class ACTarget* Target;
	class ACStar* Star;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* TargetChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* StarChild;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ACTarget> TargetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ACStar> StarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	TArray<class ACNode*> Relations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	bool bHasStar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum StarType;
	
	virtual void BeginPlay() override;
	void DisplayStar();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void SetTargetType(const CStarTypesEnum Type);
	void AddRelation(class ACNode* Relation);

	FVector GetStartLocation() const;
	TArray<FVector> GetRelationLocations();
};
