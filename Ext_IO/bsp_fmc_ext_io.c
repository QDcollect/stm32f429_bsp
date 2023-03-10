/*
*********************************************************************************************************
	��Ҫ���ܣ�
		1����չIO�ڼ�����ز�������
		
	ʹ��˵����
		1����ʼ��FMC��NE2Ƭѡ
		2����Ҫ��main���ó�ʼ������	bsp_InitExtIO();
		3����Ҫ��main.h֮�н��е���ͷ�ļ�	#include "bsp_fmc_ext_io.h"
*********************************************************************************************************
*/
#include "main.h"


#define  HC574_PORT	 *(uint32_t *)0x64001000	/*��Ӧ���ŵ���ص�ַ*/

__IO uint32_t g_HC574;	/* ����74HC574�˿�״̬ */

static void HC574_ConfigGPIO(void);
/*
*********************************************************************************************************
*	�� �� ��: bsp_InitExIO
*	����˵��: ������չIO��ص�GPIO. �ϵ�ֻ��ִ��һ�Ρ�
*	��    ��: ��
*	�� �� ֵ: ��
* ��ע��ʹ��ǰӦ�õ���һ��
*********************************************************************************************************
*/
void bsp_InitExtIO(void)
{
	HC574_ConfigGPIO();//��GPIO���Ž��г�ʼ��
		/* ��������һЩƬѡ��LED������Ϊ�� */
	g_HC574 = (NRF24L01_CE | VS1053_XDCS | LED1 | LED2 | LED3 | LED4);
	HC574_PORT = g_HC574;	/* дӲ���˿ڣ�����IO״̬ */
}
/*
*********************************************************************************************************
*	�� �� ��: HC574_ConfigGPIO
*	����˵��: ����GPIO��FMC�ܽ�����Ϊ���ù���
*	��    ��:  ��
*	�� �� ֵ: ��
*	˵��������һ�¸��ã������ʹ�ø��ã�ֱ�Ӷ�FMC����չ��IO���в���������ֱ���õ�ַ��ֵ�����ÿ�����Щ����
*********************************************************************************************************
*/
static void HC574_ConfigGPIO(void)
{
/*
	������STM32-V6��������߷�����4Ƭ74HC574����FMC 32λ�����ϡ�1����ַ�˿ڿ�����չ��32��IO
	������Ѱַ��Χ�����ǻ���ʹ��оƬ�ϵ����Ž��п������Ĵ���74HC574
	�൱������Ѱַ��Χ����ʵ�ָ��๦�ܵĸ���
	PD0/FMC_D2
	PD1/FMC_D3
	PD4/FMC_NOE		---- �������źţ�OE = Output Enable �� N ��ʾ����Ч
	PD5/FMC_NWE		-XX- д�����źţ�AD7606 ֻ�ж�����д�ź�
	PD8/FMC_D13
	PD9/FMC_D14
	PD10/FMC_D15
	PD14/FMC_D0
	PD15/FMC_D1

	PE7/FMC_D4
	PE8/FMC_D5
	PE9/FMC_D6
	PE10/FMC_D7
	PE11/FMC_D8
	PE12/FMC_D9
	PE13/FMC_D10
	PE14/FMC_D11
	PE15/FMC_D12
	
	PG0/FMC_A10		--- ����ƬѡFMC_NE2һ������
	PG1/FMC_A11		--- ����ƬѡFMC_NE2һ������
	PG9/FMC_NE2		--- ��Ƭѡ��OLED, 74HC574, DM9000, AD7606��	
	
	 +-------------------+------------------+
	 +   32-bits Mode: D31-D16              +
	 +-------------------+------------------+
	 | PH8 <-> FMC_D16   | PI0 <-> FMC_D24  |
	 | PH9 <-> FMC_D17   | PI1 <-> FMC_D25  |
	 | PH10 <-> FMC_D18  | PI2 <-> FMC_D26  |
	 | PH11 <-> FMC_D19  | PI3 <-> FMC_D27  |
	 | PH12 <-> FMC_D20  | PI6 <-> FMC_D28  |
	 | PH13 <-> FMC_D21  | PI7 <-> FMC_D29  |
	 | PH14 <-> FMC_D22  | PI9 <-> FMC_D30  |
	 | PH15 <-> FMC_D23  | PI10 <-> FMC_D31 |
	 +------------------+-------------------+	
*/	

	GPIO_InitTypeDef gpio_init_structure;

	/* ʹ�� GPIOʱ�� */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();


	/* ʹ��FMCʱ�� */
	__HAL_RCC_FMC_CLK_ENABLE();

	/* ���� GPIOD ��ص�IOΪ����������� */
	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init_structure.Alternate = GPIO_AF12_FMC;
	
	/* ����GPIOD */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
	                            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &gpio_init_structure);

	/* ����GPIOE */
	gpio_init_structure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
	                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &gpio_init_structure);

	/* ����GPIOG */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOG, &gpio_init_structure);
	
	/* ����GPIOH */
	gpio_init_structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
						| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOH, &gpio_init_structure);

	/* ����GPIOI */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
						| GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOI, &gpio_init_structure);
}

/*
*********************************************************************************************************
*	�� �� ��: HC574_SetPin
*	����˵��: ����74HC574�˿�ֵ
*	��    ��: _pin : �ܽźţ� 0-31; ֻ��ѡ1�������ܶ�ѡ
*			  _value : �趨��ֵ��0��1��0Ϊ�رգ�1Ϊ����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HC574_SetPin(uint32_t _pin, uint8_t _value)
{
	if (_value == 0)
	{
		g_HC574 &= (~_pin);
	}
	else
	{
		g_HC574 |= _pin;
	}
	HC574_PORT = g_HC574;//�Ի�����ַ�����辭�������ֵʵ�����ŵĿ���
}
/*
*********************************************************************************************************
*	�� �� ��: HC574_GetPin
*	����˵��: �ж�ָ���Ĺܽ������1����0
*	��    ��: _pin : �ܽźţ� 0-31; ֻ��ѡ1�������ܶ�ѡ
*	�� �� ֵ: 0��1
*********************************************************************************************************
*/
uint8_t HC574_GetPin(uint32_t _pin)
{
	if (g_HC574 & _pin)//�Ի�����ַ����״̬��ȡ
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: HC574_TogglePin
*	����˵��: ��ׯ74HC574�˿�ֵ
*	��    ��: _pin : �ܽźţ� 0-31; ֻ��ѡ1�������ܶ�ѡ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void HC574_TogglePin(uint32_t _pin)
{
	if (g_HC574 & _pin)
	{
		g_HC574 &= (~_pin);
	}
	else
	{
		g_HC574 |= _pin;
	}
	HC574_PORT = g_HC574;//�Ի�����ַ���账����
}