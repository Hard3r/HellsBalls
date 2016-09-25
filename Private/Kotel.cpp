// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Kotel.h"


// Sets default values
AKotel::AKotel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	

}

// Called when the game starts or when spawned
void AKotel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKotel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

