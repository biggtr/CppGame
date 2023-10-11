
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MCharacter.generated.h"

UCLASS()
class ACTIONROUGH_API AMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);	
	void TurnAt(float Value);
	void PrimaryAttack();
	void PrimaryInteract();
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "reusable", meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;


};
