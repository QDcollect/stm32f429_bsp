/*
*********************************************************************************************************
*
*	ģ������ : STM32-V6�����嶨ʱ�����������
*	�ļ����� : bsp_time.h
*	˵    �� : ��Ҫʹ���жϻ���ֱ�Ӷ�ȡ�Ĵ����ķ�ʽʵ�ֹ���
*	��		ע��ʹ�õ�ʱ����Ҫ��ʼ��bsp_InitTimer������ͷ�ļ�����main.h֮��
*						ʹ�õ�ʱ����Ҫ��ʼ��SysTick_ISR������ͷ�ļ������ж�֮��
*
*********************************************************************************************************
*/

#ifndef __BSP_TIME_H
#define __BSP_TIME_H
/*
	�ڴ˶������ɸ������ʱ��ȫ�ֱ���
	ע�⣬��������__IO �� volatile����Ϊ����������жϺ���������ͬʱ�����ʣ��п�����ɱ����������Ż���
*/
#define TMR_COUNT	4		/* �����ʱ���ĸ��� ����ʱ��ID��Χ 0 - 3) */

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* һ�ι���ģʽ */
	TMR_AUTO_MODE = 1		/* �Զ���ʱ����ģʽ */
}TMR_MODE_E;

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef struct
{
	volatile uint8_t Mode;		/* ������ģʽ��1���� */
	volatile uint8_t Flag;		/* ��ʱ�����־  */
	volatile uint32_t Count;	/* ������ */
	volatile uint32_t PreLoad;	/* ������Ԥװֵ */
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