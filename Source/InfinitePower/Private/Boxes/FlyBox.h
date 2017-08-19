// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "../CheckpointInterface.h"

#include "FlyBox.generated.h"

UCLASS()
class AFlyBox : public AActor, public ICheckpointInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //Checkpoint Interface Declaration
    virtual void ReturnToCheckpoint_Implementation () override;
    virtual void CreateCheckpoint_Implementation () override;

private:
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* CubeStaticMeshComponent;
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    USceneComponent* PropellerSceneComponent;
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* PropellerOneComponent;
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* PropellerTwoComponent;
    UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* PropellerThreeComponent;

    void ConstructorFinderDefaults ();
	
	
};
