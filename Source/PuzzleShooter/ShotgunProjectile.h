// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "GameFramework/Actor.h"
#include "ShotgunProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class AMainCharacter;

UCLASS(config=Game)
class AShotgunProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsonly, Category = Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	
public:	
	// Sets default values for this actor's properties
	
	AShotgunProjectile();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	AMainCharacter* Character;
};
