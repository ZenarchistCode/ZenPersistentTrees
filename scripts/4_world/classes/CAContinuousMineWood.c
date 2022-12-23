modded class CAContinuousMineWood : CAContinuousBase
{
	override void CreatePrimaryItems(ActionData action_data)
	{
		super.CreatePrimaryItems(action_data);

		// Probably not a necessary check, but hey, no server crashes is always nice
		if (!action_data || !action_data.m_Target)
			return;

		Object targetObject;
		Class.CastTo(targetObject, action_data.m_Target.GetObject());

		if (!targetObject)
			return;

		// Detect hard tree being cut down
		if (GetZenTreesConfig().TreeHard && targetObject.IsInherited(TreeHard) && targetObject.IsCuttable())
			GetZenTreesConfig().SaveTreeState(targetObject.GetPosition(), targetObject.GetHealth());

		// Detect soft tree being cut down
		if (GetZenTreesConfig().TreeSoft && targetObject.IsInherited(TreeSoft) && targetObject.IsCuttable())
			GetZenTreesConfig().SaveTreeState(targetObject.GetPosition(), targetObject.GetHealth());

		// Detect hard bush being cut down
		if (GetZenTreesConfig().BushHard && targetObject.IsInherited(BushHard))
			GetZenTreesConfig().SaveTreeState(targetObject.GetPosition(), targetObject.GetHealth());

		// Detect soft bush being cut down
		if (GetZenTreesConfig().BushSoft && targetObject.IsInherited(BushSoft))
			GetZenTreesConfig().SaveTreeState(targetObject.GetPosition(), targetObject.GetHealth());
	};
}