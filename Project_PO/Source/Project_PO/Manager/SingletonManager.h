// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PROJECT_PO_API SingletonManager
{
public:
    template<typename T>
    static T* GetInstance()
    {
        static T* Instance = nullptr;
        if (!Instance)
        {
            Instance = NewObject<T>();
            Instance->AddToRoot();
        }
        return Instance;
    }
};
