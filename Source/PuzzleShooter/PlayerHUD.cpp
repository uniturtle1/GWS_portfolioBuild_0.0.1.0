// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"


void UPlayerHUD::BeginPlay()
{
	NumberFont0 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_0"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberZero(TEXT("/Game/HudAssets/NumberFont_0"));
	NumberFont0 = NumberZero.Object;
	NumberFont1 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_1"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberOne(TEXT("/Game/HudAssets/NumberFont_1"));
	NumberFont1 = NumberOne.Object;
	NumberFont2 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_2"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberTwo(TEXT("/Game/HudAssets/NumberFont_2"));
	NumberFont2 = NumberTwo.Object;
	NumberFont3 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_3"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberThree(TEXT("/Game/HudAssets/NumberFont_3"));
	NumberFont3 = NumberThree.Object;
	NumberFont4 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_4"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberFour(TEXT("/Game/HudAssets/NumberFont_4"));
	NumberFont4 = NumberFour.Object;
	NumberFont5 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_5"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberFive(TEXT("/Game/HudAssets/NumberFont_5"));
	NumberFont5 = NumberFive.Object;
	NumberFont6 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_6"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberSix(TEXT("/Game/HudAssets/NumberFont_6"));
	NumberFont6 = NumberSix.Object;
	NumberFont7 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_7"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberSeven(TEXT("/Game/HudAssets/NumberFont_7"));
	NumberFont7 = NumberSeven.Object;
	NumberFont8 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_8"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberEight(TEXT("/Game/HudAssets/NumberFont_8"));
	NumberFont8 = NumberEight.Object;
	NumberFont9 = CreateDefaultSubobject<UTexture>(TEXT("NumberFont_9"));
	ConstructorHelpers::FObjectFinder<UTexture> NumberNine(TEXT("/Game/HudAssets/NumberFont_9"));
	NumberFont9 = NumberNine.Object;
}

void UPlayerHUD::EndPlay(const EEndPlayReason::Type EndPlayREason)
{
}

void UPlayerHUD::ChangeHealth(int HealthValue)
{
	int HealthValuetemp = HealthValue;
	int health100temp = 0;
	int health10temp = 0;
	int health1temp = 0;
	while (HealthValuetemp > 99) {
		HealthValuetemp -= 100;
		health100temp++;
	}
	while (HealthValuetemp > 9) {
		HealthValuetemp -= 10;
		health10temp++;
	}
	while (HealthValuetemp > 0) {
		HealthValuetemp -= 1;
		health1temp++;
	}
	if (health100temp == 1)
		Health100->SetBrushResourceObject(NumberFont1);
	else if (health100temp == 2)
		Health100->SetBrushResourceObject(NumberFont2);
	else if (health100temp == 3)
		Health100->SetBrushResourceObject(NumberFont3);
	else if (health100temp == 4)
		Health100->SetBrushResourceObject(NumberFont4);
	else if (health100temp == 5)
		Health100->SetBrushResourceObject(NumberFont5);
	else if (health100temp == 6)
		Health100->SetBrushResourceObject(NumberFont6);
	else if (health100temp == 7)
		Health100->SetBrushResourceObject(NumberFont7);
	else if (health100temp == 8)
		Health100->SetBrushResourceObject(NumberFont8);
	else if (health100temp == 9)
		Health100->SetBrushResourceObject(NumberFont9);
	else
		Health100->SetBrushResourceObject(NumberFont0);

	if (health10temp == 1)
		Health10->SetBrushResourceObject(NumberFont1);
	else if (health10temp == 2)
		Health10->SetBrushResourceObject(NumberFont2);
	else if (health10temp == 3)
		Health10->SetBrushResourceObject(NumberFont3);
	else if (health10temp == 4)
		Health10->SetBrushResourceObject(NumberFont4);
	else if (health10temp == 5)
		Health10->SetBrushResourceObject(NumberFont5);
	else if (health10temp == 6)
		Health10->SetBrushResourceObject(NumberFont6);
	else if (health10temp == 7)
		Health10->SetBrushResourceObject(NumberFont7);
	else if (health10temp == 8)
		Health10->SetBrushResourceObject(NumberFont8);
	else if (health10temp == 9)
		Health10->SetBrushResourceObject(NumberFont9);
	else
		Health10->SetBrushResourceObject(NumberFont0);

	if (health1temp == 1)
		Health1->SetBrushResourceObject(NumberFont1);
	else if (health1temp == 2)
		Health1->SetBrushResourceObject(NumberFont2);
	else if (health1temp == 3)
		Health1->SetBrushResourceObject(NumberFont3);
	else if (health1temp == 4)
		Health1->SetBrushResourceObject(NumberFont4);
	else if (health1temp == 5)
		Health1->SetBrushResourceObject(NumberFont5);
	else if (health1temp == 6)
		Health1->SetBrushResourceObject(NumberFont6);
	else if (health1temp == 7)
		Health1->SetBrushResourceObject(NumberFont7);
	else if (health1temp == 8)
		Health1->SetBrushResourceObject(NumberFont8);
	else if (health1temp == 9)
		Health1->SetBrushResourceObject(NumberFont9);
	else
		Health1->SetBrushResourceObject(NumberFont0);
}

