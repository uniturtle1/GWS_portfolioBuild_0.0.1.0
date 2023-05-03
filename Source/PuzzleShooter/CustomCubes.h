// This was for testing out creating interactable enviroments

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CustomCubes.generated.h"

class UstaticMeshComponent;

UCLASS(config=Game)
class ACustomCubes : public AStaticMeshActor
{
	GENERATED_BODY()

	

	ACustomCubes();

};
