modded class MissionServer
{
	// Called when the server shuts down - seems to work fine for our purposes.
	void ~MissionServer()
	{
		// Only save tree config on server shutdown to avoid potential lag if the file gets large
		GetZenTreesConfig().Save();
	}

	// Called when server initializes
	override void OnInit()
	{
		super.OnInit();
		Print("[ZenPersistentTrees] OnInit");

		// Load config
		GetZenTreesConfig();

		// Clear any respawned trees
		GetZenTreesConfig().ClearRespawnedTrees();

		// Deforest the lands 10 seconds after server init to give the game time to load all objects etc
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Deforestation, 10000, false);
	}

	// Restore saved "health" of trees and cut down any that have 0 health
	private void Deforestation()
	{
		for (int i = 0; i < GetZenTreesConfig().CutTrees.Count(); i++)
		{
			CutDownTree(GetZenTreesConfig().CutTrees.Get(i));
		}
	}

	// Cut down the given tree based on config info
	private void CutDownTree(ZenTreeState treeConfig)
	{
		// Get all objects within 10cm of the vector location
		array<Object> objectsNearTree = new array<Object>;
		GetGame().GetObjectsAtPosition(treeConfig.Location, 0.01, objectsNearTree, null);
		Object obj;

		// Cut down any trees/bushes within 0.01m of location
		for (int x = 0; x < objectsNearTree.Count(); x++)
		{
			obj = objectsNearTree.Get(x);

			if (!obj)
				continue;

			// Check if object is a "hard" tree and hard trees config is enabled
			if (GetZenTreesConfig().TreeHard && obj.IsInherited(TreeHard) && obj.IsCuttable())
			{
				obj.SetHealth(treeConfig.Health);

				if (treeConfig.Health <= 0)
					dBodyDestroy(obj);

				return;
			}

			// Check if object is a "soft" tree and soft trees config is enabled
			if (GetZenTreesConfig().TreeSoft && obj.IsInherited(TreeSoft) && obj.IsCuttable())
			{
				obj.SetHealth(treeConfig.Health);

				if (treeConfig.Health <= 0)
					dBodyDestroy(obj);

				return;
			}

			// Check if object is a "hard" bush and hard bush config is enabled
			if (GetZenTreesConfig().BushHard && obj.IsInherited(BushHard))
			{
				obj.SetHealth(treeConfig.Health);

				if (treeConfig.Health <= 0)
					dBodyDestroy(obj);

				return;
			}

			// Check if object is a "soft" bush and soft bush config is enabled
			if (GetZenTreesConfig().BushSoft && obj.IsInherited(BushSoft))
			{
				obj.SetHealth(treeConfig.Health);

				if (treeConfig.Health <= 0)
					dBodyDestroy(obj);

				return;
			}
		}
	}
};