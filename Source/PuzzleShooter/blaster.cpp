/* 
	This is the defunct class for the shotgun weapon based on the ones from the FPS template
	Only use this for reference
	All functions have been moved to MainCharacter to simplify the Weapon Switching Function
*/
#include "blaster.h"
#include "MainCharacter.h"
#include "ShotgunProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

Ublaster::Ublaster() {
	// MuzzleOffSet sets the location of where the projectiles spawn
	MuzzleOffset = FVector(130.0f, 50.0f, 100.0f);
}


void Ublaster::AttachWeapon(AMainCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Set up action bindings, Switchfire Action doesn't do anything atm
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &Ublaster::Fire);

		}
	}
}

//ToDo: Add a check between fires shot to avoid spamming
void Ublaster::Fire()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("BANG BANG!!!"));
	if (Character == nullptr || Character->GetController() == nullptr) {
		return;
	}
	
	if (ShotgunPellets != nullptr) {
		UWorld* const World = GetWorld();
		if (World != nullptr) {

			//used to get Player's current info, reference for later 
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			FString info = SpawnRotation.ToString();
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("" + info));

			//loop for spawning multiple projectiles in random directions within a range.
			// Pitch and Yaw change the trajectory but Roll really isn't needed since they are all spheres
			int i = 0;
			while (i < 8) {
				float PelletPitch = 0.5f * FMath::RandRange(-5, 5);
				float PelletYaw = 2.0f * FMath::RandRange(-5, 5);
				float PelletRoll = 0.5f * FMath::RandRange(-5, 5) + 5.0f;
				FRotator PelletSpawn = SpawnRotation + FRotator(PelletPitch, PelletYaw, PelletRoll);
				World->SpawnActor<AShotgunProjectile>(ShotgunPellets, SpawnLocation, PelletSpawn, ActorSpawnParams);
				i++;
			}
		}
	}
}

void Ublaster::SwitchFire()
{
	//does nothing
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
}


void Ublaster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{

		}

	}
}

