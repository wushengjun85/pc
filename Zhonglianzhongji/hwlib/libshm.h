#ifndef _LIB_SHM_H_
#define _LIB_SHM_H_

#ifdef __cplusplus
extern "C"{
#endif

#define	u8 unsigned char
#define	u16 unsigned short
#define	u32 unsigned int
#define RAM_CAN_fData                   "RAM_CAN_fData"         // CAN共享内存文件
#define CAN_LOCK                        1024+2               // CAN共享锁

/************************************************/
/* CAN 中间层数据传输结构 */
/************************************************/
/*
typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//通信超时标志
	//指示标志:0,1
	//开关量 输入 
	u8 flagLeft;  //左转
	u8 flagBattery;//电瓶指示灯 充电指示灯
	u8 flagWidthlamp; //示宽灯
	u8 flagYG; //远光灯
	u8 flagSW; //水温
	u8 flagJG; //近光灯
	u8 flagJY; //机油
	u8 flagLCM; //粮仓满
	u8 flagLCM_seven; //粮仓满70
	u8 flagFDJYR; //发动机预热
	u8 flagGL; //过滤
	u8 flagKL; //空气滤
	u8 flagSS;//手刹
	
	u8 flagECU;//ecu
	u8 flagPark;//停车
	u8 flagFDJGZ; //发动机故障
	u8 flagRight; //右转
	u8 flagDC;//倒车信号

	u8 flagYYMainSK;//液压主离合松开
	u8 flagYYMainZJ;//液压主离合张紧
	u8 flagBHLdown;//拔禾轮降低
	u8 flagBHLup;//拔河轮升
	u8 flagGTup;//割台升
	u8 flagGTdown;//割台降
	u8 flagfastspeed;//高速信号
	u8 flagXLTclose;//卸粮筒关闭
	u8 flagXLTopen;//卸粮筒打开
	u8 flagYSFL;//油水分离
	//u8 flagCD;//充电指示
	//开关量输出
	u8 flagBHLdownDCF;//拔禾轮降低电磁阀
	u8 flagBHLupDCF;//拔河轮升电磁阀
	u8 flagYYMainSKDCF;//液压主离合松开电磁阀
	u8 flagYYMainZJDCF;//液压主离合张紧电磁阀
	u8 flagGTupDCF;//割台升
	u8 flagGTdownDCF;//割台降
	u8 flagXLTcloseDCF;//卸粮筒关闭
	u8 flagXLTopenDCF;//卸粮筒打开
	u8 flagSCDCF;//刹车电磁阀
	u8 flagDCPower;//倒车电源
	u8 flagYLDCF;//溢流电磁阀
	//指示数值
	int VolYL; //油量
	int VolYeyayouwen;//液压油温
	int MIJI;//米计
	int SaLiangLV;//撒粮损失率
	int FDJ_speed;//发动机转速
	int GeChaheight;//割茬高度
	u16 speed;
} RAM_CAN_sData;
*/

typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//通信超时标志
	//指示标志:0,1
	//开关量 输入 
	u8 flagLeft;  //左转
	u8 flagBattery;//电瓶指示灯 充电指示灯
	u8 flagWidthlamp; //示宽灯
	u8 flagYG; //远光灯
	//u8 flagSW; //水温
	u8 flagJG; //近光灯
	u8 flagJY; //机油
	u8 flagLCM; //粮仓满
	u8 flagLCM_seven; //粮仓满70
	u8 flagFDJYR; //发动机预热
	u8 flagGL; //过滤
	u8 flagKL; //空气滤
	u8 flagSS;//手刹
	
	u8 flagECU;//ecu
	u8 flagPark;//停车
	u8 flagFDJGZ; //发动机故障
	u8 flagRight; //右转
	u8 flagDC;//倒车信号

	u8 flagYYMainSK;//液压主离合松开
	u8 flagYYMainZJ;//液压主离合张紧
	u8 flagBHLdown;//拔禾轮降低
	u8 flagBHLup;//拔河轮升
	u8 flagGTup;//割台升
	u8 flagGTdown;//割台降
	u8 flagfastspeed;//高速信号
	u8 flagXLTclose;//卸粮筒关闭
	u8 flagXLTopen;//卸粮筒打开
	u8 flagYSFL;//油水分离
	//u8 flagCD;//充电指示

	//开关量输出
	u8 flagBHLdownDCF;//拔禾轮降低电磁阀
	u8 flagBHLupDCF;//拔河轮升电磁阀
	u8 flagYYMainSKDCF;//液压主离合松开电磁阀
	u8 flagYYMainZJDCF;//液压主离合张紧电磁阀
	u8 flagGTupDCF;//割台升
	u8 flagGTdownDCF;//割台降
	u8 flagXLTcloseDCF;//卸粮筒关闭
	u8 flagXLTopenDCF;//卸粮筒打开
	u8 flagSCDCF;//刹车电磁阀
	u8 flagDCPower;//倒车电源
	u8 flagYLDCF;//溢流电磁阀
	//指示数值
	int VolSW;//水温
	int VolYL; //油量
	int VolJYWD;//机油温度
	int VolJYYL;//机油压力
	int VolYeyayouwen;//液压油温
	int MIJI;//米计
	int SaLiangLV;//撒粮损失率
	int FDJ_speed;//发动机转速
	int GeChaheight;//割茬高度
	int FTspeed;//复脱转速
	int SYspeed;//升运转速
	int ZLspeed;//轴流转速
	int HourSpeed;//时速
	u16 speed;
} RAM_CAN_sData;

void Can_Ram_init();
void Can_Ram_Get(RAM_CAN_sData * RAM_CAN);
void Can_Ram_Set(RAM_CAN_sData * RAM_CAN);
//加共享内存锁
void lockshm();
//解共享内存锁
void unlockshm();



#ifdef __cplusplus
}
#endif 

#endif
