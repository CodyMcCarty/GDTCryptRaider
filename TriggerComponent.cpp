// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("triggering!!"));

	AActor* KeyActor = nullptr;
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (auto Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableTag))
		{
		KeyActor = Actor;
		}
	}

	if (KeyActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlocking"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ReLocking"));
	}
		
}
