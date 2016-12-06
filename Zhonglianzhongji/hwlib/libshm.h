#ifndef _LIB_SHM_H_
#define _LIB_SHM_H_

#ifdef __cplusplus
extern "C"{
#endif

#define	u8 unsigned char
#define	u16 unsigned short
#define	u32 unsigned int
#define RAM_CAN_fData                   "RAM_CAN_fData"         // CAN�����ڴ��ļ�
#define CAN_LOCK                        1024+2               // CAN������

/************************************************/
/* CAN �м�����ݴ���ṹ */
/************************************************/
/*
typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//ͨ�ų�ʱ��־
	//ָʾ��־:0,1
	//������ ���� 
	u8 flagLeft;  //��ת
	u8 flagBattery;//��ƿָʾ�� ���ָʾ��
	u8 flagWidthlamp; //ʾ���
	u8 flagYG; //Զ���
	u8 flagSW; //ˮ��
	u8 flagJG; //�����
	u8 flagJY; //����
	u8 flagLCM; //������
	u8 flagLCM_seven; //������70
	u8 flagFDJYR; //������Ԥ��
	u8 flagGL; //����
	u8 flagKL; //������
	u8 flagSS;//��ɲ
	
	u8 flagECU;//ecu
	u8 flagPark;//ͣ��
	u8 flagFDJGZ; //����������
	u8 flagRight; //��ת
	u8 flagDC;//�����ź�

	u8 flagYYMainSK;//Һѹ������ɿ�
	u8 flagYYMainZJ;//Һѹ������Ž�
	u8 flagBHLdown;//�κ��ֽ���
	u8 flagBHLup;//�κ�����
	u8 flagGTup;//��̨��
	u8 flagGTdown;//��̨��
	u8 flagfastspeed;//�����ź�
	u8 flagXLTclose;//ж��Ͳ�ر�
	u8 flagXLTopen;//ж��Ͳ��
	u8 flagYSFL;//��ˮ����
	//u8 flagCD;//���ָʾ
	//���������
	u8 flagBHLdownDCF;//�κ��ֽ��͵�ŷ�
	u8 flagBHLupDCF;//�κ�������ŷ�
	u8 flagYYMainSKDCF;//Һѹ������ɿ���ŷ�
	u8 flagYYMainZJDCF;//Һѹ������Ž���ŷ�
	u8 flagGTupDCF;//��̨��
	u8 flagGTdownDCF;//��̨��
	u8 flagXLTcloseDCF;//ж��Ͳ�ر�
	u8 flagXLTopenDCF;//ж��Ͳ��
	u8 flagSCDCF;//ɲ����ŷ�
	u8 flagDCPower;//������Դ
	u8 flagYLDCF;//������ŷ�
	//ָʾ��ֵ
	int VolYL; //����
	int VolYeyayouwen;//Һѹ����
	int MIJI;//�׼�
	int SaLiangLV;//������ʧ��
	int FDJ_speed;//������ת��
	int GeChaheight;//���߶�
	u16 speed;
} RAM_CAN_sData;
*/

typedef struct
{
	unsigned char  can_no;
	u8 flagTXCS;//ͨ�ų�ʱ��־
	//ָʾ��־:0,1
	//������ ���� 
	u8 flagLeft;  //��ת
	u8 flagBattery;//��ƿָʾ�� ���ָʾ��
	u8 flagWidthlamp; //ʾ���
	u8 flagYG; //Զ���
	//u8 flagSW; //ˮ��
	u8 flagJG; //�����
	u8 flagJY; //����
	u8 flagLCM; //������
	u8 flagLCM_seven; //������70
	u8 flagFDJYR; //������Ԥ��
	u8 flagGL; //����
	u8 flagKL; //������
	u8 flagSS;//��ɲ
	
	u8 flagECU;//ecu
	u8 flagPark;//ͣ��
	u8 flagFDJGZ; //����������
	u8 flagRight; //��ת
	u8 flagDC;//�����ź�

	u8 flagYYMainSK;//Һѹ������ɿ�
	u8 flagYYMainZJ;//Һѹ������Ž�
	u8 flagBHLdown;//�κ��ֽ���
	u8 flagBHLup;//�κ�����
	u8 flagGTup;//��̨��
	u8 flagGTdown;//��̨��
	u8 flagfastspeed;//�����ź�
	u8 flagXLTclose;//ж��Ͳ�ر�
	u8 flagXLTopen;//ж��Ͳ��
	u8 flagYSFL;//��ˮ����
	//u8 flagCD;//���ָʾ

	//���������
	u8 flagBHLdownDCF;//�κ��ֽ��͵�ŷ�
	u8 flagBHLupDCF;//�κ�������ŷ�
	u8 flagYYMainSKDCF;//Һѹ������ɿ���ŷ�
	u8 flagYYMainZJDCF;//Һѹ������Ž���ŷ�
	u8 flagGTupDCF;//��̨��
	u8 flagGTdownDCF;//��̨��
	u8 flagXLTcloseDCF;//ж��Ͳ�ر�
	u8 flagXLTopenDCF;//ж��Ͳ��
	u8 flagSCDCF;//ɲ����ŷ�
	u8 flagDCPower;//������Դ
	u8 flagYLDCF;//������ŷ�
	//ָʾ��ֵ
	int VolSW;//ˮ��
	int VolYL; //����
	int VolJYWD;//�����¶�
	int VolJYYL;//����ѹ��
	int VolYeyayouwen;//Һѹ����
	int MIJI;//�׼�
	int SaLiangLV;//������ʧ��
	int FDJ_speed;//������ת��
	int GeChaheight;//���߶�
	int FTspeed;//����ת��
	int SYspeed;//����ת��
	int ZLspeed;//����ת��
	int HourSpeed;//ʱ��
	u16 speed;
} RAM_CAN_sData;

void Can_Ram_init();
void Can_Ram_Get(RAM_CAN_sData * RAM_CAN);
void Can_Ram_Set(RAM_CAN_sData * RAM_CAN);
//�ӹ����ڴ���
void lockshm();
//�⹲���ڴ���
void unlockshm();



#ifdef __cplusplus
}
#endif 

#endif
