// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DicomTest422 : ModuleRules {
  public DicomTest422(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    bEnableExceptions = true;
    bEnableUndefinedIdentifierWarnings = false; // Necessary for ignoring C4668 in Unreal Engine 4.21

    PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RenderCore", "RHI" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

    // Uncomment if you are using Slate UI
    // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

    // Uncomment if you are using online features
    // PrivateDependencyModuleNames.Add("OnlineSubsystem");

    // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
  }
}
