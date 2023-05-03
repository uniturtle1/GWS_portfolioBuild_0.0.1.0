// This was for testing out creating interactable enviroments but doesn't work as intended yet

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "destructable.generated.h"

class USphereComponent;

UCLASS(config=Game)
class Adestructable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	UPROPERTY(VisibleDefaultsonly, Category = Destructable)
	USphereComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ACustomCubes> TempCube;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	Adestructable();

	USphereComponent* GetCollisionComp() const { return CollisionComp; }
};
