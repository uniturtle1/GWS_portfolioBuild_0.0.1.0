// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSpawner.h"

UWeaponSpawner::UWeaponSpawner() {
	SphereRadius = 50.0f;
	ItemValue = 1;
	ItemID = 1;
}

void UWeaponSpawner::BeginPlay(){
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UWeaponSpawner::OnItemPickup);
}

void UWeaponSpawner::OnItemPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		PickupItem.Broadcast(Character);

		Character->SetWeaponWheelValue(true, ItemID, ItemValue);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
