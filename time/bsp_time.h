/*
*********************************************************************************************************
*
*	模块名称 : STM32-V6开发板定时相关驱动程序
*	文件名称 : bsp_time.h
*	说    明 : 主要使用中断或者直接读取寄存器的方式实现功能
*	备		注：使用的时候，需要初始化bsp_InitTimer并将此头文件引入main.h之中
*						使用的时候，需要初始化SysTick_ISR并将此头文件引入中断之中
*
*********************************************************************************************************
*/

#ifndef __BSP_TIME_H
#define __BSP_TIME_H
/*
	在此定义若干个软件定时器全局变量
	注意，必须增加__IO 即 volatile，因为这个变量在中断和主程序中同时被访问，有可能造成编译器错误优化。
*/
#define TMR_COUNT	4		/* 软件定时器的个数 （定时器ID范围 0 - 3) */

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* 一次工作模式 */
	TMR_AUTO_MODE = 1		/* 自动定时工作模式 */
}TMR_MODE_E;

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef struct
{
	volatile uint8_t Mode;		/* 计数器模式，1次性 */
	volatile uint8_t Flag;		/* 定时到达标志  */
	volatile uint32_t Count;	/* 计数器 */
	volatile uint32_t PreLoad;	/* 计数器预装值 */
}SOFT_TMR;


void bsp_DelayUS(uint32_t n);

void SysTick_ISR(void);
void bsp_InitTimer(void);

void bsp_StartAutoTimer(uint8_t _id, uint32_t _period);
void bsp_StartTimer(uint8_t _id, uint32_t _period);
void bsp_StopTimer(uint8_t _id);
uint8_t bsp_CheckTimer(uint8_t _id);
void bsp_DelayMS(uint32_t n);
int32_t bsp_GetRunTime(void);
int32_t bsp_CheckRunTime(int32_t _LastTime);

void bsp_RunPer1ms(void);
void bsp_RunPer10ms(void);

#endif