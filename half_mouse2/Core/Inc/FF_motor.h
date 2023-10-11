/*
 * FF_motor.h
 *
 *  Created on: 2023/01/21
 *      Author: sf199
 */

#ifndef INC_FF_MOTOR_H_
#define INC_FF_MOTOR_H_


//#define Im 0.00000121//kg/m^2 ロータ慣性モーメント
#define kb 0.0027767//Vs/rad 逆起電力定数
#define Tw 0.0001//0.00013//Nm 摩擦によるロス調整項目******************************

#define ng 39/9//ギヤ比
#define kt 0.00138//Nm/A トルク定数

#define Rm 1.07//1.07+0.3Ω 端子間抵抗*******************************************

//


#define TwT 0.00005 //7
#define kbT 0.0024767//Vs/rad 逆起電力定数 deg->rad->m変換sitenai



void feedforward_const_accel(float *,float,float,float *,float,float);

#endif /* INC_FF_MOTOR_H_ */
