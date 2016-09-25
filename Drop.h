// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Drop.generated.h"

UCLASS()
class HELLSBALLS_API ADrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrop();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Index of dropped item
	//1 - weapon
	//2 - ammo
	//3 - health
	//4 - collectable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		FName namew;
	
	//Blueprint of weapon to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UClass* BPItem;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Meshes")
	USkeletalMeshComponent* Items;

	UPROPERTY(VisibleDefaultsOnly, Category = "Meshes")
	UBoxComponent* CollisionBox;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FComponentBeginOverlapSignature OnComponentBeginOverlap;

	UFUNCTION()
	void OnMyActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
