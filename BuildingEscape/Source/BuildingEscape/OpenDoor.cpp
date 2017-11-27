// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{								
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));									//Use the inbuilt function SetActorRotation
}

void UOpenDoor::CloseDoor()
{												
	Owner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));									//Use the inbuilt function SetActorRotation
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {				//trigger volume class has a method that check if actor is overlapping,
																			//importantly it asks what actor is it overlapping with.
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}  

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) { CloseDoor(); }

	// Check if it's time to close the door


	// If the ActorThatOpens is in the volumne
	
}

