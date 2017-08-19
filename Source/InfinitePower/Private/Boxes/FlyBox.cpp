// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyBox.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"


// Sets default values
AFlyBox::AFlyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CubeStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent> (TEXT ("Cube Mesh"));
    CubeStaticMeshComponent->SetupAttachment (RootComponent);
    CubeStaticMeshComponent->bGenerateOverlapEvents = true;
    CubeStaticMeshComponent->SetCollisionObjectType (ECC_PhysicsBody);
    CubeStaticMeshComponent->SetSimulatePhysics (true);
    CubeStaticMeshComponent->BodyInstance.bLockXRotation = true;
    CubeStaticMeshComponent->BodyInstance.bLockYRotation = true;

    PropellerSceneComponent = CreateDefaultSubobject<USceneComponent> (TEXT ("Propellers"));
    PropellerSceneComponent->SetupAttachment (CubeStaticMeshComponent);

    PropellerOneComponent = CreateDefaultSubobject<UStaticMeshComponent> (TEXT ("Propeller 1 Mesh"));
    PropellerOneComponent->SetupAttachment (PropellerSceneComponent);
    PropellerOneComponent->SetRelativeLocation (FVector (-50, 0, 70));
    PropellerOneComponent->SetRelativeRotation (FRotator (-10, 90, -90));
    PropellerOneComponent->SetRelativeScale3D (FVector (1, 0.1, 1));
    PropellerOneComponent->bGenerateOverlapEvents = false;
    PropellerOneComponent->SetCollisionObjectType (ECC_WorldStatic);
    PropellerOneComponent->SetCollisionEnabled (ECollisionEnabled::NoCollision);
    PropellerOneComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    PropellerOneComponent->SetSimulatePhysics (false);
    PropellerOneComponent->SetEnableGravity (false);

    PropellerTwoComponent = CreateDefaultSubobject<UStaticMeshComponent> (TEXT ("Propeller 2 Mesh"));
    PropellerTwoComponent->SetupAttachment (PropellerSceneComponent);
    PropellerTwoComponent->SetRelativeLocation (FVector (26, -44, 70));
    PropellerTwoComponent->SetRelativeRotation (FRotator (-10, -150, -90));
    PropellerTwoComponent->SetRelativeScale3D (FVector (1, 0.1, 1));
    PropellerTwoComponent->bGenerateOverlapEvents = false;
    PropellerTwoComponent->SetCollisionObjectType (ECC_WorldStatic);
    PropellerTwoComponent->SetCollisionEnabled (ECollisionEnabled::NoCollision);
    PropellerTwoComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    PropellerTwoComponent->SetSimulatePhysics (false);
    PropellerTwoComponent->SetEnableGravity (false);

    PropellerThreeComponent = CreateDefaultSubobject<UStaticMeshComponent> (TEXT ("Propeller 3 Mesh"));
    PropellerThreeComponent->SetupAttachment (PropellerSceneComponent);
    PropellerThreeComponent->SetRelativeLocation (FVector (26, 44, 70));
    PropellerThreeComponent->SetRelativeRotation (FRotator (-10, -30, -90));
    PropellerThreeComponent->SetRelativeScale3D (FVector (1, 0.1, 1));
    PropellerThreeComponent->bGenerateOverlapEvents = false;
    PropellerThreeComponent->SetCollisionObjectType (ECC_WorldStatic);
    PropellerThreeComponent->SetCollisionEnabled (ECollisionEnabled::NoCollision);
    PropellerThreeComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
    PropellerThreeComponent->SetSimulatePhysics (false);
    PropellerThreeComponent->SetEnableGravity (false);

    Tags.Add (FName ("FlyBox"));

    ConstructorFinderDefaults ();

}

void AFlyBox::ConstructorFinderDefaults () {
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshCube (TEXT ("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (StaticMeshCube.Object)
        CubeStaticMeshComponent->SetStaticMesh (StaticMeshCube.Object);

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material (TEXT ("Material'/Game/Materials/Boxes/M_FlyBox.M_FlyBox'"));
    if (Material.Object)
        CubeStaticMeshComponent->SetMaterial (0, Material.Object);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh (TEXT ("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
    if (StaticMesh.Object) {
        PropellerOneComponent->SetStaticMesh (StaticMesh.Object);
        PropellerTwoComponent->SetStaticMesh (StaticMesh.Object);
        PropellerThreeComponent->SetStaticMesh (StaticMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialPropeller (TEXT ("Material'/Game/Materials/Boxes/M_FlyBoxPropeller.M_FlyBoxPropeller'"));
    if (MaterialPropeller.Object) {
        PropellerOneComponent->SetMaterial (0, MaterialPropeller.Object);
        PropellerTwoComponent->SetMaterial (0, MaterialPropeller.Object);
        PropellerThreeComponent->SetMaterial (0, MaterialPropeller.Object);
    }
}

// Called when the game starts or when spawned
void AFlyBox::BeginPlay() {
	Super::BeginPlay();
    CreateCheckpoint_Implementation ();
}


// Called every frame
void AFlyBox::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
    PropellerSceneComponent->AddLocalRotation (FRotator (0, 3, 0));
}

void AFlyBox::ReturnToCheckpoint_Implementation () {
    SetActorTransform (CheckpointTransform);
    CubeStaticMeshComponent->SetAllPhysicsLinearVelocity (FVector (0, 0, 0));
}

void AFlyBox::CreateCheckpoint_Implementation () {
    CheckpointTransform = GetActorTransform ();
}

