// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteBox.h"


// Sets default values
AInfiniteBox::AInfiniteBox()
{
	PrimaryActorTick.bCanEverTick = true;



}

void AInfiniteBox::ContructorFinderDefaults()
{

}

// Called when the game starts or when spawned
void AInfiniteBox::BeginPlay()
{
	Super::BeginPlay();
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