void UPlayerHUD::ChangeAmmo(int AmmoValue)
{
	int AmmoValuetemp = AmmoValue;
	int ammo100temp = 0;
	int ammo10temp = 0;
	int ammo1temp = 0;
	while (AmmoValuetemp > 99) {
		AmmoValuetemp -= 100;
		ammo100temp++;
	}
	while (AmmoValuetemp > 9) {
		AmmoValuetemp -= 10;
		ammo10temp++;
	}
	while (AmmoValuetemp > 0) {
		AmmoValuetemp -= 1;
		ammo1temp++;
	}
	if (ammo100temp == 1)
		Ammo100->SetBrushResourceObject(NumberFont1);
	else if (ammo100temp == 2)
		Ammo100->SetBrushResourceObject(NumberFont2);
	else if (ammo100temp == 3)
		Ammo100->SetBrushResourceObject(NumberFont3);
	else if (ammo100temp == 4)
		Ammo100->SetBrushResourceObject(NumberFont4);
	else if (ammo100temp == 5)
		Ammo100->SetBrushResourceObject(NumberFont5);
	else if (ammo100temp == 6)
		Ammo100->SetBrushResourceObject(NumberFont6);
	else if (ammo100temp == 7)
		Ammo100->SetBrushResourceObject(NumberFont7);
	else if (ammo100temp == 8)
		Ammo100->SetBrushResourceObject(NumberFont8);
	else if (ammo100temp == 9)
		Ammo100->SetBrushResourceObject(NumberFont9);
	else
		Ammo100->SetBrushResourceObject(NumberFont0);
	if (ammo10temp == 1)
		Ammo10->SetBrushResourceObject(NumberFont1);
	else if (ammo10temp == 2)
		Ammo10->SetBrushResourceObject(NumberFont2);
	else if (ammo10temp == 3)
		Ammo10->SetBrushResourceObject(NumberFont3);
	else if (ammo10temp == 4)
		Ammo10->SetBrushResourceObject(NumberFont4);
	else if (ammo10temp == 5)
		Ammo10->SetBrushResourceObject(NumberFont5);
	else if (ammo10temp == 6)
		Ammo10->SetBrushResourceObject(NumberFont6);
	else if (ammo10temp == 7)
		Ammo10->SetBrushResourceObject(NumberFont7);
	else if (ammo10temp == 8)
		Ammo10->SetBrushResourceObject(NumberFont8);
	else if (ammo10temp == 9)
		Ammo10->SetBrushResourceObject(NumberFont9);
	else
		Ammo10->SetBrushResourceObject(NumberFont0);

	if (ammo1temp == 1)
		Ammo1->SetBrushResourceObject(NumberFont1);
	else if (ammo1temp == 2)
		Ammo1->SetBrushResourceObject(NumberFont2);
	else if (ammo1temp == 3)
		Ammo1->SetBrushResourceObject(NumberFont3);
	else if (ammo1temp == 4)
		Ammo1->SetBrushResourceObject(NumberFont4);
	else if (ammo1temp == 5)
		Ammo1->SetBrushResourceObject(NumberFont5);
	else if (ammo1temp == 6)
		Ammo1->SetBrushResourceObject(NumberFont6);
	else if (ammo1temp == 7)
		Ammo1->SetBrushResourceObject(NumberFont7);
	else if (ammo1temp == 8)
		Ammo1->SetBrushResourceObject(NumberFont8);
	else if (ammo1temp == 9)
		Ammo1->SetBrushResourceObject(NumberFont9);
	else
		Ammo1->SetBrushResourceObject(NumberFont0);
	
}

