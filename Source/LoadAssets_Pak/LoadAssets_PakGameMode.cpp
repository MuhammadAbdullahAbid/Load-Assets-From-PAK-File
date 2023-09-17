// Copyright Epic Games, Inc. All Rights Reserved.

#include "LoadAssets_PakGameMode.h"
#include "LoadAssets_PakCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALoadAssets_PakGameMode::ALoadAssets_PakGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
