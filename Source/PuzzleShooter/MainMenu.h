// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;

UCLASS()
class PUZZLESHOOTER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StartButton;

	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayREason);

	void startGame();

};
