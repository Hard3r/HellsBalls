// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

//class AHellsBallsCharacter;

UCLASS()
class HELLSBALLS_API AProjectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* Collisionsphere;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* ProjectMovement;

	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	TArray<AActor*> objects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	UClass* ownerino;

	AActor* owners;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float basedamage;

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(class UPrimitiveComponent* HitComp, class AActor* Actor, class UPrimitiveComponent* Other, FVector Impulse, const FHitResult & HitResult);
	
	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FComponentBeginOverlapSignature OnComponentBeginOverlap;

	UFUNCTION()
		void OnMyActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
