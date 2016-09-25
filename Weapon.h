// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AHellsBallsCharacter;
class AProjectile;

UCLASS()
class HELLSBALLS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	AActor* owner;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Gun;

	UPROPERTY(EditAnywhere, Category = Mesh)
		class USphereComponent* Projectilelocation;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		UClass* Projectile;

	AProjectile* bullet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* nobulletsound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		int32 namez;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		FName namew;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
		int bulletpool;

		int bullets;
		
		bool canshoot;

	void fire();

	void addbullets();
};
