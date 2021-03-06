#include "loop.h"
#include "ANO_Drv_MPU6050.h"
#include "imu.h"
#include "ANO_Data_Transfer.h"

loop_t loop;
//float maxt[9] = {0.5,1.5,2.5,3.5,1,4.5,2,1,1.1};
//float maxt2[9] = {1,1,0,0,2,0,0,3,0};
//float maxt3[9] = {0,1,0,1,0,0,4,0,0};
//float maxt4[9] = {0.5,1.5,2.5,3.5,1,4.5,2,1,1.1};
//float maxt5[9];
//arm_matrix_instance_f32 myS;
//arm_matrix_instance_f32 myS2;
//arm_matrix_instance_f32 myS3;
//arm_status maxcheck = ARM_MATH_TEST_FAILURE;
void Loop_check()  //TIME INTTERRUPT
{
	loop.time++; //u16
	loop.cnt_2ms++;
	loop.cnt_6ms++;
	loop.cnt_10ms++;
	loop.cnt_20ms++;
	loop.cnt_50ms++;

	if( loop.check_flag >= 2)
	{
		loop.err_flag ++;     //每累加一次，证明代码在预定周期2ms内没有跑完。
	}
	else
	{	
		loop.check_flag += 1;	//该标志位在循环的最后被清零
	}
	//LED_1ms_DRV(); 				//1ms中断里边，1ms执行一次
}

u32 test_time[10];
void Duty_2ms()
{
	static float fun_time = 0;
	test_time[0] = GetSysTime_us();
	fun_time = test_time[0] - fun_time;
	if (fun_time < 0)
	{
		fun_time = 2000.0f;
	}

#if POSE_DT_USE_USART1
	ANO_DT_Data_Exchange(); 			//数据发送
#endif // POSE_DT_USE_USART1

	LED_Flash_Control(1);

#if DL_DT_USE_USART3
	DL_DT_Data_Exchange();				//zigbee数据发送
#endif // DL_DT_USE_USART3

#if MPU9250
	MPU9250_Read_ACCEL_GYRO();
	MPU9250_Data_Prepare(fun_time / 1000000.0f);
	//IMUupdate(0.002, mpu9250.Gyro_deg.x, mpu9250.Gyro_deg.y, mpu9250.Gyro_deg.z, mpu9250.Acc.x, mpu9250.Acc.y, mpu9250.Acc.z, &Roll, &Pitch, &Yaw);
	//IMUupdate(0.002, mpu9250.Gyro_deg.x, mpu9250.Gyro_deg.y, mpu9250.Gyro_deg.z, mpu9250.Acc.x, mpu9250.Acc.y, mpu9250.Acc.z, &Roll_ANO, &Pitch_ANO, &Yaw_ANO);
	
	IMU_getInfo(fun_time / 1000000.0f);
//    arm_mat_init_f32(&myS,3,3,maxt);
//    arm_mat_init_f32(&myS2,3,3,maxt2);
//    arm_mat_init_f32(&myS3,3,3,maxt3);
//    maxcheck = arm_mat_add_f32(&myS,&myS2,&myS2);
//    maxcheck = arm_mat_inverse_f32(&myS,&myS2);
//    arm_mat_init_f32(&myS3,3,3,maxt4);
//    arm_mat_init_f32(&myS,3,3,maxt5);
//    arm_mat_mult_f32(&myS3,&myS2,&myS);
#endif // MPU9250
	
	fun_time = test_time[1] = GetSysTime_us();

	test_time[2] = test_time[1] - test_time[0];	
}


void Duty_6ms()
{
	//test_time[3] = GetSysTime_us();	

	//test_time[4] = GetSysTime_us();
	//test_time[5] = test_time[4] - test_time[3];
}
void Duty_10ms()
{
#if MPU9250
	MPU9250_Read_MAG();
#endif // MPU9250
}

void Duty_20ms()
{

}

void Duty_50ms()
{
#if MPU9250
	if (Mag_CALIBRATED == 1)
	{
		led_duty = 100;
		LED_Flash_Duty(led_duty);
	}
	else
	{
		led_duty = 40;
		LED_Flash_Duty(led_duty);
	}
#endif // MPU9250
}


void main_loop()
{
	if( loop.check_flag >= 1 )
	{
		
		//Duty_1ms();							//周期1ms的任务
		
		if( loop.cnt_2ms >= 2 )
		{
			loop.cnt_2ms = 0;
			Duty_2ms();						//周期2ms的任务
		}
		if( loop.cnt_6ms >= 6 )
		{
			loop.cnt_6ms = 0;
			Duty_6ms();						//周期5ms的任务
		}
		if( loop.cnt_10ms >= 10 )
		{
			loop.cnt_10ms = 0;
			Duty_10ms();					//周期10ms的任务
		} 
		if( loop.cnt_20ms >= 20 )
		{
			loop.cnt_20ms = 0;
			Duty_20ms();					//周期20ms的任务
		}
		if( loop.cnt_50ms >= 50 )
		{
			loop.cnt_50ms = 0;
			Duty_50ms();					//周期50ms的任务
		}
		
		loop.check_flag = 0;		//循环运行完毕标志
	}
	//ANO_NRF_Check_Event();
	//Usb_Hid_Receive();//主循环里不断查询
	

}
/******************* (C) COPYRIGHT 2016 ANO TECH *****END OF FILE************/


