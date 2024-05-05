// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Campus : ModuleRules
{
	public Campus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem","Networking","WebSockets","Sockets", "EnhancedInput" });

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
			"Niagara"
		});

        PublicIncludePaths.AddRange(new string[]
        {
            "Campus/AI/AIDrone/CoreDrone"
        });

        bUseRTTI = true;
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}