// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Actor�� ���ϴ� �Լ��� ��Ʈ�ѷ��� ����
	// Ÿ�� ����
}
