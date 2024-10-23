// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawnerActor.h"
#include "NavigationSystem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../Character/Enemy/EnemyCharacter.h"
#include "../../Character/Enemy/BossEnemyCharacter.h"
#include "../../Trigger/BaseTriggerBox.h"
#include "../../Manager/BaseGameInstance.h"
#include "../../Manager/ObjectPoolManager.h"

// Sets default values
ABaseSpawnerActor::ABaseSpawnerActor()
	: SpawnMonsterID(-1)
{
    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = SceneRoot;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    MeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    MeshComponent->SetupAttachment(RootComponent);

    SpawnArea = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    SpawnArea->SetupAttachment(RootComponent);
}

void ABaseSpawnerActor::SpawnMonster()
{
    if (SpawnMonsterID == -1)
        return;

    FTransform Transform;
    Transform.SetLocation(SpawnArea->GetComponentLocation());
    Transform.SetRotation(GetActorRotation().Quaternion());

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance)
    {
        TWeakPtr<FMonsterStatData> MonsterData = GameInstance->GetDatabaseMap<FMonsterStatData>(E_ManagerType::E_MonsterDatabaseManager, SpawnMonsterID);
        if (MonsterData.IsValid())
        {
            UObjectPoolManager* ObjectPoolManager = GameInstance->GetManager<UObjectPoolManager>(E_ManagerType::E_ObjectPoolManager);
            if (ObjectPoolManager)
            {
                AEnemyCharacter* Enemy = ObjectPoolManager->GetMonster(GetWorld(), MonsterData.Pin()->MonsterType, Transform, SpawnParams);
                if (Enemy)
                {
                    if (Target)
                        Enemy->SetTarget(Target);

                    ABossEnemyCharacter* Boss = Cast<ABossEnemyCharacter>(Enemy);
                    if (Boss)
                        Boss->OnBossDied.AddUObject(OwnerTrigger, &ABaseTriggerBox::QuestClear);

                    SpawnEnemies.Emplace(Enemy);
                }
            }
        }
    }
}

void ABaseSpawnerActor::DeSpawnMonster()
{
    for (int32 i = SpawnEnemies.Num() - 1; i >= 0; i--)
    {
        if (!SpawnEnemies[i]->GetIsDied())
            SpawnEnemies[i]->DiedNotify();

        SpawnEnemies.RemoveAt(i);
    }
}
