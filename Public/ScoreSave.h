// Жулик не воруй. Rly want te steal smthing?

#pragma once

#include "GameFramework/SaveGame.h"
#include "ScoreSave.generated.h"

/**
 * 
 */
UCLASS()
class HELLSBALLS_API UScoreSave : public USaveGame
{
	GENERATED_BODY()

public:

		UScoreSave();

		UPROPERTY(VisibleAnywhere, Category = Basic)
		uint8 playerScore;
	
	
};
