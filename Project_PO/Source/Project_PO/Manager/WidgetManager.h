// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UWidgetManager : public UObject
{
	GENERATED_BODY()

private:
    UPROPERTY()
	TMap<FString, class UBaseUserWidget*> Widgets;

public:
    template<typename T>
    T* CreateAndAddWidget(UWorld* World, FString WidgetKey, TSubclassOf<T> WidgetClass)
    {
        if (!World)
            return nullptr;

        if (Widgets.Contains(WidgetKey))
        {
            return Cast<T>(Widgets[WidgetKey]);
        }

        T* NewWidget = CreateWidget<T>(World, WidgetClass);
        if (NewWidget)
        {
            Widgets.Add(WidgetKey, NewWidget);
        }
        return NewWidget;
    }

    template<typename T>
    T* GetWidget(FString WidgetKey)
    {
        if (Widgets.Contains(WidgetKey))
        {
            return Cast<T>(Widgets[WidgetKey]);
        }
        return nullptr;
    }

    void RemoveWidget(FString WidgetKey)
    {
        if (Widgets.Contains(WidgetKey))
        {
            Widgets.Remove(WidgetKey);
        }
    }
};
