// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"

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
    VE_RIGHT    UMETA(DisplayName = "Right Gravity"),
    VE_NONE     UMETA(DisplayName = "No Effect")
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
    virtual void OnConstruction(const FTransform& Transform) override;

    UFUNCTION ()
        void MoveHorizontal (float value);
    UFUNCTION ()
        void MoveVertical (float value);

    UFUNCTION()
        void JumpPressed();
    
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
    UFUNCTION()
        void CameraGravitySwitchUpdate(float delta);

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

    UFUNCTION(BlueprintCallable)
    /** Changes The Gravity that affects the Infinite Box */
    void ChangeGravity(EGravityType NewGravity);


    void FORCEINLINE CommomJump();
    void FORCEINLINE WallJump();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        EGravityType StartGravity = EGravityType::VE_DOWN;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float MovementSpeed = 620.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float JumpForce = 25000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
        float GravityForce = 980.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline Curves", meta = (AllowPrivateAccess = "true"))
        UCurveFloat* CameraGravitySwitchCurve;

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
    UPROPERTY()
        UMaterialInstanceDynamic* DynamicMaterialInstance;

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
    UPROPERTY()
        FVector LastMovementVector;

    /** Camera Gravity Switch Perspective View */
    UPROPERTY()
        UTimelineComponent* CameraGravitySwitch;
    FOnTimelineFloat InterpCameraGravitySwitchFloatFunction {};
    FOnTimelineEvent InterpCameraGravitySwitchEventFunction {};
    UPROPERTY()
        FVector StartCameraSwitchLocation;
    UPROPERTY()
        FVector EndCameraSwitchLocation;
    UPROPERTY()
        FRotator StartCameraSwitchRotator;
    UPROPERTY()
        FRotator EndCameraSwitchRotator;

    //Camera Vectors
    FVector DownLocation = FVector(-900, 0, 150);
    FRotator DownRotator = FRotator(-20, 0, 0);

    FVector UpLocation = FVector(-900, 0, -150);
    FRotator UpRotator = FRotator(20, 0, 0);

    FVector LeftLocation = FVector(-900, 150, 0);
    FRotator LeftRotator = FRotator(0, -20, 0);

    FVector RightLocation = FVector(-900, -150, 0);
    FRotator RightRotator = FRotator(0, 20, 0);

    FLinearColor StartSwitchColor;
    FLinearColor EndSwitchColor;
    FLinearColor CurrentColor;
};
