#ifndef __CAMERA_INTERFACE_H__
#define __CAMERA_INTERFACE_H__

#define IMG_WIDTH 320 //������Ƶ�Ŀ��Ϊ640 480
#define IMG_HEIGTH 240//������Ƶ�ĸ߶�Ϊ480 320


typedef enum __VIDEO_DEV_NO_EN
{
	VIDEO_DEV_0,
	VIDEO_DEV_1,
	VIDEO_DEV_BUTT
}VIDEO_DEV_NO_E;

typedef enum __VIDEO_INPUT_CAMERA_NO_EN
{
	CAMERA_AV_1,
	CAMERA_AV_2,
	CAMERA_AV_3,
	CAMERA_AV_4,
	CAMERA_AV_BUTT
}VIDEO_INPUT_CAMERA_NO_E;



/*****************************************************************
Function:
Description: ��ʼ����Ƶ�豸
Parameter: 
		[in] VideoDevNo,��Ƶ�豸���
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_VideoDev_Init(VIDEO_DEV_NO_E VideoDevNo);


/*****************************************************************
Function:
Description: ��ʼ��������Ƶ�豸
Parameter: 
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_AllVideoDev_init();


/*****************************************************************
Function:
Description: ȥ��ʼ����Ƶ�豸
Parameter: 
		[in] VideoDevNo,��Ƶ�豸���
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_VideoDev_Exit(VIDEO_DEV_NO_E VideoDevNo);


/*****************************************************************
Function:
Description: ȥ��ʼ��������Ƶ�豸
Parameter: 
		[in] VideoDevNo,��Ƶ�豸���
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_AllVideoDev_Exit();


/*****************************************************************
Function:
Description: ����Ƶ
Parameter: 
		[in] enCamNo,AV������
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_EnableVideoInput(VIDEO_INPUT_CAMERA_NO_E enCamNo);

/*****************************************************************
Function:
Description: �ر���Ƶ
Parameter:
		[in] enCamNo,AV������
Return:
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_DisableVideoInput(VIDEO_INPUT_CAMERA_NO_E enCamNo);


/*****************************************************************
Function:
Description: ��ȡ��Ƶ����
Parameter:
	[in] enCamNo,AV������
	[in,out] data,�����洢���ݵ�ַ
	[in]  size,�ռ��С
	[in] enRGBType,��ȡ��Ƶ����Ƶ������Ҫת���ɸ�RGB���ͣ�
		V4L2_PIX_FMT_RGB_CUSTOM ��Ҫת�����ͻ�������Ҫ�Լ�ת����
Return:
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
 typedef enum V4L2_PIX_FMT_CSC_RGB_TYPE_EN
{
    YUYV_CSC_RGB,
    YUYV_CSC_RGB888,
    UYVY_CSC_RGB565,
    YUV8888_CSC_RGB565,
    V4L2_PIX_FMT_CSC_RGB_CUSTOM,
    V4L2_PIX_FMT_CSC_BUTT
}V4L2_PIX_FMT_CSC_RGB_TYPE_E;

int HWE_GetVideoData(VIDEO_INPUT_CAMERA_NO_E enCamNo,unsigned char **data,unsigned int *size,V4L2_PIX_FMT_CSC_RGB_TYPE_E enRGBType);


/*****************************************************************
Function:
Description: �ͷ���Ƶ����
Parameter:
		[in] enCamNo,AV������
Return:
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_ReleaseVideoData(VIDEO_INPUT_CAMERA_NO_E enCamNo);


/*****************************************************************
Function:
Description: ��ʼ����
Parameter:
Return:
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
void HWE_Reverse_Start();


/*****************************************************************
Function:
Description: ��ʼ���
Parameter:
Return:
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
void HWE_Monitor_Start();


#endif
