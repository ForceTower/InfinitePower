// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteBox.h"
#include "ConstructorHelpers.h"

// Sets default values
AInfiniteBox::AInfiniteBox()
{
	PrimaryActorTick.bCanEverTick = true;

    MovementComponent = GetCharacterMovement();
    MovementComponent->GravityScale = 0.0f;

    GetCapsuleComponent()->InitCapsuleSize(50, 50);
    GetCapsuleComponent()->SetSimulatePhysics(true);
    GetCapsuleComponent()->SetMassOverrideInKg(NAME_None, 100);
    GetCapsuleComponent()->SetEnableGravity(false);
    GetCapsuleComponent()->BodyInstance.bLockXRotation = true;
    GetCapsuleComponent()->BodyInstance.bLockYRotation = true;
    GetCapsuleComponent()->BodyInstance.bLockZRotation = true;
    GetCapsuleComponent()->BodyInstance.bLockXTranslation = true;

    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
    CubeMesh->SetupAttachment(RootComponent);
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CubeMesh);
    Camera->SetRelativeLocation(FVector(-700, 0, 150));
    Camera->SetRelativeRotation(FRotator(-20, 0, 0));

    UpCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Up Collision"));
    UpCollision->SetupAttachment(RootComponent);
    UpCollision->SetRelativeLocation(FVector(0, 0, 30));
    UpCollision->SetBoxExtent(FVector(34, 34, 34));
    UpCollision->OnComponentBeginOverlap.AddDynamic(this, &AInfiniteBox::UpBeginOverlap);
    UpCollision->OnComponentEndOverlap.AddDynamic(this, &AInfiniteBox::UpEndOverlap);

    DownCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Down Collision"));
    DownCollision->SetupAttachment(RootComponent);
    DownCollision->SetRelativeLocation(FVector(0, 0, -30));
    DownCollision->SetBoxExtent(FVector(34, 34, 34));
    DownCollision->OnComponentBeginOverlap.AddDynamic(this, &AInfiniteBox::DownBeginOverlap);
    DownCollision->OnComponentEndOverlap.AddDynamic(this, &AInfiniteBox::DownEndOverlap);

    LeftCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Collision"));
    LeftCollision->SetupAttachment(RootComponent);
    LeftCollision->SetRelativeLocation(FVector(0, -30, 0));
    LeftCollision->SetBoxExtent(FVector(34, 34, 34));
    LeftCollision->OnComponentBeginOverlap.AddDynamic(this, &AInfiniteBox::LeftBeginOverlap);
    LeftCollision->OnComponentEndOverlap.AddDynamic(this, &AInfiniteBox::LeftEndOverlap);

    RightCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Collision"));
    RightCollision->SetupAttachment(RootComponent);
    RightCollision->SetRelativeLocation(FVector(0, 30, 0));
    RightCollision->SetBoxExtent(FVector(34, 34, 34));
    RightCollision->OnComponentBeginOverlap.AddDynamic(this, &AInfiniteBox::RightBeginOverlap);
    RightCollision->OnComponentEndOverlap.AddDynamic(this, &AInfiniteBox::RightEndOverlap);


    ConstructorFinderDefaults();
}

void AInfiniteBox::ConstructorFinderDefaults()
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
    CurrentGravity = StartGravity;
    CreateCheckpoint_Implementation();
}

// Called every frame
void AInfiniteBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    CurrentDeltaTime = DeltaTime;

    ApplyGravity(DeltaTime);
}

// Called to bind functionality to input
void AInfiniteBox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis ("Move Horizontal", this, &AInfiniteBox::MoveHorizontal);
    PlayerInputComponent->BindAxis ("Move Vertical", this, &AInfiniteBox::MoveVertical);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AInfiniteBox::JumpPressed);
}

void AInfiniteBox::MoveHorizontal(float value) 
{
    if (CurrentGravity == EGravityType::VE_DOWN || CurrentGravity == EGravityType::VE_UP)
    {
        //Tries to go to the Right and not colliding on wall or Tries to go to the left and not colliding on left
        if ((value > 0 && !bOnRightWall) || (value < 0 && !bOnLeftWall))
        {
            FVector movementVector = FVector(0, value * CurrentDeltaTime * MovementSpeed, 0);
            AddActorLocalOffset(movementVector);
        }

    }
}

