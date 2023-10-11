
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionRough/Interfaces/SInterface.h"
#include "ItemChest.generated.h"

class UStaticMeshComponent;
UCLASS()
class ACTIONROUGH_API AItemChest : public AActor, public ISInterface
{
	GENERATED_BODY()
	void Interact_Implementation(APawn* InstigatorPawn);
public:	
	AItemChest();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere,Category="ChestAnimationDegree",meta = (AllowPrivateAccess = "true"))
	float TargetPitch;
};
