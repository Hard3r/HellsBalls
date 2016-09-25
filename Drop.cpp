// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Drop.h"
#include "Engine.h"
#include "HellsBallsCharacter.h"


// Sets default values
ADrop::ADrop()
{


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollBox"));
	//CollisionBox->AttachTo(RootComponent);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADrop::OnMyActorHit);
	RootComponent = CollisionBox;

	Items = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Item"));
	Items->AttachTo(RootComponent);
	
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	index = 0;
	BPItem = NULL;

}

// Called when the game starts or when spawned
void ADrop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrop::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
FRotator ActorRotation = this->GetActorRotation();

	ActorRotation.Yaw++;

	this->SetActorRotation(ActorRotation);
	
	

}

void ADrop::OnMyActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor == player) && (OtherComp->GetName() != player->col->GetName()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());

		switch (index)
		{
		case 0:
			//Nihya ibo default
			break;
		case 1:
			//Weapon
			if (BPItem && !player->hasSoul) {
				player->addWeapon(BPItem, namew);
				this->Destroy();
			}
			break;
		case 2:
			//Ammo
				player->addAmmo();
				this->Destroy();
			break;
		case 3:
			//Health
				player->addHealth();
				this->Destroy();
			break;
		case 4:
			//Collectable
			//poka hyu znaet suka
			//mb deattach weapon v rykah (ofc sohranit last weapon ili pohyu)
			//attach eto dermo v socket
			//ezpz nahyu
			//bool peremennaya (isNesuItem) 4tob mojno bilo sdat
			if (BPItem && !player->hasSoul) {
				player->hasSoul = true;
				player->takeSoul(BPItem);
				this->Destroy();
			}
			break;
		default:
			break;
		}


		
	}

}




