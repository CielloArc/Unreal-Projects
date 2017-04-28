// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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
	owner = GetOwner();	

	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure plate is null"));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//
	if (GetMassOnPlate() >= triggerMass) 
	{
		OnOpen.Broadcast();
	}else
	{
		OnClose.Broadcast();
	}
	
}

float UOpenDoor::GetMassOnPlate()
{
	float totalMass = 0.0f;

	//Find all the overlapping actors
	TArray<AActor*> overlappingActors;
	if (!pressurePlate){return totalMass;}
	pressurePlate->GetOverlappingActors(OUT overlappingActors);
	//add their mass
	for (const auto* Actor : overlappingActors) 
	{
		totalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Actor %s on trigger"), *Actor->GetName());
	}


	return totalMass;
}

