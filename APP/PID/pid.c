#include "pid.h"


void PIDCalculate(PIDTypedef *pidset)
{
	static float Real_Kp = 0;
	//计算偏差
	pidset->Err = pidset->ExpValu - pidset->NowValu;
	//计算微分
	pidset->Diff = pidset->Err - pidset->ErrLast;
	
	//积分分离 
	//如果偏差过大，则减小积分，P进行调整 
	if((pidset->Err > pidset->ErrLimit) || (pidset->Err < -pidset->ErrLimit)) 
	{
		Real_Kp = pidset->NoInteKp; 
		pidset->Inte += (pidset->IntePar)*pidset->Err;
		//计算积分 
//		pidset->Inte = 0;
	}else
	{
		Real_Kp = pidset->Kp;
		pidset->Inte += pidset->Err;
	} 
	//积分限幅
	if(pidset->Inte > pidset->InteLimitPost)
	{
		pidset->Inte = pidset->InteLimitPost;
	}else if(pidset->Inte < pidset->InteLimitNega)
	{
		pidset->Inte = pidset->InteLimitNega;
	}
	
	//计算输出值 
	pidset->OutValu =  (Real_Kp * pidset->Err) + \
						(pidset->Ki * pidset->Inte) +\
						 (pidset->Kd * pidset->Diff);
	//积分限幅
	if(pidset->OutValu > pidset->OutLimitPost)
	{
		pidset->OutValu = pidset->OutLimitPost; 
	}else if(pidset->OutValu < pidset->OutLimitNega)
	{
		pidset->OutValu = pidset->OutLimitNega;
	}
    //上次偏差
    pidset->ErrLast = pidset->Err;
	
}

float PIDController(PIDTypedef *pidset,float expvalue,float nowvalue)
{
    static uint8_t Deadcnt = 0;
	pidset->ExpValu = expvalue;
	pidset->NowValu = nowvalue;
	
	PIDCalculate(pidset);
	if(pidset->Err > -0.5 && pidset->Err < 0.5)
    {
        Deadcnt ++;
        if(Deadcnt > 5)
        {
            pidset->OutValu = 0;
        }
    }else
    {
        Deadcnt = 0;
    }
	return (pidset->OutValu);
}

//清除PID参数值
void ClearPidPar(PIDTypedef *pidset)
{
	pidset->Err = 0;
	pidset->Inte = 0;
	pidset->Diff = 0;
	pidset->OutValu = 0;
} 





