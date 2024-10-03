// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_PO : ModuleRules
{
	public Project_PO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Slate", "SlateCore", "GeometryCollectionEngine" });
		bEnableExceptions = true;
	}
}
