// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HellsBalls.h"
#include "HellsBallsCharacter.h"
#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Animation/AnimInstance.h"
#include "Drop.h"
#include "Engine.h"
#include "Cotel.h"
#include "Bot.h"





//////////////////////////////////////////////////////////////////////////
// AHellsBallsCharacter

float AHellsBallsCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{

	HP -= DamageAmount;
	return 0.0f;
}

AHellsBallsCharacter::AHellsBallsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	MuzzleOffset = CreateDefaultSubobject<USphereComponent>(TEXT("Muzzle"));
	MuzzleOffset->SetupAttachment(RootComponent);

	BPWeapon = NULL;
	BPSoulDrop = NULL;
	Weapon = NULL;
	HP = 100;
	maxHP = 100;
	isFiring = false;
	lastweapon = 0;

	//Check for weapon (if exist or not)
	isFound = false;

	//Has soul in hands or not
	hasSoul = false;

	col = CreateDefaultSubobject<USphereComponent>(TEXT("col"));
	col->SetupAttachment(RootComponent);
	col->OnComponentBeginOverlap.AddDynamic(this, &AHellsBallsCharacter::OnOverlap);
	col->OnComponentEndOverlap.AddDynamic(this, &AHellsBallsCharacter::OnOverlapEND);
	col->BodyInstance.SetCollisionProfileName("PlayerCol");

	botdetect = CreateDefaultSubobject<USphereComponent>(TEXT("botdetect"));
	botdetect->SetupAttachment(RootComponent);
	botdetect->OnComponentBeginOverlap.AddDynamic(this, &AHellsBallsCharacter::OnOverlapBOT);
	botdetect->OnComponentEndOverlap.AddDynamic(this, &AHellsBallsCharacter::OnOverlapENDBOT);
	botdetect->BodyInstance.SetCollisionProfileName("botdetect");

	cotel = NULL;
	nearCotel = false;
	aimed = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHellsBallsCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//InputComponent->BindAction("Change", IE_Pressed, this, &AHellsBallsCharacter::nextWeapon);
	//InputComponent->BindAction("Change", IE_Released, this, &AHellsBallsCharacter::nextWeapon2);

	InputComponent->BindAxis("MoveForward", this, &AHellsBallsCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHellsBallsCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AHellsBallsCharacter::TurnAtRate);
	//InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//InputComponent->BindAxis("LookUpRate", this, &AHellsBallsCharacter::LookUpAtRate);

	// handle touch devices
	//InputComponent->BindTouch(IE_Pressed, this, &AHellsBallsCharacter::TouchStarted);
	//InputComponent->BindTouch(IE_Released, this, &AHellsBallsCharacter::TouchStopped);

}



void AHellsBallsCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{

	
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1 && !hasSoul)
	{

		isFiring = true;
		//Jump();
		if (Weapon) {
			Weapon->fire();
		}

		if (nearCotel && cotel)
		{
			cotel->dropSouls(123123132);
		}
	}
	else {
		if (BPSoulDrop)
		{
			Weapon->Destroy();


			FRotator spawnrotation = FRotator(20, 0, 20);
			ADrop* drop = GetWorld()->SpawnActor<ADrop>(BPSoulDrop, this->GetActorLocation() + FVector(0, 0, 200), this->GetActorRotation());
			//drop->CollisionBox->AddImpulse(FVector(-140, -140, 500)*drop->CollisionBox->GetMass());
			//drop->CollisionBox->AddImpulse( (FVector(100, 0, 500) )*drop->CollisionBox->GetMass());
			
			drop->CollisionBox->AddImpulse((this->GetActorForwardVector() * 200 + FVector(0, 0, 500))*drop->CollisionBox->GetMass());



			if (Weapons[lastweapon])
			{
				Weapon = Weapons[lastweapon];
				Weapons[lastweapon]->canshoot = true;
				const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapons[lastweapon]->namew);
				socket->AttachActor(Weapons[lastweapon], GetMesh());
			}


			hasSoul = false;
		}
	}
}

void AHellsBallsCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1 && !hasSoul)
	{
		//StopJumping();
		isFiring = false;
	}
}

void AHellsBallsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information

	if (!aimed) 
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}

	
}

void AHellsBallsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHellsBallsCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BPWeapon) {

		Weapon = GetWorld()->SpawnActor<AWeapon>(BPWeapon, FVector(0), FRotator(0));


		if (Weapon) {
			Weapons.Add(Weapon);
			Weapon->canshoot = true;

			Weapon->owner = this;

			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
			socket->AttachActor(Weapon, GetMesh());

		}
	}



/*
	if (BPWeapon) {
		Weapon = GetWorld()->SpawnActor<AWeapon>(BPWeapon, FVector(0, 0, -1000), FRotator());
		if (Weapon) {
			Weapons.Add(Weapon);
			Weapon->canshoot = true;
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
			socket->AttachActor(Weapon, GetMesh());
		}
	}
*/
	//if (BPKalash) {
		//Weapon->Destroy();

		//NextWeapon = GetWorld()->SpawnActor<AWeapon>(BPKalash, FVector(0), FRotator(0));
		//Weapons.Add(NextWeapon);
	//}

}

//Na vhod brat drygoy weapon
void AHellsBallsCharacter::nextWeapon()
{
	//Weapon->SetActorLocation(FVector(0));
	//Weapon->canshoot = false;
	if (!hasSoul) {
		int32 index = Weapons.Find(Weapon);

		Weapons[index]->SetActorLocation(FVector(0, 0, -1000));
		Weapons[index]->canshoot = false;

		if (index == Weapons.Num() - 1)
		{
			Weapon = Weapons[0];
			if (Weapon) {
				//Nahya const?
				const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
				socket->AttachActor(Weapon, GetMesh());
				Weapon->canshoot = true;
			}
		}
		else {
			Weapon = Weapons[index + 1];
			if (Weapon) {
				//Nahya const?
				const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
				socket->AttachActor(Weapon, GetMesh());
				Weapon->canshoot = true;
			}
		}
	}
	/*
	
	if (BPKalash) {
		//Weapon->Destroy();
	
		Weapon = GetWorld()->SpawnActor<AWeapon>(BPKalash, FVector(0), FRotator(0));
		
		if (Weapon) {
			//Weapons.Add(Weapon);
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
			socket->AttachActor(Weapon, GetMesh());
		}
	} */
}

void AHellsBallsCharacter::fire()
{

	if (!hasSoul)
	{

		isFiring = true;
		//Jump();
		if (Weapon) {
			Weapon->fire();
		}

		if (nearCotel && cotel)
		{
			cotel->dropSouls(123123132);
		}
	}
	else {
		if (BPSoulDrop)
		{
			Weapon->Destroy();


			FRotator spawnrotation = FRotator(20, 0, 20);
			ADrop* drop = GetWorld()->SpawnActor<ADrop>(BPSoulDrop, this->GetActorLocation() + FVector(0, 0, 200), this->GetActorRotation());
			//drop->CollisionBox->AddImpulse(FVector(-140, -140, 500)*drop->CollisionBox->GetMass());
			//drop->CollisionBox->AddImpulse( (FVector(100, 0, 500) )*drop->CollisionBox->GetMass());

			drop->CollisionBox->AddImpulse((this->GetActorForwardVector() * 200 + FVector(0, 0, 500))*drop->CollisionBox->GetMass());



			if (Weapons[lastweapon])
			{
				Weapon = Weapons[lastweapon];
				Weapons[lastweapon]->canshoot = true;
				const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapons[lastweapon]->namew);
				socket->AttachActor(Weapons[lastweapon], GetMesh());
			}


			hasSoul = false;
		}
	}

}



bool AHellsBallsCharacter::hasSouls()
{
	return hasSoul;
}

void AHellsBallsCharacter::takeSoul(UClass* item)
{

	if (item)
	{
		int32 index = Weapons.Find(Weapon);
		Weapons[index]->canshoot = false;
		Weapons[index]->SetActorLocation(FVector(0, 0, -1000));
		lastweapon = index;

		Weapon = GetWorld()->SpawnActor<AWeapon>(item, FVector(0, 0, -1000), FRotator(0));
		Weapon->canshoot = false;

		Weapon->owner = this;

		if (Weapon) {
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
			socket->AttachActor(Weapon, GetMesh());
		}

	}

}

void AHellsBallsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

int AHellsBallsCharacter::getBulletspool()
{
	if (Weapon)
	{
		return Weapon->bulletpool;
	}

	return 0;
}

