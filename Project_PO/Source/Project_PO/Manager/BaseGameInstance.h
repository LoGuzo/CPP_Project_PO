// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../MyStructureAll.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBaseGameInstance();

	virtual void Init() override;
    virtual void Shutdown() override;
private:
    UPROPERTY()
	TMap<E_ManagerType, UObject*> ManagerMap;

    TMap<E_ManagerType, TMap<int32, TSharedPtr<FTableRowBase>>> DatabaseMap;

public:
    template<typename T>
    T* GetManager(E_ManagerType ManagerKey)
    {
        if (ManagerMap.Contains(ManagerKey))
        {
            return Cast<T>(ManagerMap[ManagerKey]);
        }
        return nullptr;
    }

    template<typename T>
    TSharedPtr<T> GetDatabaseMap(E_ManagerType Type, int32 ID)
    {
        return StaticCastSharedPtr<T>(*DatabaseMap.Find(Type)->Find(ID));
    }

    void AddDataToDatabase(E_ManagerType ManagerType, TMap<int32, TSharedPtr<FTableRowBase>> NewData);
};