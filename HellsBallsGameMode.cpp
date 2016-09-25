// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "HellsBalls.h"
#include "HellsBallsGameMode.h"
#include "HellsBallsCharacter.h"
#include "HellsBallsCharacter.h"
#include "ScoreSave.h"

AHellsBallsGameMode::AHellsBallsGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	timertime = 0;
	mostsurvived = 0;
}



void AHellsBallsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (playerEnteredGround)
	{
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerhandle, this, &AHellsBallsGameMode::survivetime, 1.0f, true);
		playerEnteredGround = false;
	}

	AHellsBallsCharacter* player = Cast<AHellsBallsCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (player->HP <= 1)
	{

		if (timertime > mostsurvived)
		{
			mostsurvived = timertime;

			UScoreSave* SaveGameInstance = Cast<UScoreSave>(UGameplayStatics::CreateSaveGameObject(UScoreSave::StaticClass()));
			SaveGameInstance->playerScore = mostsurvived;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveScore"), 1);

		}

		GetWorld()->GetTimerManager().ClearTimer(FuzeTimerhandle);
		timertime = 0;
	}

}

void AHellsBallsGameMode::survivetime()
{
	timertime++;
}

uint8 AHellsBallsGameMode::gettimertime()
{
	return timertime;
}

uint8 AHellsBallsGameMode::getmostsurvived()
{
	return mostsurvived;
}

void AHellsBallsGameMode::setPlayerEntered()
{
	playerEnteredGround = true;
}

void AHellsBallsGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UScoreSave* LoadGameInstance = Cast<UScoreSave>(UGameplayStatics::CreateSaveGameObject(UScoreSave::StaticClass()));
	LoadGameInstance = Cast <UScoreSave>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveScore"), 1));


	if (LoadGameInstance)
	{
	
	if (mostsurvived < LoadGameInstance->playerScore)
	{
		mostsurvived = LoadGameInstance->playerScore;
	}
}
}
