// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Campus : ModuleRules
{
	public Campus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"HTTP",
			"Json",
			"JsonUtilities",
			"UMG",
			"SlateCore",
			"Slate", 
			"Niagara",
		});

		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		PrivateDependencyModuleNames.AddRange(new string[]{"HeadMountedDisplay", "OpenXR"});

        PublicIncludePaths.AddRange(new string[]
        {
            "Campus/AI/AIDrone/CoreDrone"
        });

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
	        PrivateDependencyModuleNames.AddRange(new string[]{"Launch"});
        }

		bUseRTTI = true;
		bEnableExceptions = true;

        PublicDefinitions.Add("ALPINIST_GAME");
        
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}