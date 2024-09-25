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
    template<typename OwnerType, typename T>
    T* CreateAndAddWidget(OwnerType* OwningObject, FString WidgetKey, TSubclassOf<T> WidgetClass)
    {
        if (!OwningObject)
            return nullptr;

        if (Widgets.Contains(WidgetKey))
        {
            UUserWidget* ExistingWidget = Widgets[WidgetKey];

            if (ExistingWidget)
            {
                ExistingWidget->RemoveFromParent();

                ExistingWidget->MarkAsGarbage();
            }
            Widgets.Remove(WidgetKey);
        }

        OwnerType* Owner = Cast<OwnerType>(OwningObject);
        if (Owner)
        {
            T* NewWidget = CreateWidget<T>(Owner, WidgetClass);
            if (NewWidget)
            {
                Widgets.Emplace(WidgetKey, NewWidget);
            }
            return NewWidget;
        }
        return nullptr;
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
