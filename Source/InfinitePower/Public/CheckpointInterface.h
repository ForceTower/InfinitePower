// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CheckpointInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCheckpointInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ICheckpointInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    /** Returns the object to the previously created checkpoint */
    UFUNCTION (BlueprintCallable, BlueprintNativeEvent, Category = "Checkpoint Function")
    void ReturnToCheckpoint ();
    /** Create a new checkpoint to this Actor */
    UFUNCTION (BlueprintCallable, BlueprintNativeEvent, Category = "Checkpoint Function")
    void CreateCheckpoint ();

protected:
    FTransform CheckpointTransform;
	
};
