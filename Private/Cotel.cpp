// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Cotel.h"
#include "HellsBallsCharacter.h"
#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine.h"
#include "Drop.h"





// Sets default values
ACotel::ACotel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	lava = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Lava"));
	lava->SetupAttachment(RootComponent);

	soulone = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("soulone"));
	soulone->SetupAttachment(lava);
	soulone->SetVisibility(false);
	
	soultwo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("soultwo"));
	soultwo->SetupAttachment(lava);
	soultwo->SetVisibility(false);
	


	soulthree = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("soulthree"));
	soulthree->SetupAttachment(lava);
	soulthree->SetVisibility(false);
	


	soulfour = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("soulfour"));
	soulfour->SetupAttachment(lava);
	soulfour->SetVisibility(false);
	



	col = CreateDefaultSubobject<USphereComponent>(TEXT("col"));
	col->SetupAttachment(lava);
	col->OnComponentBeginOverlap.AddDynamic(this, &ACotel::OnOverlap);
	col->OnComponentEndOverlap.AddDynamic(this, &ACotel::OnOverlapEND);

	souls = 0;
	playerinrage = false;
	
}

// Called when the game starts or when spawned
void ACotel::BeginPlay()
{
	Super::BeginPlay();

	//AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	
}







// Called every frame
void ACotel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	
}

void ACotel::showSouls(int32 number)
{
	switch (number)
	{
	case 0:
		//nichego
		break;
	case 1:
		soulone->SetVisibility(true);
		break;
	case 2:
		soultwo->SetVisibility(true);
		break;
	case 3:
		soulthree->SetVisibility(true);
		break;
	case 4:
		soulfour->SetVisibility(true);
		break;
	default:
		break;
	}
}

void ACotel::clearSouls()
{
		soulone->SetVisibility(false);

		soultwo->SetVisibility(false);

		soulthree->SetVisibility(false);

		soulfour->SetVisibility(false);

		souls = 0;
}

void ACotel::dropSouls(int32 number)
{
	if (playerinrage)
	{
		switch (souls)
		{
		case 0:
			//nichego
			break;
		case 1:
			if (Drops[0])
			{
				int32 randint = FMath::RandRange(-140, -240);
				int32 randint2 = FMath::RandRange(-140, -240);
				ADrop* drophp = GetWorld()->SpawnActor<ADrop>(Drops[0], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
				drophp->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*drophp->CollisionBox->GetMass());
				this->clearSouls();
			}

			if (Drops[1])
			{
				int32 randint = FMath::RandRange(140, 240);
				int32 randint2 = FMath::RandRange(140, 240);
				ADrop* dropammo = GetWorld()->SpawnActor<ADrop>(Drops[1], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
				dropammo->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*dropammo->CollisionBox->GetMass());
				this->clearSouls();
			}
			break;
		case 2:
			if (Drops[2])
			{
				int32 randint = FMath::RandRange(140, 240);
				int32 randint2 = FMath::RandRange(140, 240);
				ADrop* dropshotgun = GetWorld()->SpawnActor<ADrop>(Drops[2], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
				dropshotgun->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*dropshotgun->CollisionBox->GetMass());
				this->clearSouls();
			}
			break;
		case 3:
			if (Drops[3])
			{
				int32 randint = FMath::RandRange(140, 240);
				int32 randint2 = FMath::RandRange(140, 240);
				ADrop* droprifle = GetWorld()->SpawnActor<ADrop>(Drops[3], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
				droprifle->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*droprifle->CollisionBox->GetMass());
				this->clearSouls();
			}
			break;
		case 4:
			if (Drops[4])
			{
				int32 randint = FMath::RandRange(140, 240);
				int32 randint2 = FMath::RandRange(140, 240);
				ADrop* droprpg = GetWorld()->SpawnActor<ADrop>(Drops[4], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
				droprpg->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*droprpg->CollisionBox->GetMass());
				this->clearSouls();
			}
			break;
		default:
			break;
		}
	}
}

void ACotel::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (OtherActor == player)
	{
		playerinrage = true;
		
		//check(InputComponent);

		//this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
	}

	if (OtherActor == player && player->hasSoul)
	{
		//Vipolnaem chenado i delaem hasoul false
		
		if (souls <= 4) {
			souls++;
			showSouls(souls);


			player->Weapon->Destroy();
			player->hasSoul = false;

			if (player->Weapons[player->lastweapon])
			{
				player->Weapon = player->Weapons[player->lastweapon];
				player->Weapons[player->lastweapon]->canshoot = true;
				const USkeletalMeshSocket *socket = player->GetMesh()->GetSocketByName(player->Weapons[player->lastweapon]->namew);
				socket->AttachActor(player->Weapons[player->lastweapon], player->GetMesh());
			}
		}
	}


}

void ACotel::OnOverlapEND(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (OtherActor == player)
	{
		playerinrage = false;

		
		//InputComponent->BindTouch(IE_Pressed, player, &AHellsBallsCharacter::TouchStarted);
		//InputComponent->BindTouch(IE_Released, player, &AHellsBallsCharacter::TouchStopped);
	}
}

float ACotel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	

	

	
	return DamageAmount;
}

void ACotel::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{

		//this->dropSouls(souls);
		if (Drops[0])
		{
			int32 randint = FMath::RandRange(140, 240);
			int32 randint2 = FMath::RandRange(140, 240);
			ADrop* drophp = GetWorld()->SpawnActor<ADrop>(Drops[0], this->GetActorLocation() + FVector(0, 0, 0), this->GetActorRotation());
			drophp->CollisionBox->AddImpulse(FVector(randint, randint2, 500)*drophp->CollisionBox->GetMass());
			this->clearSouls();
		}

	}

}

void ACotel::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		
	}
}