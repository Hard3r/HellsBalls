// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Kotel.generated.h"

UCLASS()
class HELLSBALLS_API AKotel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKotel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
