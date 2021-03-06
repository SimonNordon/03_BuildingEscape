// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();							//instatiating a protected method OpenDoor();	
	void CloseDoor();							//instatiating a protected method OpenDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = 10.0f;					//Expose Door Angle (type float) to the editor.

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;				//Expose PressurePlate (type ATriggerVolume) to the editor. Must be dereferenced.

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;					//Expose Time of door delay to the editor.

	float LastDoorOpenTime;						//Create a private variable to store the time the door was last closed.

	AActor *ActorThatOpens;						//This dereferenced Actor will be what actions the trigger event.
	AActor *Owner;								//This references the door itself.
	
};
