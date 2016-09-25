// Cvopyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "HellsBallsGameMode.generated.h"

UCLASS(minimalapi)
class AHellsBallsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AHellsBallsGameMode();

	virtual void Tick(float DeltaSeconds) override;

	FTimerHandle FuzeTimerhandle;

	UPROPERTY(EditAnywhere, Category = "Game")
		bool playerEnteredGround;

	void survivetime();

	uint8 timertime;

	uint8 mostsurvived;

	UFUNCTION(BlueprintCallable, Category = "MyGame")
	uint8 gettimertime();

	UFUNCTION(BlueprintCallable, Category = "MyGame")
	uint8 getmostsurvived();

	UFUNCTION(BlueprintCallable, Category = "MyGame")
		void setPlayerEntered();

	virtual void PostInitializeComponents() override;

};



