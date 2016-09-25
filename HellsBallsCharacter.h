// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"
#include "HellsBallsCharacter.generated.h"

class AWeapon;
class ACotel;
class ABot;

UCLASS(config=Game)
class AHellsBallsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);


public:
	AHellsBallsCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USphereComponent* MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UClass* BPWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UClass* BPKalash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UClass* BPSoulDrop;

	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_properties")
	float maxHP;

	TArray<AWeapon*> Weapons;
	int32 lastweapon;

	AWeapon* Weapon;

	AWeapon* NextWeapon;

	bool isFiring;
	bool isFound;
	bool hasSoul;

	UFUNCTION(BlueprintCallable, Category = "Attack")
		bool getFiring();

	UFUNCTION(BlueprintCallable, Category = "Attack")
		void stopFiring();

	UFUNCTION(BlueprintCallable, Category = "HUDprop")
		float getHP();

	UFUNCTION(BlueprintCallable, Category = "HUDprop")
		int getBullets();

	UFUNCTION(BlueprintCallable, Category = "HUDprop")
		int getBulletspool();

	void addWeapon(UClass* Weapon, FName weapname);
	void addAmmo();
	void addHealth();
	UFUNCTION(BlueprintCallable, Category = "Soul")
	bool hasSouls();

	void takeSoul(UClass* item);


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void nextWeapon();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void fire();


protected:
	virtual void PostInitializeComponents() override;

	
	

	

	
	
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//Handle inputs for near items
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USphereComponent* col;

	ACotel* cotel;

	bool nearCotel;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEND(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* botBehavior;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USphereComponent* botdetect;

	UFUNCTION()
		void OnOverlapBOT(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapENDBOT(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<ABot*> Bots;

	bool aimed;

	virtual void Tick(float DeltaSeconds) override; 

	UFUNCTION(BlueprintCallable, Category = "HUDprop")
	AWeapon* getWeapon();
};

