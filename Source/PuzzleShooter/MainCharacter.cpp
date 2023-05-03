// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharacter.h"
#include "ShotgunProjectile.h"
#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework\CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	FP_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FP_CameraComponent->SetupAttachment(GetCapsuleComponent());
	FP_CameraComponent->SetRelativeLocation(FVector(10.f, 0.f, 60.f)); // Position the camera
	FP_CameraComponent->bUsePawnControlRotation = true;

	MeshMC = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainCharacterMesh"));
	MeshMC->SetOnlyOwnerSee(true);
	MeshMC->SetupAttachment(FP_CameraComponent);
	MeshMC->bCastDynamicShadow = false;
	MeshMC->CastShadow = true;
	MeshMC->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	MeshShotgunWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShotgunWeaponMesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ShotgunSkeletalMeshFinder(TEXT("/Game/MainCharacter/Norma/WeaponAssets/shotgunMesh"));
	MeshShotgunWeapon->SetSkeletalMesh(ShotgunSkeletalMeshFinder.Object);
	MeshShotgunWeapon->SetupAttachment(FP_CameraComponent);
	MeshShotgunWeapon->bCastDynamicShadow = false;
	MeshShotgunWeapon->SetVisibility(false);
	MeshShotgunWeapon->CastShadow = true;

	MeshBiggerIronWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BiggerIronWeaponMesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> BiggerIronSkeletalMeshFinder(TEXT("/Game/MainCharacter/Norma/WeaponAssets/TheBiggerIronFrameMesh"));
	MeshBiggerIronWeapon->SetSkeletalMesh(BiggerIronSkeletalMeshFinder.Object);
	MeshBiggerIronWeapon->SetupAttachment(FP_CameraComponent);
	MeshBiggerIronWeapon->bCastDynamicShadow = false;
	MeshBiggerIronWeapon->SetVisibility(false);
	MeshBiggerIronWeapon->CastShadow = true;

	MeshBiggerIronWeapon_2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BiggerIronWeaponMesh_2"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> BiggerIronSkeletalMesh2Finder(TEXT("/Game/MainCharacter/Norma/WeaponAssets/TheBiggerIronCylinderMesh"));
	MeshBiggerIronWeapon_2->SetSkeletalMesh(BiggerIronSkeletalMesh2Finder.Object);
	MeshBiggerIronWeapon_2->SetupAttachment(MeshBiggerIronWeapon);
	MeshBiggerIronWeapon_2->bCastDynamicShadow = false;
	MeshBiggerIronWeapon_2->SetVisibility(false);
	MeshBiggerIronWeapon_2->CastShadow = true;

	PlayerMovementComponent->MaxWalkSpeed = 12000.0f;
	PlayerMovementComponent->JumpZVelocity = 600.0f;
	PlayerMovementComponent->Mass = PlayerMovementComponent->Mass / 25.0f;

	CurrentWheel.Add({ nullptr, nullptr, "Unarmed", true, 0, 0 });
	CurrentWheel.Add({ MeshShotgunWeapon, nullptr, "Shotgun", true, 100, 0 });
	CurrentWheel.Add({ MeshBiggerIronWeapon, MeshBiggerIronWeapon_2, "TheBiggerIron", true, 120, 0});

	CurrentWeapon = 0;
	MuzzleOffset = FVector(130.0f, 20.0f, -10.0f);

	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();
	}
}

void AMainCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD) {
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);
		EnhancedInputComponent->BindAction(Equip1Action, ETriggerEvent::Triggered, this, &AMainCharacter::Equip1);
		EnhancedInputComponent->BindAction(Equip2Action, ETriggerEvent::Triggered, this, &AMainCharacter::Equip2);
		EnhancedInputComponent->BindAction(Equip3Action, ETriggerEvent::Triggered, this, &AMainCharacter::Equip3);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMainCharacter::Fire);
		EnhancedInputComponent->BindAction(AltFireAction, ETriggerEvent::Triggered, this, &AMainCharacter::AltFire);
		EnhancedInputComponent->BindAction(exitGameAction, ETriggerEvent::Triggered, this, &AMainCharacter::exitGame);
	}
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void AMainCharacter::Equip1(const FInputActionValue& Value)
{
	WeaponSwap(0);
	CurrentWeapon = 0;
	FString info = FString::FromInt(CurrentWeapon);
}
void AMainCharacter::Equip2(const FInputActionValue& Value)
{
	WeaponSwap(1);
	CurrentWeapon = 1;
	FString info = FString::FromInt(CurrentWeapon);
}
void AMainCharacter::Equip3(const FInputActionValue& Value)
{
	WeaponSwap(2);
	CurrentWeapon = 2;
	FString info = FString::FromInt(CurrentWeapon);
}

