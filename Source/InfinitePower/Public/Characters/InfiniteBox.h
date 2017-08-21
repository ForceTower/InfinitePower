// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../CheckpointInterface.h"
#include "InfiniteBox.generated.h"

UENUM(BlueprintType)
enum class EGravityType : uint8
{
    VE_DOWN     UMETA(DisplayName = "Down Gravity"),
    VE_UP       UMETA(DisplayName = "Up Gravity"),
    VE_LEFT     UMETA(DisplayName = "Left Gravity"),
    VE_RIGHT    UMETA(DisplayName = "Right Gravity")
};

UCLASS()
class INFINITEPOWER_API AInfiniteBox : public ACharacter, public ICheckpointInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInfiniteBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION ()
        void MoveHorizontal (float value);
    UFUNCTION ()
        void MoveVertical (float value);

private:
    void ContructorFinderDefaults();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //Checkpoint Interface Declaration
    virtual void ReturnToCheckpoint_Implementation() override;
    virtual void CreateCheckpoint_Implementation() override;

private:
    UPROPERTY()
        bool bLanded;
    UPROPERTY()
        bool bOnRightWall;
    UPROPERTY()
        bool bOnLeftWall;
    UPROPERTY()
        bool bOnUpWall;
    UPROPERTY()
        bool bOnDownWall;
    UPROPERTY()
        EGravityType CurrentGravity;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
        UStaticMeshComponent* CubeMesh;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
        UCameraComponent* Camera;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision Detectors", meta = (AllowPrivateAccess = "true"))
        UBoxComponent* UpCollision;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision Detectors", meta = (AllowPrivateAccess = "true"))
        UBoxComponent* DownCollision;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision Detectors", meta = (AllowPrivateAccess = "true"))
        UBoxComponent* LeftCollision;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision Detectors", meta = (AllowPrivateAccess = "true"))
        UBoxComponent* RightCollision;
};
