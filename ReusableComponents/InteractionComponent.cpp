// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "../Interfaces/SInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FHitResult OutHit;

	AActor* MyCharacter = GetOwner();

	FVector EyeLocation;

	FRotator EyeRotation;

	FVector End = EyeLocation + (EyeRotation.Vector() * 500);

	MyCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	GetWorld()->LineTraceSingleByObjectType(OutHit, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = OutHit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<USInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyCharacter);
			ISInterface::Execute_Interact(HitActor, MyPawn);
		}
	}

}