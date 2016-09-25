// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Bot.h"
#include "Perception/PawnSensingComponent.h"
#include "HellsBallsCharacter.h"
#include "AIControllerCPLUS.h"
#include "AIController.h"
#include "Engine.h"
#include "Weapon.h"
#include "Drop.h"



// Sets default values
ABot::ABot()
{

	sense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sense"));
	sense->OnSeePawn.AddDynamic(this, &ABot::OnSeePawn);
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	inRange = false;
	isMoving = false;
	switchdirection = false;
	switchstrafe = false;
	deathanim = false;


	col = CreateDefaultSubobject<USphereComponent>(TEXT("collis"));
	col->SetupAttachment(RootComponent);
	col->OnComponentBeginOverlap.AddDynamic(this, &ABot::OnOverlap);
	col->OnComponentEndOverlap.AddDynamic(this, &ABot::OnOverlapEND);

	shootrange = CreateDefaultSubobject<USphereComponent>(TEXT("shootrange"));
	shootrange->SetupAttachment(RootComponent);
	shootrange->OnComponentBeginOverlap.AddDynamic(this, &ABot::OnOverlapShoot);
	shootrange->OnComponentEndOverlap.AddDynamic(this, &ABot::OnOverlapENDShoot);

	MuzzleOffset = CreateDefaultSubobject<USphereComponent>(TEXT("Muzzle"));
	MuzzleOffset->SetupAttachment(RootComponent);

	//EnemyPC = NULL;
	
	shootDelay = 30;
	deathdelay = 50;
	countshoot = 3;
	isDead = false;

	HP = 100;
	maxHP = 100;

	BDrop = NULL;

	//BDrop = LoadClass<UClass>(NULL, TEXT("HellsBalls/Content/Weapons/Commons/soul/SoulDropBP"), NULL, LOAD_None, NULL);

	death = NULL;
	Deathsound = NULL;
	
}

void ABot::OnOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (OtherActor == player)
	{
		inRange = true;
	}

}

void ABot::OnOverlapEND(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (OtherActor == player)
	{
		inRange = false;

		if (kydabejat && kydabejat2){ 
		//this->patrol(kydabejat, kydabejat2, player);
		}
	}

}

void ABot::OnOverlapShoot(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (OtherActor == player)
	{
		inShootRange = true;
	}

}

void ABot::OnOverlapENDShoot(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (OtherActor == player)
	{
		inShootRange = false;
		shootDelay = 30;
	}
}

bool ABot::getdead()
{
	return isDead;
}

// Called when the game starts or when spawned
void ABot::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector velocity = GetMovementComponent()->GetPawnOwner()->GetVelocity();
	


	//if (inRange && !inShootRange)
	if (inRange && !inShootRange)
	{
		AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!player) { return; }

		FVector toPlayer = player->GetActorLocation() - this->GetActorLocation();
		toPlayer.Normalize();

		AddMovementInput(toPlayer, 100 * DeltaTime);

		FRotator toPlayerRotation = toPlayer.Rotation();
		//toPlayerRotation.Pitch = 0;
		this->SetActorRotation(toPlayerRotation);
		//RootComponent->SetWorldRotation(toPlayerRotation);
	}
	else if (inShootRange && !isDead)
	{
		shootDelay++ ;

		AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!player) { return; }


		FVector toPlayer = player->GetActorLocation() - this->GetActorLocation();
		toPlayer.Normalize();

		
		

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0;
		this->SetActorRotation(toPlayerRotation);
		//RootComponent->SetWorldRotation(toPlayerRotation);

		FRotator strafe = toPlayerRotation;
		//strafe.Yaw += 80;

		if (shootDelay < 30)
		{

				switchstrafe ? strafe.Yaw += 80 : strafe.Yaw -= 80;				
				
			//switchstrafe ? strafe.Yaw += 80 : strafe.Yaw -= 80 ;
			this->SetActorRotation(toPlayerRotation);
			AddMovementInput(strafe.Vector(), 1000 * DeltaTime);

		}
		

		if (shootDelay > 30)
		{
			//switchstrafe ? strafe.Yaw += 40 : strafe.Yaw -= 80;
			toPlayerRotation.Pitch = 0;
			this->SetActorRotation(toPlayerRotation);
			Weapon->fire();
			shootDelay = 0;
			countshoot++;

			if (countshoot >= 3)
			{
				switchstrafe = !switchstrafe;
				countshoot = 0;
			}
		}
	}
	

	if (!inRange && !isMoving && kydabejat && kydabejat2) {
		//this->patrol(kydabejat, kydabejat2, enemy);

	}

	//if (GetMovementComponent()->GetPawnOwner()->GetVelocity().Size() > 0)
	//{
	//	isMoving = true;
	//}
	//else
	//{
	//	isMoving = false;
	//}

	if (HP <= 0)
	{
		//play aimation
		isDead = true;
		deathdelay--;
		Weapon->Destroy();
		deathanim = true;

		
	}


	if (isDead && deathdelay == 40)
	{
		if (Deathsound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, Deathsound, GetActorLocation());
		}

		if (BDrop)
		{
			ADrop* drop = GetWorld()->SpawnActor<ADrop>(BDrop, this->GetActorLocation() + FVector(0, 0, 200), this->GetActorRotation());
			//drop->CollisionBox->AddImpulse(FVector(-140, -140, 500)*drop->CollisionBox->GetMass());
			//drop->CollisionBox->AddImpulse( (FVector(100, 0, 500) )*drop->CollisionBox->GetMass());

			drop->CollisionBox->AddImpulse((this->GetActorForwardVector() * 200 + FVector(0, 0, 500))*drop->CollisionBox->GetMass());
		}

		//spawn mogilky
		//drop kakahy

		if (death)
		{
		GetMesh()->PlayAnimation(death, false);
		}
		
		

		isDead = false;
		
		
	}
	else if (isDead && deathdelay <= 0)
	{
		this->Destroy();
	}




}

