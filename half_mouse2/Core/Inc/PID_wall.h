/*
 * PID_wall.h
 *
 *  Created on: 2023/01/17
 *      Author: sf199
 */

#ifndef INC_PID_WALL_H_
#define INC_PID_WALL_H_


#include "stm32g4xx_hal.h"
#include "define.h"
//#define CONTROLLEFTWALL 1
//#define CONTROLRIGHTWALL 2

// 壁制御に使用する値
//#define SENSOR_GAIN 0.16*800/500//0.16横壁制御のゲイン
#define SENSOR_GAIN_P 0.5//0.16横壁制御のゲイン
#define SENSOR_GAIN_D 0.006//0.16横壁制御のゲイン
//#define SENSOR_GAIN_SHORT 0.5*800/1200//0.16横壁制御のゲイン最短用
#define SENSOR_GAIN_SHORT_P 0.4//0.16横壁制御のゲイン最短用
#define SENSOR_GAIN_SHORT_D -0.01//0.16横壁制御のゲイン最短用
#define CENTER_L 1685//左90
#define CENTER_R 1451//右90
#define CONTROLWALL_THRESHOLD_L 700//左壁制御の閾値110
#define CONTROLWALL_THRESHOLD_R 700//右壁制御の閾値110
#define CONTROLWALLCUT_THRESHOLD_L 157//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_R 110//右壁制御の壁切れの閾値

#define CONTROLWALLCUT_THRESHOLD_SHORT_L 180//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_SHORT_R 130//右壁制御の壁切れの閾値
#define SENSOR_L_MIN 740
#define SENSOR_L_MAX 2300
#define SENSOR_R_MIN 650
#define SENSOR_R_MAX 1800

//串制御
#define SKEWER_LIMIT 35//左90

//前壁制御3348,SEN3=1366,SEN4=1710
#define SENSOR_FRONT_GAIN 0.15
#define CENTER_FRONT_L 2678//前壁制御
#define CENTER_FRONT_R 3290//前壁制御
#define F_PRESENCE2 1100

//壁切れ
#define WALLCUT_THRESHOLD_L90 400
#define WALLCUT_THRESHOLD_R90 500
//#define WALLCUT_THRESHOLD_L45 100
//#define WALLCUT_THRESHOLD_R45 80
#define WALLCUT_THRESHOLD_L45 200
#define WALLCUT_THRESHOLD_R45 250
#define WALLCUT_THRESHOLD_DIFF_L45 -50
#define WALLCUT_THRESHOLD_DIFF_R45 -90
#define WALLCUT_THRESHOLD_DIFF_L45_SLANT -240
#define WALLCUT_THRESHOLD_DIFF_R45_SLANT -240//-1200

//壁切れの位置と区画の境目の距離(壁切れ位置-区画の境目)
#define CUTPLACE_TO_CENTER_L90 16
#define CUTPLACE_TO_CENTER_R90 18
#define CUTPLACE_TO_CENTER_L45 -13//10
#define CUTPLACE_TO_CENTER_R45 -13//10
//#define CUTPLACE_TO_CENTER_L90_2 -60
//#define CUTPLACE_TO_CENTER_R90_2 -60//大回りも90°を使用
#define CUTPLACE_TO_CENTER_L45_SLANT 4//17
#define CUTPLACE_TO_CENTER_R45_SLANT 2//20


//壁切れの距離補正(終了位置)壁切れてから臨界の
#define CUTPLACE_THRESHOLD_END_L90 55
#define CUTPLACE_THRESHOLD_END_R90 55
#define CUTPLACE_THRESHOLD_END_L90_2 25
#define CUTPLACE_THRESHOLD_END_R90_2 25
#define CUTPLACE_THRESHOLD_END_L45 32
#define CUTPLACE_THRESHOLD_END_R45 32
#define CUTPLACE_THRESHOLD_END_L45_SLANT 35//105
#define CUTPLACE_THRESHOLD_END_R45_SLANT 35//105

//壁切れ補正用(壁切れ時の横距離があった場合の縦補正)なしになってる
#define CENTER_FL 493//左90
#define CENTER_FR 801//右90
#define CENTER_FL_SLANT 3500//左90
#define CENTER_FR_SLANT 3500//右90
#define GAIN_WALLCUT 0//30/6
#define GAIN_WALLCUT_SLANT 0//210/2//中心より大きい方
#define GAIN_WALLCUT_SLANT2 0//4.8/2//中心より大きい方


//斜めの制御の変数
#define SENSOR_GAIN_SLANT90_P 0.95//0.099*800/170//0.081
#define SENSOR_GAIN_SLANT90_D -0.08//0.018*800/170//0.018
#define CONTROLWALL_THRESHOLD_SLANT_L 90//左壁制御の閾値110
#define CONTROLWALL_THRESHOLD_SLANT_R 90//右壁制御の閾値110
#define CONTROLWALLCUT_THRESHOLD_SLANT90_L 80//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_SLANT90_R 80//右壁制御の壁切れの閾値

