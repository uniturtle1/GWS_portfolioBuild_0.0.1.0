// Fill out your copyright notice in the Description page of Project Settings.


#include "GnobGnob.h"

// Sets default values
AGnobGnob::AGnobGnob()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGnobGnob::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGnobGnob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGnobGnob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

