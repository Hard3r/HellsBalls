// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class ABot;

UCLASS()
class HELLSBALLS_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual void PostInitializeComponents() override;


	UPROPERTY(EditAnywhere, Category = "Bot")
		UClass* bot;

	ABot* botref;

	

	UPROPERTY(EditAnywhere, Category = "Bot")
		class ATargetPoint* patrolone;

	UPROPERTY(EditAnywhere, Category = "Bot")
		class ATargetPoint* patroltwo;

	bool botisdead;

	void spawnBot();

	float delay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimationAsset* death;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* Deathsound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UClass* drop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class AActor* templateact;

	
};
