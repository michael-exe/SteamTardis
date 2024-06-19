class SCR_TimeTravel : ScriptedUserAction
{
    // References
    protected TimeAndWeatherManagerEntity m_TimeManager;

    //------------------------------------------------------------------------------------------------
    override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
    {
        // Obtain the ChimeraWorld instance
        ChimeraWorld world = ChimeraWorld.CastFrom(GetGame().GetWorld());
        
        // Ensure world casting was successful
        if (!world)
        {
            Print("Failed to cast world to ChimeraWorld");
            return;
        }

        // Get the TimeAndWeatherManagerEntity
        m_TimeManager = world.GetTimeAndWeatherManager();
        
        // Check if m_TimeManager was successfully obtained
        if (!m_TimeManager)
        {
            Print("Failed to get TimeAndWeatherManagerEntity");
            return;
        }

        // Retrieve and manipulate the time of day
        float currentTime = m_TimeManager.GetTimeOfTheDay();
        
        // Validate currentTime before use
        if (EPF_Const.IsUnset(currentTime))
        {
            Print("Invalid current time of day");
            return;
        }
        
        float timeToAdd = 6.0;
        float newTime = currentTime + timeToAdd;

        // Ensure newTime is within valid bounds (0.0 to 24.0 for time of day)
        newTime = Clamp(newTime, 0.0, 24.0);

        // Validate newTime before setting it
        if (!EPF_Const.IsUnset(newTime))
        {
            m_TimeManager.SetTimeOfTheDay(newTime);
        }
        else
        {
            Print("New time of day is invalid");
        }
    }

    //------------------------------------------------------------------------------------------------
    override bool GetActionNameScript(out string outName)
    {
        outName = "Time Travel";
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    // Utility function to clamp values within a range
    float Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }
};
