// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtils.h"

namespace MyUtils
{
    FVector2D RandomVector2D(FVector2D OriginalVector, float RandomRange)
    {
        float RandomX = FMath::RandRange(-RandomRange, RandomRange);
        float RandomY = FMath::RandRange(-RandomRange, RandomRange);

        // 원래 데미지에 랜덤 오프셋을 추가하여 새로운 데미지를 반환
        return FVector2D(OriginalVector.X + RandomX, OriginalVector.Y + RandomY);
        return FVector2D();
    }
}