class CfgPatches
{
	class ZenPersistentTrees
	{
		units[]={};
		weapons[]={};
		requiredVersion=1;
		requiredAddons[] = 
		{ 
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenPersistentTrees
	{
		dir="ZenPersistentTrees";
		picture=""; 
		action="";
		hideName=1;
		hidePicture=1;
		name="ZenPersistentTrees";
		credits=""; 
		author="Zenarchist";
		authorID="0";  
		version="1.0";
		extra=0;
		type="mod";
		dependencies[] =
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenPersistentTrees/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenPersistentTrees/scripts/4_world" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenPersistentTrees/scripts/5_mission" };
			};
		}
	};
};