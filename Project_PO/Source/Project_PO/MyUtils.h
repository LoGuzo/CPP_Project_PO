// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
namespace MyUtils
{
	FVector2D RandomVector2D(FVector2D const& OriginalVector, float const& RandomRange);

	FVector RandomVector(FVector const& OriginalVector, float const& RandomRange);
}
