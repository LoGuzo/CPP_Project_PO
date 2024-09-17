// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../MyEnumClass.h"
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
};
