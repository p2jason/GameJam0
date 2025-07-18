// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameJam0 : ModuleRules
{
	public GameJam0(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"GameplayTags",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"CommonUI",
			"CommonInput",
			"CommonGame",
			"CommonUser",
			"ModularGameplayActors",
		});

		PublicIncludePaths.AddRange(new string[] {
			"GameJam0",
			"GameJam0/Variant_Horror",
			"GameJam0/Variant_Shooter",
			"GameJam0/Variant_Shooter/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
