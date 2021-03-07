#pragma once

#include "Support/Enums/StarTypesEnum.h"
#include "NodeGraph.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSuccessAttachSignature, const class ANodeGraph*, Node, const bool, Success);

UCLASS()
class CATCHTHESTARS_API ANodeGraph : public AActor

{
	GENERATED_BODY()

public:
	ANodeGraph();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class ATarget* Target;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class AStar* Star;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* TargetChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* StarChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UNiagaraComponent* Niagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ATarget> TargetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class AStar> StarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	bool bHasStar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	StarTypesEnum TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	StarTypesEnum StarType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	TSet<class ANodeGraph*> Links;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UNiagaraSystem* FXTemplate;

	void RemoveChild(class UChildActorComponent* Child);
	void SetupType() const;
	void SetupTarget();
	void SetupStar();
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;	

	class ATarget* GetTarget() const;
	class AStar* GetStar() const;
	TSet<class ANodeGraph*> GetLinks() const;
	FVector GetStarLocation() const;	
	void SetStar(class AStar* NewStar);	
	bool IsSuccessAttach() const;
	bool HasStar() const;
	void RemoveStar();

	FSuccessAttachSignature OnSuccessAttached;

	UFUNCTION(CallInEditor, Category=Setup)
	void ShowLinks();
};
