// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Bot.generated.h"


class AWeapon;

UCLASS()
class HELLSBALLS_API ABot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABot();

/*
Сделать сферу для ренджа стрельбы и сделать сферу для ренджа чтоб убежать
Use controller Yaw чтобы стрейфить и отрубить мышку
*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UClass* BPWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UClass* BDrop;


	AWeapon* Weapon;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* botBehavior;

	UPROPERTY(EditAnywhere, Category = "AI")
		class ATargetPoint* kydabejat;

	UPROPERTY(EditAnywhere, Category = "AI")
		class ATargetPoint* kydabejat2;

	UPROPERTY(EditAnywhere, Category = "AI")
		class AHellsBallsCharacter* enemy;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USphereComponent* col;


	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USphereComponent* shootrange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USphereComponent* MuzzleOffset;


	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEND(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnOverlapShoot(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapENDShoot(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UPROPERTY(EditAnywhere, Category = "AIq")
		//class AAIControllerCPLUS* controller;

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool getdead();
		
		bool isDead;
	bool inRange;
	bool isMoving;
	bool switchdirection;
	bool inShootRange;
	bool switchstrafe;
	uint8 countshoot;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Main")
	class UPawnSensingComponent* sense;
	
	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	void moveToTargets(ATargetPoint* target);

	void patrol(ATargetPoint* kydabejat1, ATargetPoint* kydabejat2, AHellsBallsCharacter* target);

	float shootDelay;

	void stopMovement();

	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float maxHP;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float getHP();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	float deathdelay;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimationAsset* death;

	bool deathanim;

	FVector spawnlcoation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* Deathsound;
};
