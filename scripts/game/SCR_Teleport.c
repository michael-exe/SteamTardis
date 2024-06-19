class SCR_Teleport : ScriptedUserAction
{
	 // Indices to keep track of the current position
    private int m_CurrentIndex = 0;

    // Positions array for the player and the TARDIS	
ref	array<vector> m_PlayerPositions = {"5158.263 13.831 3959.744", "4834.332 170.396 7005.776", "4815.983 51.697 6194.626"};
ref	array<vector> m_TardisPositions = { "5178.675 14.571 3976.484", "4833.263 170.319 7015.651", "4820.329 51.507 6162.347" };

//ref array<float> m_PlayerYaws = {0, 90, 180};
//ref array<float> m_TardisYaws = {0, 270, 0}; 	
	
//------------------------------------------------------------------------------------------------
override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
    {
        if (m_CurrentIndex < m_PlayerPositions.Count() && m_CurrentIndex < m_TardisPositions.Count())
        {
            Teleport(pUserEntity, m_PlayerPositions[m_CurrentIndex]);
            Teleport(pOwnerEntity, m_TardisPositions[m_CurrentIndex]);
			
			//Teleport(pUserEntity, m_PlayerPositions[m_CurrentIndex], m_PlayerYaws[m_CurrentIndex]);
			//Teleport(pOwnerEntity, m_TardisPositions[m_CurrentIndex], m_TardisYaws[m_CurrentIndex]);

            Print("Player coordinates: " + pUserEntity.GetOrigin());
            Print("TARDIS coordinates: " + pOwnerEntity.GetOrigin());

            m_CurrentIndex++; // Move to the next set of coordinates
        }
        else
        {
            Print("No more coordinates to teleport to!");
        }
    }

//------------------------------------------------------------------------------------------------
override bool GetActionNameScript(out string outName)
	{
	    outName = "Teleport";
	    return true;
	}

static void Teleport(notnull IEntity entity, vector position, float yaw = "-1337.42042".ToFloat())
	{
	    vector transform[4];
	
	    if (!EPF_Const.IsUnset(yaw))
	    {
	        Math3D.AnglesToMatrix(Vector(yaw, 0, 0), transform);
	    }
	    else
	    {
	        entity.GetWorldTransform(transform);
	    }
	
	    transform[3] = position;
	    SCR_TerrainHelper.OrientToTerrain(transform);
	
	    ForceTransformEx(entity, transform);
	}

static void ForceTransformEx(notnull IEntity entity, vector transform[4])
	{
	    vector previousOrigin = entity.GetOrigin();
	
	    BaseGameEntity baseGameEntity = BaseGameEntity.Cast(entity);
	    if (baseGameEntity && !BaseVehicle.Cast(baseGameEntity))
	    {
	        baseGameEntity.Teleport(transform);
	    }
	    else
	    {
	        entity.SetWorldTransform(transform);
	    }
	
	    Physics physics = entity.GetPhysics();
	    if (physics)
	    {
	        physics.SetVelocity(vector.Zero);
	        physics.SetAngularVelocity(vector.Zero);
	    }
	
	    RplComponent replication = EPF_Component<RplComponent>.Find(entity);
	    if (replication)
	        replication.ForceNodeMovement(previousOrigin);
	
	    if (!ChimeraCharacter.Cast(entity))
	        entity.Update();
	}
};
