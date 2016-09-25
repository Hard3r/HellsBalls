// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Cotel.generated.h"
class ADrop;
class AHellsBallsCharacter;

UCLASS()
class HELLSBALLS_API ACotel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACotel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USphereComponent* col;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FComponentBeginOverlapSignature OnComponentBeginOverlap;

	UPROPERTY(BlueprintAssignable, Category = "Collision")
		FComponentEndOverlapSignature OnComponentEndOverlap;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* lava;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* soulone;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* soultwo;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* soulthree;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* soulfour;

	int32 souls;

	bool playerinrage;

	ADrop* drop;

	void showSouls(int32 number);

	void clearSouls();

	void dropSouls(int32 number);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
		TArray<UClass*> Drops;
	
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEND(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
};
