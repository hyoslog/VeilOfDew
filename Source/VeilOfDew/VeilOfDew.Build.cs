// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VeilOfDew : ModuleRules
{
	public VeilOfDew(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
