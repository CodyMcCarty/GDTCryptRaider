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

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* KeyActor = nullptr;
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	if (Mover == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover not found %s"), *GetOwner()->GetActorNameOrLabel());
		return;
	}

	for (auto Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableTag) && !Actor->ActorHasTag("Grabbed"))
		{
			KeyActor = Actor;
		}
	}

	if (KeyActor != nullptr)
	{
		UPrimitiveComponent* KeyRootComponent = Cast<UPrimitiveComponent>(KeyActor->GetRootComponent());
		if (KeyRootComponent != nullptr)
		{
			KeyRootComponent->SetSimulatePhysics(false);
			KeyRootComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Mover->SetShouldMove(true);
		}
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}
