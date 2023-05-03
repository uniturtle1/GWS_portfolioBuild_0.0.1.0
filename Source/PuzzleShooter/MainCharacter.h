// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class UCharacterMovementComponent;
class UPlayerHUD;

UCLASS(config=Game)
class AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* MeshMC;

	// Weapon Meshes all loaded into the character but set invisible until later use. 
	// ToDo: figure out a better system for this
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* MeshShotgunWeapon;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* MeshBiggerIronWeapon;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* MeshBiggerIronWeapon_2;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AShotgunProjectile> ShotgunPellets;

	// First person camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FP_CameraComponent;

	// MappingContext 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	// Jump Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	// Move Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	// Equip Actions {Unarmed, Shotgun, TheBiggerIron}
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Equip1Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Equip2Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* Equip3Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AltFireAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* exitGameAction;

	UCharacterMovementComponent* PlayerMovementComponent = GetCharacterMovement();


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;
	UPROPERTY()
	class UPlayerHUD* PlayerHUD;

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected: 
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip1(const FInputActionValue& Value);
	void Equip2(const FInputActionValue& Value);
	void Equip3(const FInputActionValue& Value);
	void exitGame(const FInputActionValue& Value);

public:

	struct WeaponWheel {
		USkeletalMeshComponent* weaponMesh;
		USkeletalMeshComponent* secondMesh;
		FString WeaponName;
		bool hasWeapon;
		int MaxAmmo;
		int CurrentAmmo;
	};
	TArray<WeaponWheel> CurrentWheel;

	void SetWeaponWheelValue(bool pickup, int ItemID, int AddedValue);

	USkeletalMeshComponent* GetMeshMC() const { return MeshMC; }

	UCameraComponent* GetFP_CameraComponent() const { return FP_CameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int CurrentWeapon;

	void WeaponSwap(int x);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AltFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	void ShotgunProjectiles(int x);

	void BiggerIronProjectile();
};
