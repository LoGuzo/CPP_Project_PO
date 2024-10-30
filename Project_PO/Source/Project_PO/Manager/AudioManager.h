// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PO_API UAudioManager : public UObject
{
	GENERATED_BODY()
	
public:
	UAudioManager();

private:
    TMap<FString, int32> NameMap;

    UPROPERTY()
    UAudioComponent* BackgroundMusicComponent;

private:
    float VolumeSize;

public:
    void PlayBackgroundMusic(UWorld const* World, FString const& MusicCueName, float const& FadeInDuration = 1.0f);
    void StopBackgroundMusic(float const& FadeOutDuration = 1.0f);
    void SetBackgroundMusicVolume(float const& Volume);
    void PauseBackgroundMusic();
    void ResumeBackgroundMusic();

    void PlayEffectSound(UWorld const* World, FString const& EffectCueName, FVector const& Location);


    void SetVolume(float const& _VolumeSize);
    float GetVolume() { return VolumeSize; }

private:
    class USoundCue* FindSoundCue(UWorld const* World, FString const& SoundName);

};
