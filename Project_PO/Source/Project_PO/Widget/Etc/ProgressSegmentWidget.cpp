// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressSegmentWidget.h"
#include "Components/ProgressBar.h"

void UProgressSegmentWidget::SetSegment(float const& Value)
{
	if (Value > 0.f)
	{
		if (PB_1)
			PB_1->SetPercent(1.f);
	}

	if (Value > 0.2f)
	{
		if (PB_2)
			PB_2->SetPercent(1.f);
	}

	if (Value > 0.4f)
	{
		if (PB_3)
			PB_3->SetPercent(1.f);
	}

	if (Value > 0.6f)
	{
		if (PB_4)
			PB_4->SetPercent(1.f);
	}

	if (Value > 0.8f)
	{
		if (PB_5)
			PB_5->SetPercent(1.f);
	}
}