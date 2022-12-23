What Is This?

This small and simple mod adds persistent trees to DayZ.

Whenever a player cuts down a tree or bush, the server will save that info to a JSON config file when the server shuts down.

Upon the next restart, the script will cut down any trees that were cut down on the previous session.

You can specify how long a tree or bush takes to respawn (in seconds) in the JSON config. By default it's set to 3 real-life days.

You can also specify whether or not to save hard trees, soft trees, hard bushes and/or soft bushes.

The mod saves the "health" of each tree/bush, so for example, if a tree gives out 2 logs and a player cuts 1 log, the tree will be saved as 50% health. Then if a player cuts the tree before the respawn time is reached (3 days by default), they will only get 1 log before the tree falls down.

If a tree or bush is cut down completely, then on the next restart it will be cut down again.

This is intended for hardcore servers, it makes basebuilding and survival a little more challenging by not being able to farm all the trees around your base after each restart.

Installation Instructions:

Install this mod like any other mod - copy it into your server's root directory, add it to your launch parameters, and make sure to copy the .bikey into your server keys.

This mod should be able to run as a server-side mod, but this hasn't been tested. If it doesn't work as a server mod, just repack it into your server pack.

When you run your server for the first time a JSON config file will be created in your server profile folder under "Zenarchist/ZenTreesConfig.json". You can adjust the following parameters:

"ConfigVersion": "1" // Don't touch this.
"TimeToRespawn": 259200 // How many seconds until the tree "respawns".
"TreeHard": 1 // Set to 0 to disable saving hard/large tree health. 
"TreeSoft": 1 // Set to 0 to disable saving soft/small tree health.
"BushHard": 1 // Set to 0 to disable saving hard/large bush health.
"BushSoft": 1 // Set to 0 to disable saving soft/small bush health.
"CutTrees":[] // This will be a list of saved trees when cut. 

Repack & Source Code:

You can repack this mod if you like, and do anything else you want with it for that matter. The source code is on my GitHub at www.zenarchist.io

Enjoy!