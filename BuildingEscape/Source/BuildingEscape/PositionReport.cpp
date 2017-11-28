// This Components return the position of the object it is attached to.


#include "PositionReport.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();									//Set the var ObjectName to the Name of the Owner of this component.

	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();	//Set the var Object Pos to the location, found in the -
																				//transform of the object this is attached to.

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);		//Print to Log ObjectName, ObjectPos via UE_LOG Macro
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

