#include "pid.h"



PIDTypedef LengthCtrlPid = 
{
	500.0f,       	//比例系数
    0.25f,       	//积分时间
    0.0f,       	//微分时间
    
    0.0f,  			//期望值
    0.0f,  			//当前值
    
    0.0f,     		//微分
    
    0.0f,     		//积分
    20000.0f,		//积分正限幅
    -20000.0f,		//积分负限幅
    
    0.0f,			//偏差过大 无积分时的Kp 
    
    0.0f,      		//本次偏差
    600.0f, 			//积分分离阈值
    0.0f,			//积分分离时的积分系数 ，如果是0则完全不积分 
	 
    0.0f,  			//上次偏差
    
    0.0f, 		    //输出值
    1500.0f, 		//输出正限幅
    -1500.0f			//输出负限幅 
};

