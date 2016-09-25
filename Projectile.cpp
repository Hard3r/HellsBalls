// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"
#include "HellsBallsCharacter.h"

// Sets default values
AProjectile::AProjectile()
{

	


	Collisionsphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Collisionsphere->InitSphereRadius(5.0f);
	Collisionsphere->BodyInstance.SetCollisionProfileName("Projectile");
	Collisionsphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	Collisionsphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMyActorHit);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	

	Collisionsphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Collisionsphere->CanCharacterStepUpOn = ECB_No;

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Collisionsphere;

	ProjectMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectMovement->UpdatedComponent = Collisionsphere;
	ProjectMovement->InitialSpeed = 3000.f;
	ProjectMovement->MaxSpeed = 3000.f;
	ProjectMovement->bRotationFollowsVelocity = true;
	ProjectMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;

	name = "default";
	
	basedamage = 10;

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::OnHit(class UPrimitiveComponent* HitComp, class AActor* Actor, class UPrimitiveComponent* Other, FVector Impulse, const FHitResult & HitResult)
{
	//IF NOT SELF
	if (Actor)
	{
		//Actor->TakeDamage(basedamage, FDamageEvent(), NULL, this);
	}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Actor->GetName());
	
}

void AProjectile::OnMyActorHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	AActor* actor = Cast<AActor>(ownerino);

	//AActor* player = Cast<AActor>(owner);
	//if (OtherActor->GetActorClass() == ownerino) { return; }

	if (OtherActor->GetClass() == ownerino) { return; }
	if (OtherComp->GetName() == Collisionsphere->GetName()) { return; }

	//if (OtherActor != player && OtherActor != NULL && OtherActor->GetClass() != this->GetClass() && objects.Num() == 0)
	if (OtherActor != actor && OtherActor != NULL && OtherActor->GetClass() != this->GetClass() && objects.Num() == 0)

	{
		objects.Add(OtherActor);
		OtherActor->TakeDamage(basedamage, FDamageEvent(), NULL, this);
		this->Destroy();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherActor->GetName());
	}

	
}


