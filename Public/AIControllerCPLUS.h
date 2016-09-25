// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIControllerCPLUS.generated.h"

/**
 * 
 */
UCLASS()
class HELLSBALLS_API AAIControllerCPLUS : public AAIController
{
	GENERATED_BODY()


public:

		AAIControllerCPLUS();

		UPROPERTY(transient)
		UBlackboardComponent* blackboardComp;
	
	UPROPERTY(transient)
		UBehaviorTreeComponent* btreeComp;

	virtual void Possess(APawn* InPawn) override;

	void SetEnemy(APawn* InPawn);

	uint8 EnemykeyID;

};
