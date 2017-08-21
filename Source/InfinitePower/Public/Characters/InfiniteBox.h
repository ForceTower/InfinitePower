// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

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

    UFUNCTION()
        void JumpPressed();

    void FORCEINLINE CommomJump();
    void FORCEINLINE WallJump();
    
    void FORCEINLINE ApplyGravity(float DeltaTime);

    UFUNCTION()
        void LeftBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
        void LeftEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    UFUNCTION()
        void RightBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
        void RightEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    UFUNCTION()
        void UpBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
        void UpEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    UFUNCTION()
        void DownBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
        void DownEndOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    void ConstructorFinderDefaults();
    bool FORCEINLINE IsSelf(class AActor* OtherActor) { return OtherActor == this;  }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //Checkpoint Interface Declaration
    virtual void ReturnToCheckpoint_Implementation() override;
    virtual void CreateCheckpoint_Implementation() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        EGravityType StartGravity = EGravityType::VE_DOWN;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float MovementSpeed = 620.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float JumpForce = 21000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float GravityForce = 980.0f;
    UPROPERTY()
        FVector GravityVector;
    UPROPERTY()
        float CurrentDeltaTime;
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
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement Component", meta = (AllowPrivateAccess = "true"))
        UCharacterMovementComponent* MovementComponent;

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

    UPROPERTY()
        uint16 UpCollisionCount = 0;
    UPROPERTY()
        uint16 DownCollisionCount = 0;
    UPROPERTY()
        uint16 RightCollisionCount = 0;
    UPROPERTY()
        uint16 LeftCollisionCount = 0;
};
