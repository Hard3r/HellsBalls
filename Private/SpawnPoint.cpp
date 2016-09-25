// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "SpawnPoint.h"
#include "Bot.h"
#include "HellsBallsCharacter.h"


// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	botisdead = false;
	
	delay = 300;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void ASpawnPoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	
	if (botref && botref->isDead) {

		botref->Destroy();
		botisdead = true;
		}

	if (botisdead)
	{
		delay--;
		//this->spawnBot();
		//botisdead = false;
	}

	if (delay == 0)
	{
		this->spawnBot();
		botisdead = false;
		delay = 300;
	}
	
	
	


}

void ASpawnPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	this->spawnBot();

}

void ASpawnPoint::spawnBot()
{
	if(bot)
	{
		FActorSpawnParameters spawnpoaram;

		if (templateact)
		{
			spawnpoaram.Template = templateact;
			botref = GetWorld()->SpawnActor<ABot>(bot, this->GetActorLocation(), FRotator(0), spawnpoaram);
		}
		else {
			botref = GetWorld()->SpawnActor<ABot>(bot, this->GetActorLocation(), FRotator(0));
		}
		
		
		//botref = GetWorld()->SpawnActor<ABot>(bot, this->GetActorLocation(), FRotator(0));
		AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (patrolone && patroltwo) 
		{
			//botref->kydabejat = patrolone;
			//botref->kydabejat2 = patroltwo;
			//botref->patrol(patrolone, patroltwo, player);


		}

		if (patrolone)
		{
			//botref->moveToTargets(botref->kydabejat);
		}
		
	

		//player2->enemy = player;

	}

}


