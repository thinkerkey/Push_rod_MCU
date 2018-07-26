#ifndef _PID_H_
#define _PID_H_

typedef struct{
    float Kp;       	//比例系数
    float Ki;       	//积分时间
    float Kd;       	//微分时间
    
    float ExpValu;  	//期望值
    float NowValu;  	//当前值
    
    float Diff;     	//微分
    
    float Inte;     	//积分
    float InteLimitPost;//积分正限幅
    float InteLimitNega;//积分正限幅
    
    float NoInteKp;		//偏差过大 无积分时的Kp 
    
    float Err;      	//本次偏差
    float ErrLimit; 	//积分分离阈值
    float IntePar;		//积分分离时的积分系数 ，如果是0则完全不积分 
	 
    float ErrLast;  	//上次偏差
    
    float OutValu;  	//输出值
    float OutLimitPost; //输出正限幅
    float OutLimitNega;	//输出负限幅 
}PIDTypedef;


extern PIDTypedef AltitudeUpPid;
extern PIDTypedef SinUpCtrlPid;
extern PIDTypedef SinDownCtrlPid;

void PIDCalculate(PIDTypedef *pidset);
float PIDController(PIDTypedef *pidset,float expvalue,float nowvalue);
void ClearPidPar(PIDTypedef *pidset);

#endif