// Called to bind functionality to input
void ABot::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABot::PostInitializeComponents()
{

	Super::PostInitializeComponents();

	sense->OnSeePawn.AddDynamic(this, &ABot::OnSeePawn);

	if (BPWeapon) {
		Weapon = GetWorld()->SpawnActor<AWeapon>(BPWeapon, FVector(0, 0, -1000), FRotator());
		if (Weapon) {
			//Weapons.Add(Weapon);
			Weapon->canshoot = true;
			Weapon->owner = this;
			const USkeletalMeshSocket *socket = GetMesh()->GetSocketByName(Weapon->namew);
			socket->AttachActor(Weapon, GetMesh());
		}
	}
	//BDrop = LoadClass<UClass>(NULL, TEXT("/Content/Weapons/Commons/soul/SoulDropBP"), NULL, LOAD_None, NULL);
	spawnlcoation = this->GetActorLocation();
}

void ABot::OnSeePawn(APawn* OtherPawn)
{

	//GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, OtherPawn->GetName());
	
	//AAIControllerCPLUS* EnemyPC = Cast<AAIControllerCPLUS>(this->GetOwner());
	AAIControllerCPLUS* EnemyPC = Cast<AAIControllerCPLUS>(this->GetController());

	//AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	//if (EnemyPC && player && player == OtherPawn)
		if (player == OtherPawn)

	{
		inRange = true;
		//EnemyPC->MoveToActor(enemy, 5.f, true, true, true, 0, true);
		//EnemyPC->MoveTo(player);
		
		
	}

}

void ABot::moveToTargets(ATargetPoint * target)
{
	AAIControllerCPLUS* EnemyPC = Cast<AAIControllerCPLUS>(this->GetController());
	EnemyPC->MoveToActor(target, 5.f, true, true, true, 0, true);

	EnemyPC = NULL;
	
}

void ABot::patrol(ATargetPoint * kydabejat1, ATargetPoint * kydabejat2, AHellsBallsCharacter * target)
{
	AAIControllerCPLUS* EnemyPC = Cast<AAIControllerCPLUS>(this->GetController());

	

	if (switchdirection) 
	{

		FVector toPlayer = kydabejat1->GetActorLocation() - this->GetActorLocation();
		toPlayer.Normalize();

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0;
		this->SetActorRotation(toPlayerRotation);

		EnemyPC->MoveTo(kydabejat1);
		switchdirection = !switchdirection;
	}
	else
	{

		FVector toPlayer = kydabejat2->GetActorLocation() - this->GetActorLocation();
		toPlayer.Normalize();

		FRotator toPlayerRotation = toPlayer.Rotation();
		toPlayerRotation.Pitch = 0;
		this->SetActorRotation(toPlayerRotation);
		//EnemyPC->MoveToActor(kydabejat2, 5.f, true, true, true, 0, true);
		EnemyPC->MoveTo(kydabejat2);
		switchdirection = !switchdirection;
	}
	EnemyPC = NULL;
}

void ABot::stopMovement()
{

	AAIControllerCPLUS* EnemyPC = Cast<AAIControllerCPLUS>(this->GetController());

	//EnemyPC->StopMovement();
	//EnemyPC->MoveTo(this);
}

float ABot::getHP()
{
	return (HP * 100) / maxHP;
}

float ABot::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{

	HP -= DamageAmount;
	return 0.0f;
}

