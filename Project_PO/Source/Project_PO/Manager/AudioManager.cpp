// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "BaseGameInstance.h"
#include "Components/AudioComponent.h"
#include "DatabaseManager/SoundDatabaseManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UAudioManager::UAudioManager()
	: BackgroundMusicComponent(nullptr)
{
    NameMap.Emplace(TEXT("First Stage"), 9001);
    NameMap.Emplace(TEXT("Protect Statue"), 9002);
    NameMap.Emplace(TEXT("First Boss"), 9003);
}

void UAudioManager::PlayBackgroundMusic(UWorld const* World, FString const& MusicCueName, float const& FadeInDuration)
{
    if (!World) 
        return;

    StopBackgroundMusic(FadeInDuration);

    if (MusicCueName.IsEmpty())
        return;

    USoundCue* SoundCue = FindSoundCue(World, MusicCueName);
    if (SoundCue)
    {
        BackgroundMusicComponent = UGameplayStatics::SpawnSound2D(World, SoundCue, 1.0f, 1.0f, 0.0f);
        if (BackgroundMusicComponent)
            BackgroundMusicComponent->FadeIn(FadeInDuration);
    }
}

void UAudioManager::StopBackgroundMusic(float const& FadeOutDuration)
{
    if (BackgroundMusicComponent && BackgroundMusicComponent->IsPlaying())
        BackgroundMusicComponent->FadeOut(FadeOutDuration, 0.0f);
}

void UAudioManager::SetBackgroundMusicVolume(float const& Volume)
{
    if (BackgroundMusicComponent)
        BackgroundMusicComponent->SetVolumeMultiplier(Volume);
}

void UAudioManager::PauseBackgroundMusic()
{
    if (BackgroundMusicComponent && BackgroundMusicComponent->IsPlaying())
        BackgroundMusicComponent->SetPaused(true);
}

void UAudioManager::ResumeBackgroundMusic()
{
    if (BackgroundMusicComponent && !BackgroundMusicComponent->IsPlaying())
        BackgroundMusicComponent->SetPaused(false);
}

void UAudioManager::PlayEffectSound(UWorld const* World, FString const& EffectCueName, FVector const& Location)
{
    if (!World || EffectCueName.IsEmpty())
        return;

    USoundCue* SoundCue = FindSoundCue(World, EffectCueName);
    if (SoundCue)
        UGameplayStatics::PlaySoundAtLocation(World, SoundCue, Location);
}

USoundCue* UAudioManager::FindSoundCue(UWorld const* World, FString const& SoundName)
{
    int32 SoundID = *NameMap.Find(SoundName);

    if (SoundID != -1)
    {
        UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(World));
        if (GameInstance)
        {
            TWeakPtr<FSoundData> SoundData = GameInstance->GetDatabaseMap<FSoundData>(E_ManagerType::E_SoundDatabaseManager, SoundID);
            if (SoundData.IsValid())
            {
                USoundCue* SoundCue = SoundData.Pin()->SoundClass.LoadSynchronous();
                if (SoundCue)
                    return SoundCue;
            }
        }
    }
    return nullptr;
}
