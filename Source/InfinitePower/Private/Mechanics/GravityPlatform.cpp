// Fill out your copyright notice in the Description page of Project Settings.

#include "GravityPlatform.h"
#include "ConstructorHelpers.h"
#include "Linker.h"


// Sets default values
AGravityPlatform::AGravityPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
    DefaultSceneRoot->SetupAttachment(RootComponent);

    Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
    Platform->SetupAttachment(DefaultSceneRoot);
    Platform->SetRelativeScale3D(FVector(3.5, 3.5, 0.5));
    Platform->bGenerateOverlapEvents = true;
    Platform->OnComponentBeginOverlap.AddDynamic(this, &AGravityPlatform::OnPlatformBeginOverlap);

    ConstructorFinderDefaults();
}

void AGravityPlatform::OnConstruction(const FTransform & Transform)
{
    DynamicMaterial = Platform->CreateDynamicMaterialInstance(0);
    ColorManager();
}

void AGravityPlatform::ConstructorFinderDefaults()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (StaticMesh.Object)
        Platform->SetStaticMesh(StaticMesh.Object);

    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("MaterialInstanceConstant'/Game/Materials/GlowTron/M_GlowTron_Platform.M_GlowTron_Platform'"));
    if (Material.Object)
        Platform->SetMaterial(0, Material.Object);
}

// Called when the game starts or when spawned
void AGravityPlatform::BeginPlay()
{
	Super::BeginPlay();
    ColorManager();
}

void AGravityPlatform::ChangeGravityModifier(EGravityType NewGravity)
{
    GravityModifier = NewGravity;
    ColorManager();
}

void AGravityPlatform::OnPlatformBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AInfiniteBox* box = Cast<AInfiniteBox>(OtherActor);
    if (box)
    {
        box->ChangeGravity(GravityModifier);
    }
}

void AGravityPlatform::ColorManager()
{
    FLinearColor color;
    switch (GravityModifier)
    {
        case EGravityType::VE_DOWN:
            color = FLinearColor(0, 0.18, 1);
            break;
        case EGravityType::VE_UP:
            color = FLinearColor::Green;
            break;
        case EGravityType::VE_LEFT:
            color = FLinearColor::Yellow;
            break;
        case EGravityType::VE_RIGHT:
            color = FLinearColor::Red;
            break;
        case EGravityType::VE_NONE:
            color = FLinearColor::White;
            break;
    }

    DynamicMaterial->SetVectorParameterValue(FName("Color"), color);
}


