/*
	This has been repurposed to an all around Weapon/Ammo Spawner meant to be able to be editted in
	blueprints to change values for testing
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "WeaponSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AMainCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLESHOOTER_API UWeaponSpawner : public USphereComponent
{
	GENERATED_BODY()
	
public:


	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp PickupItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int ItemValue;




	UWeaponSpawner();

protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
		void OnItemPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
