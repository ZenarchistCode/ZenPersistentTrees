class ZenTreesConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "1";

	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenTreesConfig.json";

	// Config data
	string ConfigVersion = "";
	int TimeToRespawn = 0;
	bool TreeHard = true;
	bool TreeSoft = true;
	bool BushHard = true;
	bool BushSoft = true;
	ref array<ref ZenTreeState> CutTrees = new ref array<ref ZenTreeState>;

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (FileExist(zenModFolder + zenConfigName))
		{
			// If config exists, load file
			JsonFileLoader<ZenTreesConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			// If version mismatch, backup old version of json before replacing it
			if (ConfigVersion != CONFIG_VERSION)
			{
				JsonFileLoader<ZenTreesConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, stop here.
				return;
			}
		}

		// Set new config version
		ConfigVersion = CONFIG_VERSION;
		CutTrees.Clear();
		TimeToRespawn = 86400 * 3; // 3 days

		// Save config
		Save();
	};

	// Save config
	void Save()
	{
		if (!FileExist(zenModFolder))
		{	// If config folder doesn't exist, create it.
			MakeDirectory(zenModFolder);
		}

		// Save JSON config
		JsonFileLoader<ZenTreesConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	// Save tree state
	void SaveTreeState(vector location, float hp)
	{
		// Update existing tree
		int ts = JMDate.Now(false).GetTimestamp() + TimeToRespawn;
		foreach (ZenTreeState treeState : CutTrees)
		{
			if (treeState.Location == location)
			{
				treeState.Health = hp;
				treeState.RenewTime = ts;
				return; // Stop function here
			}
		}

		// Save new tree if not found
		ZenTreeState newTreeState = new ZenTreeState(location, ts, hp);
		CutTrees.Insert(newTreeState);
	}

	// Clears any "respawned" trees (ie. trees that have exceeded their timestamp)
	void ClearRespawnedTrees()
	{
		autoptr array<ZenTreeState> tempTreeArray = new array<ZenTreeState>;
		int timestamp = JMDate.Now(false).GetTimestamp();
		int i;
		ZenTreeState treeState;

		// Loop through saved tree list
		for (i = 0; i < CutTrees.Count(); i++)
		{
			treeState = CutTrees.Get(i);

			// Check if today's timestamp is less than future renew timestamp
			if (timestamp < treeState.RenewTime)
				tempTreeArray.Insert(treeState);
		}

		// Clear old array and re-populate with any non-removed items
		CutTrees.Clear();
		for (i = 0; i < tempTreeArray.Count(); i++)
		{
			CutTrees.Insert(tempTreeArray.Get(i));
		}

		// Save any changes to config file
		Save();

		// Clear temp array
		tempTreeArray.Clear();
	}
}

// Define tree state
class ZenTreeState
{
	vector Location;
	float Health = 0;
	int RenewTime = 0;

	void ZenTreeState(vector loc, int time, float hp)
	{
		Health = hp;
		Location = loc;
		RenewTime = time;
	}
};

// Save config data
ref ZenTreesConfig m_ZenTreesConfig;

// Helper function to return Config data storage object
static ZenTreesConfig GetZenTreesConfig()
{
	if (!m_ZenTreesConfig)
	{
		Print("[ZenTreesConfig] Init");
		m_ZenTreesConfig = new ZenTreesConfig;

		// Only load JSON config on the server
		if (GetGame().IsDedicatedServer())
		{
			m_ZenTreesConfig.Load();
		}
	}

	return m_ZenTreesConfig;
};