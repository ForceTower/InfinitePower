// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteBox.h"
#include "ConstructorHelpers.h"


// Sets default values
AInfiniteBox::AInfiniteBox()
{
	PrimaryActorTick.bCanEverTick = true;

    MovementComponent = GetMovementComponent();

    GetCapsuleComponent()->InitCapsuleSize(50, 50);
    GetCapsuleComponent()->SetSimulatePhysics(true);
    GetCapsuleComponent()->SetMassOverrideInKg(NAME_None, 100);
    GetCapsuleComponent()->SetEnableGravity(false);

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
    DefaultSceneRoot->SetupAttachment(RootComponent);

    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
    CubeMesh->SetupAttachment(DefaultSceneRoot);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CubeMesh);
    Camera->SetRelativeLocation(FVector(-700, 0, 150));
    Camera->SetRelativeRotation(FRotator(-20, 0, 0));

    UpCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Up Collision"));
    UpCollision->SetupAttachment(DefaultSceneRoot);
    UpCollision->SetRelativeLocation(FVector(0, 0, 30));
    UpCollision->SetBoxExtent(FVector(34, 34, 34));

    DownCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Down Collision"));
    DownCollision->SetupAttachment(DefaultSceneRoot);
    DownCollision->SetRelativeLocation(FVector(0, 0, -30));
    DownCollision->SetBoxExtent(FVector(34, 34, 34));

    LeftCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Collision"));
    LeftCollision->SetupAttachment(DefaultSceneRoot);
    LeftCollision->SetRelativeLocation(FVector(0, -30, 0));
    LeftCollision->SetBoxExtent(FVector(34, 34, 34));

    RightCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Collision"));
    RightCollision->SetupAttachment(DefaultSceneRoot);
    RightCollision->SetRelativeLocation(FVector(0, 30, 0));
    RightCollision->SetBoxExtent(FVector(34, 34, 34));


}

void AInfiniteBox::ContructorFinderDefaults()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (StaticMesh.Object)
        CubeMesh->SetStaticMesh(StaticMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("MaterialInstanceConstant'/Game/Materials/GlowTron/M_MrBox.M_MrBox'"));
    if (Material.Object)
        CubeMesh->SetMaterial(0, Material.Object);
}

// Called when the game starts or when spawned
void AInfiniteBox::BeginPlay()
{
	Super::BeginPlay();
    CreateCheckpoint_Implementation();
}

// Called every frame
void AInfiniteBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInfiniteBox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis ("Move Horizontal", this, &AInfiniteBox::MoveHorizontal);
    PlayerInputComponent->BindAxis ("Move Vertical", this, &AInfiniteBox::MoveVertical);

}

void AInfiniteBox::MoveHorizontal(float value) 
{

}

void AInfiniteBox::MoveVertical(float value) 
{

}

void AInfiniteBox::ReturnToCheckpoint_Implementation()
{
    SetActorTransform(CheckpointTransform);
    CubeMesh->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
}

void AInfiniteBox::CreateCheckpoint_Implementation()
{
    CheckpointTransform = GetActorTransform();
}

