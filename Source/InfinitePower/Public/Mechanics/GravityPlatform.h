// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/Characters/InfiniteBox.h"
#include "GravityPlatform.generated.h"

UCLASS()
class INFINITEPOWER_API AGravityPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityPlatform();

    UFUNCTION(BlueprintCallable)
        void ChangeGravityModifier(EGravityType NewGravity);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    void ConstructorFinderDefaults();

    UFUNCTION()
        void OnPlatformBeginOverlap(class UPrimitiveComponent* OverlapedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
    UFUNCTION()
        void ColorManager();

private:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
        USceneComponent* DefaultSceneRoot;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
        UStaticMeshComponent* Platform;
    UPROPERTY()
        UMaterialInstanceDynamic* DynamicMaterial;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity", meta = (AllowPrivateAccess = "true"))
        EGravityType GravityModifier;
};
