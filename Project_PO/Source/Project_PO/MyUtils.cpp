// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtils.h"

namespace MyUtils
{
    FVector2D RandomVector2D(FVector2D const& OriginalVector, float const& RandomRange)
    {
        float RandomX = FMath::RandRange(-RandomRange, RandomRange);
        float RandomY = FMath::RandRange(-RandomRange, RandomRange);

        return FVector2D(OriginalVector.X + RandomX, OriginalVector.Y + RandomY);
    }

    FVector RandomVector(FVector const& OriginalVector, float const& RandomRange)
    {
        float RandomX = FMath::RandRange(-RandomRange, RandomRange);
        float RandomY = FMath::RandRange(-RandomRange, RandomRange);

        return FVector(OriginalVector.X + RandomX, OriginalVector.Y + RandomY, OriginalVector.Z);
    }
}