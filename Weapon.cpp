// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Weapon.h"
#include "HellsBallsCharacter.h"
#include "Projectile.h"
#include "Engine.h"



// Sets default values
AWeapon::AWeapon()
{
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(RootComponent);

	Projectilelocation = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnLocation"));
	Projectilelocation->SetupAttachment(RootComponent);

	 
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	namez = 0;
	bulletpool = 0;
	bullets = 0;
	canshoot = false;
	
	

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	bullets = bulletpool;

}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWeapon::fire()
{
	//Simple projectile
	if (namez != 3) {
	// try and fire a projectile
	if (Projectile != NULL && bullets > 0 && canshoot)
	{
		AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		//const FRotator SpawnRotation = player->GetActorRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		//const FVector SpawnLocation = Projectilelocation->GetComponentLocation();

		//FVector SpawnLocation = this->GetActorLocation();
		//FVector SpawnLocation2 = owner->MuzzleOffset->GetComponentLocation();

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			//World->SpawnActor<AProjectile>(Projectile, SpawnLocation2, SpawnRotation);
			//bullet->owner = this;

			FRotator SpawnRotation = owner->GetActorRotation();
			//SpawnRotation.Yaw -= 5.f;
			

			bullet = World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);
			//World->SpawnActor<AProjectile>(bullet, this->GetActorLocation(), owner->GetActorRotation());

			//bullet->owner = owner;
			//bullet->setOwner(owner);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, bullet->owner->GetName());
			
		}

		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}


		bullets--;
	}
	else if (Projectile != NULL && bullets == 0 && canshoot) {
		if (nobulletsound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, nobulletsound, GetActorLocation());
			}
		}
	}
	else {

		//shootgun projectile
		if (Projectile != NULL && bullets > 0 && canshoot)
		{
			AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

			//const FRotator SpawnRotation = player->GetActorRotation();
			FRotator SpawnRotation = player->GetActorRotation();
			SpawnRotation.Yaw -= 20.f;

			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = Projectilelocation->GetComponentLocation();
			//FVector SpawnLocation2 = player->MuzzleOffset->GetComponentLocation();

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);

				SpawnRotation.Yaw += 5.f;
				SpawnRotation.Pitch += 5.f;
				World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);

				SpawnRotation = player->GetActorRotation();
				SpawnRotation.Yaw -= 5.f;
				SpawnRotation.Pitch += 5.f;
				World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);

				SpawnRotation = player->GetActorRotation();
				SpawnRotation.Yaw += 5.f;
				SpawnRotation.Pitch -= 5.f;
				World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);

				SpawnRotation = player->GetActorRotation();
				SpawnRotation.Yaw -= 5.f;
				SpawnRotation.Pitch -= 5.f;
				World->SpawnActor<AProjectile>(Projectile, this->GetActorLocation(), SpawnRotation);

			}

			if (FireSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}


			bullets--;
		}
		else if (Projectile != NULL && bullets == 0 && canshoot) {
			if (nobulletsound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(this, nobulletsound, GetActorLocation());
			}
		}
	}
}

void AWeapon::addbullets()
{
	bullets = bulletpool;
}

