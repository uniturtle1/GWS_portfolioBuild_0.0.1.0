// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleShooterGameMode.h"
#include "MainCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleShooterGameMode::APuzzleShooterGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MainCharacter/Norma/MyMainCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}