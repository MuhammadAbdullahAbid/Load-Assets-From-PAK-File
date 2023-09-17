// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IPlatformFilePak.h"
#include "LoadAssetWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOADASSETS_PAK_API ULoadAssetWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	

	UFUNCTION(BlueprintCallable, Category = "Load Assets")
	bool SetPathAndMountPak(FString PakName);

	UFUNCTION()
	bool MountPak(FString PakFileFullPath);
	
	UFUNCTION(BlueprintCallable, Category = "Load Assets")
	bool DoesFileExist(FString FullPAKPath);
	

};
