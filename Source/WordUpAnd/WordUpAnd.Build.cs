using System.IO;
using UnrealBuildTool;

public class WordUpAnd : ModuleRules
{

	private string ModulePath
    {
		get { return ModuleDirectory;  }
    }

	private string LibPath
    {
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../lib/")); }
    }


	public WordUpAnd(ReadOnlyTargetRules Target) : base(Target)
	// public WordUpAnd(TargetInfo Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "UMG", "Http"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		LoadCURL(Target);
	}

	public bool LoadCURL(ReadOnlyTargetRules Target)
    {

		bool isLibrarySupported = false;
		if (Target.Platform == UnrealTargetPlatform.Win64)
        {
			isLibrarySupported = true;
			string PlatformString = "_64";
			string libcurl_path = Path.Combine(LibPath, "libcurl_a.lib");
			PublicAdditionalLibraries.Add(libcurl_path);
			System.Console.WriteLine("Libpath = " + LibPath);
			System.Console.WriteLine("libcurl path = " + libcurl_path);

			string includePath = Path.Combine(ModulePath, "..\\..\\include");
			PublicIncludePaths.Add(includePath);
			System.Console.WriteLine("added include path = " + includePath);
        }
		else
        {
			System.Console.WriteLine("Unsupported build system!");
        }
		PublicDefinitions.Add(string.Format("WITH_CURL_LIB_BINDING={0}", isLibrarySupported ? 1 : 0));

		return isLibrarySupported;
    }
}
