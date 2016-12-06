#ifndef __CAMERA_INTERFACE_H__
#define __CAMERA_INTERFACE_H__

#define IMG_WIDTH 320 //定义视频的宽度为640 480
#define IMG_HEIGTH 240//定义视频的高度为480 320


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
Description: 初始化视频设备
Parameter: 
		[in] VideoDevNo,视频设备编号
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_VideoDev_Init(VIDEO_DEV_NO_E VideoDevNo);


/*****************************************************************
Function:
Description: 初始化所有视频设备
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
Description: 去初始化视频设备
Parameter: 
		[in] VideoDevNo,视频设备编号
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_VideoDev_Exit(VIDEO_DEV_NO_E VideoDevNo);


/*****************************************************************
Function:
Description: 去初始化所有视频设备
Parameter: 
		[in] VideoDevNo,视频设备编号
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
int HWE_AllVideoDev_Exit();


/*****************************************************************
Function:
Description: 打开视频
Parameter: 
		[in] enCamNo,AV输入编号
Return: 
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_EnableVideoInput(VIDEO_INPUT_CAMERA_NO_E enCamNo);

/*****************************************************************
Function:
Description: 关闭视频
Parameter:
		[in] enCamNo,AV输入编号
Return:
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_DisableVideoInput(VIDEO_INPUT_CAMERA_NO_E enCamNo);


/*****************************************************************
Function:
Description: 获取视频数据
Parameter:
	[in] enCamNo,AV输入编号
	[in,out] data,用来存储数据地址
	[in]  size,空间大小
	[in] enRGBType,获取视频的视频数据需要转换成该RGB类型，
		V4L2_PIX_FMT_RGB_CUSTOM 不要转换，客户根据需要自己转换；
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
Description: 释放视频数据
Parameter:
		[in] enCamNo,AV输入编号
Return:
		0,successful
		-1,failed
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/

int HWE_ReleaseVideoData(VIDEO_INPUT_CAMERA_NO_E enCamNo);


/*****************************************************************
Function:
Description: 开始倒车
Parameter:
Return:
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
void HWE_Reverse_Start();


/*****************************************************************
Function:
Description: 开始监控
Parameter:
Return:
Date:
	[2016/11/2]  wangxw add;
	
**********************************************************************/
void HWE_Monitor_Start();


#endif
