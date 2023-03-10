/*
*********************************************************************************************************
	主要功能：
		1、拓展IO口及其相关操作函数
		
	使用说明：
		1、初始化FMC的NE2片选
		2、需要在main调用初始化函数	bsp_InitExtIO();
		3、需要在main.h之中进行调用头文件	#include "bsp_fmc_ext_io.h"
*********************************************************************************************************
*/
#include "main.h"


#define  HC574_PORT	 *(uint32_t *)0x64001000	/*对应引脚的相关地址*/

__IO uint32_t g_HC574;	/* 保存74HC574端口状态 */

static void HC574_ConfigGPIO(void);
/*
*********************************************************************************************************
*	函 数 名: bsp_InitExIO
*	功能说明: 配置扩展IO相关的GPIO. 上电只能执行一次。
*	形    参: 无
*	返 回 值: 无
* 备注：使用前应该调用一次
*********************************************************************************************************
*/
void bsp_InitExtIO(void)
{
	HC574_ConfigGPIO();//对GPIO引脚进行初始化
		/* 将开发板一些片选，LED口设置为高 */
	g_HC574 = (NRF24L01_CE | VS1053_XDCS | LED1 | LED2 | LED3 | LED4);
	HC574_PORT = g_HC574;	/* 写硬件端口，更改IO状态 */
}
/*
*********************************************************************************************************
*	函 数 名: HC574_ConfigGPIO
*	功能说明: 配置GPIO，FMC管脚设置为复用功能
*	形    参:  无
*	返 回 值: 无
*	说明：设置一下复用，如果不使用复用，直接对FMC所扩展的IO进行操作，可以直接用地址赋值，不用开启这些复用
*********************************************************************************************************
*/
static void HC574_ConfigGPIO(void)
{
/*
	安富莱STM32-V6开发板接线方法：4片74HC574挂在FMC 32位总线上。1个地址端口可以扩展出32个IO
	增加了寻址范围，但是还是使用芯片上的引脚进行控制外界寄存器74HC574
	相当于扩建寻址范围，来实现更多功能的复用
	PD0/FMC_D2
	PD1/FMC_D3
	PD4/FMC_NOE		---- 读控制信号，OE = Output Enable ， N 表示低有效
	PD5/FMC_NWE		-XX- 写控制信号，AD7606 只有读，无写信号
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
	
	PG0/FMC_A10		--- 和主片选FMC_NE2一起译码
	PG1/FMC_A11		--- 和主片选FMC_NE2一起译码
	PG9/FMC_NE2		--- 主片选（OLED, 74HC574, DM9000, AD7606）	
	
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

	/* 使能 GPIO时钟 */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();


	/* 使能FMC时钟 */
	__HAL_RCC_FMC_CLK_ENABLE();

	/* 设置 GPIOD 相关的IO为复用推挽输出 */
	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init_structure.Alternate = GPIO_AF12_FMC;
	
	/* 配置GPIOD */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
	                            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &gpio_init_structure);

	/* 配置GPIOE */
	gpio_init_structure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
	                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &gpio_init_structure);

	/* 配置GPIOG */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOG, &gpio_init_structure);
	
	/* 配置GPIOH */
	gpio_init_structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
						| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOH, &gpio_init_structure);

	/* 配置GPIOI */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
						| GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOI, &gpio_init_structure);
}

/*
*********************************************************************************************************
*	函 数 名: HC574_SetPin
*	功能说明: 设置74HC574端口值
*	形    参: _pin : 管脚号， 0-31; 只能选1个，不能多选
*			  _value : 设定的值，0或1（0为关闭，1为开）
*	返 回 值: 无
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
	HC574_PORT = g_HC574;//对基本地址，赋予经过处理的值实现引脚的控制
}
/*
*********************************************************************************************************
*	函 数 名: HC574_GetPin
*	功能说明: 判断指定的管脚输出是1还是0
*	形    参: _pin : 管脚号， 0-31; 只能选1个，不能多选
*	返 回 值: 0或1
*********************************************************************************************************
*/
uint8_t HC574_GetPin(uint32_t _pin)
{
	if (g_HC574 & _pin)//对基本地址进行状态读取
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
*	函 数 名: HC574_TogglePin
*	功能说明: 饭庄74HC574端口值
*	形    参: _pin : 管脚号， 0-31; 只能选1个，不能多选
*	返 回 值: 无
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
	HC574_PORT = g_HC574;//对基本地址赋予处理结果
}