void AHellsBallsCharacter::addWeapon(UClass* newWeapon, FName weapname)
{
	int32 index = Weapons.Find(Weapon);

	for (int i = 0; i < Weapons.Num(); i++) 
	{
		if (Weapons[i]->namew == weapname)
		{
			Weapons[i]->addbullets();
			isFound = true;
		}
	}

	if (isFound)
	{
		isFound = false;
		return;
	}
	else {
		if (newWeapon) {
			Weapons[index]->canshoot = false;
			Weapons[index]->SetActorLocation(FVector(0, 0, -1000));
			//Weapon->canshoot = false;
			//Weapon->SetActorLocation(FVector(0));

			Weapon = GetWorld()->SpawnActor<AWeapon>(newWeapon, FVector(0, 0, -1000), FRotator(0));
			Weapons.Add(Weapon);
			
			if (Weapon) {
				const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
				socket->AttachActor(Weapon, GetMesh());
				Weapon->canshoot = true;

				Weapon->owner = this;
			}
		}
	}

}

void AHellsBallsCharacter::addAmmo()
{
	for (int i = 0; i < Weapons.Num(); i++)
	{
			Weapons[i]->addbullets();
	}
}

void AHellsBallsCharacter::addHealth()
{

	HP = maxHP;

}

bool AHellsBallsCharacter::getFiring()
{
	return isFiring;
}

void AHellsBallsCharacter::stopFiring()
{
	isFiring = false;
}

float AHellsBallsCharacter::getHP()
{
	return (HP * 100) / maxHP;
}

int AHellsBallsCharacter::getBullets()
{

	if (Weapon) {
		return Weapon->bullets;
	}

	return 0;
}



void AHellsBallsCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHellsBallsCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void AHellsBallsCharacter::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, OtherActor->GetName());

	cotel = Cast<ACotel>(OtherActor);

	if (cotel)
	{
		Weapon->canshoot = false;
		//GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, cotel->GetName());
		nearCotel = true;

	}
}

void AHellsBallsCharacter::OnOverlapEND(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	cotel = Cast<ACotel>(OtherActor);

	if (cotel)
	{
		Weapon->canshoot = true;
		//GEngine->AddOnScreenDebugMessage(0, 3, FColor::Red, cotel->GetName());
		nearCotel = false;

	}
}

void AHellsBallsCharacter::OnOverlapBOT(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABot* bot = Cast<ABot>(OtherActor);
	//GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Black, OtherActor->GetName());
	
	int32 index = Bots.AddUnique(bot);
	
	if (index >= 0) {
		aimed = true;
		//GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Black, "BOT ADDED");

		
	}
	

}

void AHellsBallsCharacter::OnOverlapENDBOT(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	ABot* bot = Cast<ABot>(OtherActor);

	
	int32 index = Bots.Remove(bot);

	//if (index > 0) {GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Black, "BOT REMOVED"); }
	
	
	

	if (Bots.Num() <= 0) { aimed = false; }

}

void AHellsBallsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (aimed)
	{
		
		

		ABot* nearestbot;
		FVector nearestbotrange;

		if (Bots.Num() > 0) 
		{ 
			nearestbot = Bots[0]; 
			nearestbotrange = nearestbot->GetActorLocation() - this->GetActorLocation();
		
		}

		 
		//FRotator toPlayerRotation = toPlayer.Rotation();
		//toPlayerRotation.Pitch = 0;
		//this->SetActorRotation(toPlayerRotation);
		//RootComponent->SetWorldRotation(toPlayerRotation);


		//GOVNO
		/*
		for (int i = 0; i < Bots.Num(); i++)
		{
			FVector toPlayer = Bots[i]->GetActorLocation() - this->GetActorLocation();
			toPlayer.Normalize();

			if (toPlayer.Size() < nearestbotrange.Size())
			{
				nearestbot = Bots[i];
				nearestbotrange = toPlayer;
			}
			
		}*/

		
		FRotator toPlayerRotation = nearestbotrange.Rotation();
		toPlayerRotation.Pitch = 0;
		this->SetActorRotation(toPlayerRotation);
	}


}

AWeapon * AHellsBallsCharacter::getWeapon()
{
	return Weapon;
}