#define SENSOR_GAIN_SLANT45_P 0.8//0.081*800/170//0.081
#define SENSOR_GAIN_SLANT45_D -0.08//0.018*800/170//0.018
#define CONTROLWALL_THRESHOLD_SLANT45_R 130//New
#define CONTROLWALL_THRESHOLD_SLANT45_L 130//New
#define CONTROLWALLCUT_THRESHOLD_SLANT45_L 80//左壁制御の壁切れの閾値
#define CONTROLWALLCUT_THRESHOLD_SLANT45_R 80//右壁制御の壁切れの閾値
//#define CONTROLWALLCUT_THRESHOLD_SLANT_L 100//左壁制御の壁切れの閾値
//#define CONTROLWALLCUT_THRESHOLD_SLANT_R 100//右壁制御の壁切れの閾値

//可制御の領域
#define AREAMIN_R0 1
#define AREAMAX_R0 15
#define AREAMIN_R1 35
#define AREAMAX_R1 60
#define AREAMIN_R2 100//
#define AREAMAX_R2 120

#define AREAMIN_L0 1
#define AREAMAX_L0 15
#define AREAMIN_L1 35
#define AREAMAX_L1 60
#define AREAMIN_L2 100
#define AREAMAX_L2 120

#define AREAMIN45_R0 20
#define AREAMAX45_R0 80
#define AREAMIN45_L0 20
#define AREAMAX45_L0 80

//近似直線の係数(matlabから算出)

#define	COEFFICIENT_R0_0	595.0192691
#define	COEFFICIENT_R0_1	39.53111503
#define	COEFFICIENT_R0_2	-0.344362422
#define	COEFFICIENT_R0_3	1.30E-01
#define	COEFFICIENT_R1_0	5697.60982
#define	COEFFICIENT_R1_1	-294.9095869
#define	COEFFICIENT_R1_2	5.48877161
#define	COEFFICIENT_R1_3	-0.034915121
#define	COEFFICIENT_R2_0	28835.02023
#define	COEFFICIENT_R2_1	-763.6457403
#define	COEFFICIENT_R2_2	6.70164149
#define	COEFFICIENT_R2_3	-1.92E-02
#define	COEFFICIENT_L0_0	653.7994791
#define	COEFFICIENT_L0_1	36.11904087
#define	COEFFICIENT_L0_2	-0.121365542
#define	COEFFICIENT_L0_3	0.142346613
#define	COEFFICIENT_L1_0	7213.753515
#define	COEFFICIENT_L1_1	-318.2533864
#define	COEFFICIENT_L1_2	5.064109257
#define	COEFFICIENT_L1_3	-0.028032283
#define	COEFFICIENT_L2_0	5105.59109
#define	COEFFICIENT_L2_1	-120.839599
#define	COEFFICIENT_L2_2	0.917581109
#define	COEFFICIENT_L2_3	-1.92E-03






#define	COEFFICIENT45_R0_0	400.4060863
#define	COEFFICIENT45_R0_1	-8.052144942
#define	COEFFICIENT45_R0_2	0.174959998
#define	COEFFICIENT45_R0_3	-4.55E-04
#define	COEFFICIENT45_L0_0	536.5474176
#define	COEFFICIENT45_L0_1	-14.50739364
#define	COEFFICIENT45_L0_2	0.249118514
#define	COEFFICIENT45_L0_3	-0.000690946











#define F_BREAK_THRESHOLD_90 1000
#define F_BREAK_THRESHOLD_45 300
#define F_BREAK_THRESHOLD_45SLANT 500

//typedef struct {
//	uint8_t g_WallControl_mode;//0で壁制御なし、1で通常の壁制御、2で斜めの制御
//	uint8_t g_WallControlStatus;
//
//
//}CONTROLWALL_MODE;
typedef struct{

	float error;
	float old_error;
//	float sigma_error;
	float delta_error;

}PIDW;

extern PIDW wall_normal;
extern PIDW wall_slant90;
extern PIDW wall_slant45;

extern uint8_t g_WallControl_mode;
extern uint8_t g_FrontWallControl_mode;
extern uint8_t g_wallCut_mode;

extern uint8_t g_WallControlStatus;
extern uint8_t g_WallControlStatus45;

extern float g_log_CenterSlantR45, g_log_CenterSlantL45;//log用
extern float g_log_CenterSlantR90, g_log_CenterSlantL90;//log用


extern volatile uint32_t NoWallCountR90, NoWallCountL90, NoWallCountR45, NoWallCountL45;
extern volatile uint32_t NoWallCountR45slant, NoWallCountL45slant;

extern volatile float NoWallDisplacementR90, NoWallDisplacementL90, NoWallDisplacementR45, NoWallDisplacementL45;
extern volatile float NoWallDisplacementR45slant, NoWallDisplacementL45slant;
extern volatile float NoWallDisplacementR45slant2, NoWallDisplacementL45slant2;

extern volatile  uint8_t front_wall_break_90,front_wall_break_45,front_wall_break_45slant;

void init_WallControl();

float calWallConrol();

void calFrontWallConrol(float *,float *);

void interrupt_WallCut(void);


#endif /* INC_PID_WALL_H_ */
