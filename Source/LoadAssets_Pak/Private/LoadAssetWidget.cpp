// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadAssetWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HAL/PlatformFilemanager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "IPlatformFilePak.h"

bool ULoadAssetWidget::SetPathAndMountPak(FString PakName)
{
	bool Return = false;
	FString FullPAKPath = UKismetSystemLibrary::GetProjectContentDirectory() + "Paks/" + PakName + ".pak";
	UE_LOG(LogTemp, Warning, TEXT("Full PAK Path : %s"), *FullPAKPath);

	if (DoesFileExist(FullPAKPath))
	{
		Return = MountPak(FullPAKPath);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("File Doesn't Exist"));

	}
	return Return;
}

bool ULoadAssetWidget::MountPak(FString PakFileFullPath)
{
	IPlatformFile& InnerPlatform = FPlatformFileManager::Get().GetPlatformFile();
	FPakPlatformFile* PakPlatform = new FPakPlatformFile();

	PakPlatform->Initialize(&InnerPlatform, TEXT(""));

	FPlatformFileManager::Get().SetPlatformFile(*PakPlatform);


	FString path = FPaths::ConvertRelativePathToFull(PakFileFullPath);
	bool check = false;
	TArray<FAssetData> OutAssetsData;
	IPakFile* MountedPak;
	FString MountPoint;
	FString PakContentPath;
	

	if (FCoreDelegates::MountPak.IsBound())
	{
		//check = FCoreDelegates::MountPak.Execute(SaveDirectory, 0);
		MountedPak = FCoreDelegates::MountPak.Execute(PakFileFullPath, 0);
		//FCoreDelegates::OnPakFileMounted2.Broadcast(*MountedPak);
		if (MountedPak)
		{
			MountPoint = MountedPak->PakGetMountPoint();
			PakContentPath = MountPoint + FPaths::ProjectContentDir();
			FPackageName::RegisterMountPoint("/Game/", *PakContentPath);
			check = PakPlatform->Mount(*PakFileFullPath, 0, *FPaths::ProjectContentDir());
			FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
			IAssetRegistry& assetRegistry = assetRegistryModule.Get();
			//UE_LOG(LogTemp, Warning, TEXT("Mount Point: %s"), *MountedPak->PakGetMountPoint());
			assetRegistry.ScanPathsSynchronous({ TEXT("/Game/") }, true);
			assetRegistry.GetAllAssets(OutAssetsData, true);
			UE_LOG(LogTemp, Warning, TEXT("Assets Data Count: %d"), OutAssetsData.Num());
			check = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: MountPak is NOT Bound"));
	}
	UE_LOG(LogTemp, Log, TEXT("Bool value is: %s"), (check ? TEXT("true") : TEXT("false")));
	return check;
}

bool ULoadAssetWidget::DoesFileExist(FString FullPAKPath)
{
	return FPaths::FileExists(FullPAKPath);
}
