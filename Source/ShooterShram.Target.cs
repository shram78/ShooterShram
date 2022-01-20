// ShooterShram Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterShramTarget : TargetRules
{
	public ShooterShramTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterShram" } );
	}
}
