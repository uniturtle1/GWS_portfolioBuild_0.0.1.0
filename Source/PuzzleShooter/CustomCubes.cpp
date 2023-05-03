// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCubes.h"

ACustomCubes::ACustomCubes() {

	SetMobility(EComponentMobility::Movable);
	UStaticMeshComponent* MeshCube = AStaticMeshActor::GetStaticMeshComponent();

	MeshCube->SetSimulatePhysics(true);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CustomCubeStaticMeshFinder(TEXT("/Game/MainCharacter/Norma/Meshes/Barrel"));
	MeshCube->SetStaticMesh(CustomCubeStaticMeshFinder.Object);
}