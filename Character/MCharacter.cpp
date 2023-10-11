#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MCharacter.h"
#include "../ReusableComponents/InteractionComponent.h"

// Sets default values
AMCharacter::AMCharacter() :
	BaseLookUpRate{ 45.f },
	BaseTurnRate{ 45.f }
{


	PrimaryActorTick.bCanEverTick = true;
	//SpringArm Sittings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector{ 0.0f,50.f ,50.f };

	//CameraComp Sittings
	FollowCamera= CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//InteractionComponentSetup
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComp");


	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	
}

void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation{0.f, Rotation.Yaw ,0.f};
		FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation{ 0.f, Rotation.Yaw ,0.f };
		FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);

	}
}

void AMCharacter::LookUp(float Value)
{
	AddControllerPitchInput(BaseLookUpRate * Value * GetWorld()->DeltaTimeSeconds);
}

void AMCharacter::TurnAt(float Value)
{
	AddControllerYawInput(BaseTurnRate * Value * GetWorld()->DeltaTimeSeconds);

}

void AMCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_02");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	
}

void AMCharacter::PrimaryInteract()
{
	if (InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}

void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Movement Binding
	PlayerInputComponent->BindAxis("MoveForward", this, &AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnAt", this, &AMCharacter::TurnAt);
	PlayerInputComponent->BindAxis("LookUp", this, &AMCharacter::LookUp);

	//Action Binding 
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMCharacter::PrimaryInteract);

}