void AMainCharacter::exitGame(const FInputActionValue& Value)
{
}

void AMainCharacter::SetWeaponWheelValue(bool pickup, int ItemID, int AddedValue)
{
	if (pickup && !CurrentWheel[ItemID].hasWeapon) {
		CurrentWheel[ItemID].hasWeapon = true;
		CurrentWheel[ItemID].CurrentAmmo = CurrentWheel[ItemID].MaxAmmo / 2;
	}
	else {
		CurrentWheel[ItemID].CurrentAmmo += AddedValue;
		if (CurrentWheel[ItemID].CurrentAmmo > CurrentWheel[ItemID].MaxAmmo)
			CurrentWheel[ItemID].CurrentAmmo = CurrentWheel[ItemID].MaxAmmo;
	}
	if (ItemID == CurrentWeapon)
		PlayerHUD->ChangeAmmo(CurrentWheel[ItemID].CurrentAmmo);
	FString info = FString::FromInt(CurrentWheel[ItemID].CurrentAmmo);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("" + info));
}

void AMainCharacter::WeaponSwap(int x)
{
	if (!CurrentWheel[x].hasWeapon)
		return;
	int i = 0;
	while(i < CurrentWheel.Num()) {
		if (CurrentWheel[i].weaponMesh) {
			if (i == x) {
				CurrentWheel[i].weaponMesh->SetVisibility(true);
				if (CurrentWheel[i].secondMesh)
					CurrentWheel[i].secondMesh->SetVisibility(true);
			}
			else {
				CurrentWheel[i].weaponMesh->SetVisibility(false);
				if (CurrentWheel[i].secondMesh)
					CurrentWheel[i].secondMesh->SetVisibility(false);
			}
		}
		i++;
	}
	PlayerHUD->ChangeAmmo(CurrentWheel[x].CurrentAmmo);
}

void AMainCharacter::Fire()
{
	if (CurrentWeapon == 1 && CurrentWheel[CurrentWeapon].CurrentAmmo > 1) {
		ShotgunProjectiles(8);
		SetWeaponWheelValue(true, CurrentWeapon, -2);
	}
	else if (CurrentWeapon == 2 && CurrentWheel[CurrentWeapon].CurrentAmmo > 0) {
		ShotgunProjectiles(1);
		SetWeaponWheelValue(true, CurrentWeapon, -1);
	}
}

void AMainCharacter::AltFire()
{
}

void AMainCharacter::ShotgunProjectiles(int x)
{
	
	if (ShotgunPellets != nullptr) {
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			//used to get Player's current info, reference for later 
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			//loop for spawning multiple projectiles in random directions within a range.
			// Pitch and Yaw change the trajectory but Roll really isn't needed since they are all spheres I think
			int i = 0;
			while (i < x) {
				float PelletPitch = 0.5f * FMath::RandRange(-5, 5);
				float PelletYaw = 1.5f * FMath::RandRange(-5, 5);
				float PelletRoll = 0.5f * FMath::RandRange(-5, 5) + 5.0f;
				FRotator PelletSpawn = SpawnRotation + FRotator(PelletPitch, PelletYaw, PelletRoll);
				World->SpawnActor<AShotgunProjectile>(ShotgunPellets, SpawnLocation, PelletSpawn, ActorSpawnParams);
				i++;
			}
		}
	}
}

void AMainCharacter::BiggerIronProjectile()
{
	//ToDo: This is suppose to work as a hitscan
}



