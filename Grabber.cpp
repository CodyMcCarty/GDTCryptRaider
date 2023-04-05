// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	// ...
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	UPhysicsHandleComponent* PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandleComponent == nullptr) return;
	if (PhysicsHandleComponent->GetGrabbedComponent() == nullptr) return;

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDist;
	PhysicsHandleComponent->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandleComponent == nullptr) return;
	if (PhysicsHandleComponent->GetGrabbedComponent() == nullptr) return;

	PhysicsHandleComponent->GetGrabbedComponent()->WakeAllRigidBodies();
	PhysicsHandleComponent->ReleaseComponent();
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	FHitResult HitResult = FHitResult();
	bool HasHit = GetGrabbableInReach(HitResult);

	if (!HasHit) return;
	if (PhysicsHandleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandleComponent is nullptr.  Please add the component"));
		return;
	}

	PhysicsHandleComponent->SetLinearStiffness(1400);
	HitResult.GetComponent()->WakeAllRigidBodies();
	PhysicsHandleComponent->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None,HitResult.ImpactPoint, GetComponentRotation());
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDist;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
}
