// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LoadAssets_Pak : ModuleRules
{
	public LoadAssets_Pak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] { "PakFile", "StreamingFile" });
	}
}
