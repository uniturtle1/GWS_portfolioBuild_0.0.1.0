// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
class UImage;
class UTexture2D;
class UTexture;


UCLASS(Abstract)
class PUZZLESHOOTER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayREason);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Ammo1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Ammo10;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Ammo100;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* AmmoDisplay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Health1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Health10;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Health100;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* HealthDisplay;

	UPROPERTY(EditAnywhere)
	UTexture* NumberFont0;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont1;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont2;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont3;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont4;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont5;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont6;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont7;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont8;
	UPROPERTY(EditAnywhere)
	UTexture* NumberFont9;

	

public:
	void ChangeHealth(int HealthValue);

	void ChangeAmmo(int AmmoValue);

};
