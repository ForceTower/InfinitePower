// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpBox.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"


// Sets default values
AJumpBox::AJumpBox() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CubeStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent> (TEXT ("Cube Mesh"));
    CubeStaticMeshComponent->SetupAttachment (RootComponent);
    CubeStaticMeshComponent->bGenerateOverlapEvents = true;
    CubeStaticMeshComponent->SetCollisionObjectType (ECC_PhysicsBody);
    CubeStaticMeshComponent->SetSimulatePhysics (true);
    CubeStaticMeshComponent->BodyInstance.bLockXRotation = true;
    CubeStaticMeshComponent->BodyInstance.bLockYRotation = true;

    BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent> (TEXT ("Collision"));
    BoxCollisionComponent->bGenerateOverlapEvents = true;
    BoxCollisionComponent->SetCollisionObjectType (ECC_WorldDynamic);
    BoxCollisionComponent->SetCollisionEnabled (ECollisionEnabled::QueryOnly);
    BoxCollisionComponent->SetRelativeLocation (FVector (0, 0, 52));
    BoxCollisionComponent->SetRelativeScale3D (FVector (0.95, 0.95, 0.1));
    BoxCollisionComponent->SetBoxExtent (FVector (47, 47, 10));
    BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic (this, &AJumpBox::OnBoxComponentBeginOverlap);
    BoxCollisionComponent->SetupAttachment (CubeStaticMeshComponent);

    ConstructorFinderDefaults ();

    Tags.Add (FName ("JumpBox"));
}

void AJumpBox::ConstructorFinderDefaults () {
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh (TEXT ("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (StaticMesh.Object)
        CubeStaticMeshComponent->SetStaticMesh (StaticMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material (TEXT ("Material'/Game/Materials/Boxes/M_JumpBox.M_JumpBox'"));
    if (Material.Object)
        CubeStaticMeshComponent->SetMaterial (0, Material.Object);
}

// Called when the game starts or when spawned
void AJumpBox::BeginPlay() {
	Super::BeginPlay();
    CreateCheckpoint_Implementation ();
}

void AJumpBox::OnBoxComponentBeginOverlap (class UPrimitiveComponent* overlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    ACharacter* player = Cast<ACharacter> (OtherActor);
    if (player) {
        player->GetCapsuleComponent()->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
        player->GetCapsuleComponent()->AddForce(FVector(0, 0, 30000), NAME_None, true);
    }
}

void AJumpBox::ReturnToCheckpoint_Implementation () {
    SetActorTransform (CheckpointTransform);
    CubeStaticMeshComponent->SetAllPhysicsLinearVelocity (FVector (0, 0, 0));
}

void AJumpBox::CreateCheckpoint_Implementation () {
    CheckpointTransform = GetActorTransform ();
}


