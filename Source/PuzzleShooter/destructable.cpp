// Fill out your copyright notice in the Description page of Project Settings.

#include "destructable.h"
#include "Components/SphereComponent.h"
#include "CustomCubes.h"


// Sets default values
Adestructable::Adestructable()
{
 	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->BodyInstance.SetCollisionProfileName("desctructable");
    CollisionComp->OnComponentHit.AddDynamic(this, &Adestructable::OnHit);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CustomCubeStaticMeshFinder(TEXT("/Game/MainCharacter/Norma/Meshes/Barrel"));
    RootComponent = CollisionComp;

}

void Adestructable::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
    {
        UWorld* const World = GetWorld();
        if (World != nullptr) {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn trash"));
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
            World->SpawnActor<ACustomCubes>(TempCube, GetOwner()->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParams);
        }

        Destroy();
    }
}


