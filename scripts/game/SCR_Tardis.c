//------------------------------------------------------------------------------------------------
class SCR_Tardis : ScriptedUserAction
{   
    //References
    protected PlayerManager m_PlayerManager;
    //------------------------------------------------------------------------------------------------
    override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
    {
        IEntity playerEntity = pUserEntity;
        DamageManagerComponent damageManager = DamageManagerComponent.Cast(playerEntity.FindComponent(DamageManagerComponent));

        if (!damageManager || damageManager.GetState() == EDamageState.DESTROYED)
            return;
        
        damageManager.SetHealthScaled(0);                          
    }
    
    //------------------------------------------------------------------------------------------------
    override bool GetActionNameScript(out string outName)
    {
        outName = "Regenerate";
        return true;
    }    
};

