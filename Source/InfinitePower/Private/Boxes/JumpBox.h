// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../CheckpointInterface.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "JumpBox.generated.h"

UCLASS()
class AJumpBox : public AActor, public ICheckpointInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UFUNCTION ()
    void OnBoxComponentBeginOverlap (class UPrimitiveComponent* overlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
    //Checkpoint Interface Declaration
    virtual void ReturnToCheckpoint_Implementation () override;
    virtual void CreateCheckpoint_Implementation () override;

private:
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* CubeStaticMeshComponent;
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UBoxComponent* BoxCollisionComponent;

    void ConstructorFinderDefaults ();
};