void AInfiniteBox::MoveVertical(float value) 
{

    if (CurrentGravity == EGravityType::VE_LEFT || CurrentGravity == EGravityType::VE_RIGHT)
    {
        //Tries to go to the Right and not colliding on wall or Tries to go to the left and not colliding on left
        if ((value > 0 && !bOnUpWall) || (value < 0 && !bOnDownWall))
        {
            FVector movementVector = FVector(0, 0, value * CurrentDeltaTime * MovementSpeed);
            AddActorLocalOffset(movementVector);
        }

    }
}

void AInfiniteBox::ApplyGravity(float DeltaTime)
{
    FVector force = FVector(0, 0, -1);
    switch (CurrentGravity)
    {
        case EGravityType::VE_UP:
            force = FVector(0, 0, 1);
            break;
        case EGravityType::VE_RIGHT:
            force = FVector(0, 1, 0);
            break;
        case EGravityType::VE_LEFT:
            force = FVector(0, -1, 0);
            break;
    }

    GravityVector = force;

    force = force * GravityForce;
    GetCapsuleComponent()->AddForce(force, NAME_None, true);
}

void AInfiniteBox::JumpPressed()
{
    GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, FString("Jump"));
    if (bLanded)
        CommomJump();
    else
        WallJump();
}

void AInfiniteBox::CommomJump()
{
    FVector jumpVector = GravityVector * -1 * JumpForce;
    GetCapsuleComponent()->AddForce(jumpVector, NAME_None, true);
}

void AInfiniteBox::WallJump()
{
    FVector jumpVector;
    bool conditionOk = false;
    if (CurrentGravity == EGravityType::VE_DOWN || CurrentGravity == EGravityType::VE_UP)
    {
        if (bOnLeftWall)
        {
            jumpVector = GravityVector * GravityForce * 2;
            jumpVector.Y = JumpForce * 2;
            conditionOk = true;
        }
        else if (bOnRightWall)
        {
            jumpVector = GravityVector * -1 * GravityForce * 2;
            jumpVector.Y = JumpForce * -2;
            conditionOk = true;
        }
    }
    else
    {
        if (bOnUpWall)
        {
            jumpVector = GravityVector * -1 * GravityForce * 2;
            jumpVector.Z = JumpForce * -2;
            conditionOk = true;
        }
        else if (bOnDownWall)
        {
            jumpVector = GravityVector * GravityForce * 2;
            jumpVector.Z = JumpForce * 2;
            conditionOk = true;
        }
    }

    if (conditionOk)
    {
        GetCapsuleComponent()->AddForce(jumpVector, NAME_None, true);
    }
}

void AInfiniteBox::LeftBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsSelf(OtherActor))
    {
        LeftCollisionCount++;
        bOnLeftWall = true;
        if (CurrentGravity == EGravityType::VE_LEFT)
            bLanded = true;
    }
}

void AInfiniteBox::LeftEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsSelf(OtherActor))
    {
        LeftCollisionCount--;
        bOnLeftWall = false;
        if (CurrentGravity == EGravityType::VE_LEFT && LeftCollisionCount <= 0)
        {
            bLanded = false;
            LeftCollisionCount = 0;
        }
    }
}

void AInfiniteBox::RightBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsSelf(OtherActor))
    {
        RightCollisionCount++;
        bOnRightWall = true;
        if (CurrentGravity == EGravityType::VE_RIGHT)
            bLanded = true;
    }
}

void AInfiniteBox::RightEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsSelf(OtherActor))
    {
        bOnRightWall = false;
        RightCollisionCount--;
        if (CurrentGravity == EGravityType::VE_RIGHT && RightCollisionCount <= 0)
        {
            bLanded = false;
            RightCollisionCount = 0;
        }
    }
}

void AInfiniteBox::UpBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsSelf(OtherActor))
    {
        bOnUpWall = true;
        UpCollisionCount++;
        if (CurrentGravity == EGravityType::VE_UP)
            bLanded = true;

    }
}

void AInfiniteBox::UpEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsSelf(OtherActor))
    {
        UpCollisionCount--;
        bOnUpWall = false;
        if (CurrentGravity == EGravityType::VE_UP && UpCollisionCount <= 0)
        {
            bLanded = false;
            UpCollisionCount = 0;
        }

    }
}

void AInfiniteBox::DownBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsSelf(OtherActor))
    {
        DownCollisionCount++;
        bOnDownWall = true;
        if (CurrentGravity == EGravityType::VE_DOWN)
            bLanded = true;
    }
}

void AInfiniteBox::DownEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsSelf(OtherActor))
    {
        bOnDownWall = false;
        DownCollisionCount--;
        if (CurrentGravity == EGravityType::VE_DOWN && DownCollisionCount <= 0)
        {
            bLanded = false;
            DownCollisionCount = 0;
        }
    }
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

