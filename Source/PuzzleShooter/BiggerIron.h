/*
	This is defuncted only for reference
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BiggerIron.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PUZZLESHOOTER_API UBiggerIron : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void AttachWeapon(AMainCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* FireAction;

	UBiggerIron();

protected:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndplayReason) override;

private:
	/** The Character holding this weapon*/
	AMainCharacter* Character;
};
