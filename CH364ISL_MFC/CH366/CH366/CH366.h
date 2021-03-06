#include "stdafx.h"


/******************************************************************************* 
1、 函数名称： OpenTP366
2、 功能描述： 打开366设备
3、 输入参数： 无
4、 返 回 值： -1   DLL加载失败
			 -2    驱动加载失败
			 -3    未找到卡
			 1     打开成功 
5、 动态内存： 无
6、 代码设计：  阿毛
7、 开发日期： 2011-9-1 14:42:46
8、 备    注： 
********************************************************************************/ 
extern "C" __declspec(dllexport) int OpenCH366(void);

/******************************************************************************* 
1、 函数名称： GetNet
2、 功能描述： 得到当前的网络类型
3、 输入参数：  无
4、 返 回 值： 返回2为外网，1为内网
5、 动态内存： 无
6、 代码设计：  阿毛
7、 开发日期： 2011-9-1 15:09:16
8、 备    注： 
********************************************************************************/ 
extern "C" __declspec(dllexport) int GetNet(void);

/******************************************************************************* 
1、 函数名称： ChangeNet
2、 功能描述： 
3、 输入参数： bNetBit    为1时，切换到外网;否则切换到内网。
			 iPowerOff    为1时，重启计算机，为2休眠计算机。如果是休眠的话，计算机将自动唤醒 为3时关闭计算机
			 bInterFace 为1时，开机时出现选择界面，否则不出选择界面。
4、 返 回 值：  0、成功切换
			   1、未找到卡
			   2、获取网络环境失败
			   3、休眠切换读出数据失败
			   4、休眠切换写入换醒数据失败
			   5、参数输入有误
			   6、重启、休眠、关机出错
			   7、切换网络类型出错
5、 动态内存： 无
6、 代码设计：  阿毛
7、 开发日期： 2011-9-23 17:48:03
8、 备    注： 此处未加处出处理代码
********************************************************************************/ 
extern "C" __declspec(dllexport) int ChangeNet(BOOL bNetBit, int iPowerOff, BOOL bInterFace);

//关闭366设备
extern "C" __declspec(dllexport) void CloseCH366(void);

//自定义TRACE函数
extern "C" __declspec(dllexport) void MyTRACE(WCHAR *fmt, ...);