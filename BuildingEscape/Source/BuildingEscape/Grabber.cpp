// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"

#define OUT //does nothing, good for annotation

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));			//Print String to World for debugging purposes.
	/// look for attached physics handle

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	FString OwnerName = GetOwner()->GetName();

	if (PhysicsHandle) {}
	else 
	{	
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle Not Found on %s"), *OwnerName);
	}
	if (Input) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Found on %s"), *OwnerName);
		//Input->BindAction("Grab", IE_Pressed, this, &UGrabber::UGrabber);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Input Not Found!"));
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get the player view point every tick (transform and direction)
	// Ray-cast out to the reach distance
	// See what we hit

	FVector PlayerViewPointLocation;										//Instatiate a vector for the players location.
	FRotator PlayerViewPointRotation;										//Instatiate a rotator for their rotation.

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(				//Use the function GetPlayerViewPoint which Gets AND Sets the
																			//input values. We pass in the variables while getting.
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

		
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);	//Add our location to the vectorized rotation, which is extended by our Reach.

	FString LineWarning = LineTraceEnd.ToString();							
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *LineWarning);						//Print Linetraceend for debugging purposes.

	DrawDebugLine(															//engine method to draw our ray cast with several parameters.
		GetWorld(),															//we want it in our current world.
		PlayerViewPointLocation,											//starts at veiwer location
		LineTraceEnd,														//ends at extent of our ray cast
		FColor(255, 0, 0),													//make it red
		false,																//no persistant lines
		0.f,																//no float time
		0.f,																//no depth priority
		10.f																//10cm thick.
	);

	//Line Trace (a.k.a Ray-Cast) out to reach distance.
	//setup params

	FCollisionQueryParams TraceParams (FName(TEXT("")), false, GetOwner());	//a filter for the ray cast?

	FHitResult Hit;															//new var of type FHitResult

	GetWorld()->LineTraceSingleByObjectType(								//call the getworld function raycast by object type
		OUT Hit,															//returns a hit
		PlayerViewPointLocation,											//start ray trace location
		LineTraceEnd,														//end ray tray location
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	//object filtering
		TraceParams															//additional parameters.
	);

	AActor* ActorHit = Hit.GetActor();										//store a reference to the actor hit
	if (ActorHit) {

		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));	//if the actor was hit, print its name in the log.
		//see what we het
	}
}

