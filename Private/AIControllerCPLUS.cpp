// Fill out your copyright notice in the Description page of Project Settings.

#include "HellsBalls.h"
#include "AIControllerCPLUS.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "HellsBallsCharacter.h"
#include "Bot.h"






AAIControllerCPLUS::AAIControllerCPLUS()
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));

	btreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));

}

void AAIControllerCPLUS::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	ABot* player = Cast<ABot>(InPawn);

	if (player && player->botBehavior)
	{
		blackboardComp->InitializeBlackboard(*player->botBehavior->BlackboardAsset);

		EnemykeyID = blackboardComp->GetKeyID("Target");

		btreeComp->StartTree(*player->botBehavior);
	}
}

void AAIControllerCPLUS::SetEnemy(APawn * InPawn)
{


}
