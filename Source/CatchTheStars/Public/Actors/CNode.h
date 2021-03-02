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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class ACTarget* Target;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
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
	bool bHasStar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum StarType;

	virtual void BeginPlay() override;
	void SetupChildren();

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	ACTarget* GetTarget() const;
	ACStar* GetStar() const;
};
