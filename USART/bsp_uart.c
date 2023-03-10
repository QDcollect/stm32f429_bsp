/*
*********************************************************************************************************
	��Ҫ���ܣ�
		1��ʹ��FIFOʵ�ַ�����ʽ�����շ�	
		2������ʵ��printf
	ʹ��˵����
		1����Ҫ��main���ó�ʼ������	bsp_InitUart();
		2����Ҫ��main.h֮�н��е���ͷ�ļ�	#include "bsp_uart.h"
		3����Ҫ������Ӧ���жϣ����ļ�������ʵ��FIFO��������ݣ�����ע�͵���Ӧ�Ļص������Է�ֹ�ظ�����
				��ñ�ɾ������Ȼ��֪��Ϊɶ�����ǻ������
		4����Ҫ����ͷ�ļ�	#include <stdio.h>	#include <string.h>	#include <stdlib.h>
		5����Ҫ��MDK�Ͽ���MicroLIB��ʹ����ȷ�ı�������compiler��
*********************************************************************************************************
*/

#include "main.h"


static void UartVarInit(void);
static void InitHardUart(void);

/* ����ÿ�����ڽṹ����� */
/* ��ʼ���ṹ�����	���������� */

#if UART1_FIFO_EN == 1
	static UART_T g_tUart1;												/* �����ṹ����� */
	static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART2_FIFO_EN == 1
	static UART_T g_tUart2;												/* �����ṹ����� */
	static uint8_t g_TxBuf2[UART2_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf2[UART2_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART3_FIFO_EN == 1
	static UART_T g_tUart3;												/* �����ṹ����� */
	static uint8_t g_TxBuf3[UART3_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf3[UART3_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART4_FIFO_EN == 1
	static UART_T g_tUart4;												/* �����ṹ����� */
	static uint8_t g_TxBuf4[UART4_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf4[UART4_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART5_FIFO_EN == 1
	static UART_T g_tUart5;												/* �����ṹ����� */
	static uint8_t g_TxBuf5[UART5_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf5[UART5_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART6_FIFO_EN == 1
	static UART_T g_tUart6;												/* �����ṹ����� */
	static uint8_t g_TxBuf6[UART6_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf6[UART6_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART7_FIFO_EN == 1
	static UART_T g_tUart7;												/* �����ṹ����� */
	static uint8_t g_TxBuf7[UART7_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf7[UART7_RX_BUF_SIZE];		/* ���ջ����� */
#endif

#if UART8_FIFO_EN == 1
	static UART_T g_tUart8;												/* �����ṹ����� */
	static uint8_t g_TxBuf8[UART8_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf8[UART8_RX_BUF_SIZE];		/* ���ջ����� */
#endif
		

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitUart
*	����˵��: ��ʼ������Ӳ��������ȫ�ֱ�������ֵ.
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitUart(void)
{
	
	UartVarInit();		/* �����ȳ�ʼ��ȫ�ֱ���,������Ӳ�� */
	InitHardUart();		/* �������������������ô���	*/
	
	/*��ش��ڵĳ�ʼ����Ҫʹ��CUBEMX���г�ʼ��*/
}

/*
*********************************************************************************************************
*	�� �� ��: UartVarInit
*	����˵��: ��ʼ��������صı���	������ؽṹ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void UartVarInit(void)
{
#if UART1_FIFO_EN == 1
	g_tUart1.uart = USART1;						/* STM32 �����豸 ��Ӧ���ǳ�ʼ���õ�ַ�뱾�ļ��޹�*/
	g_tUart1.pTxBuf = g_TxBuf1;					/* ���ͻ�����ָ�� */
	g_tUart1.pRxBuf = g_RxBuf1;					/* ���ջ�����ָ�� */
	g_tUart1.usTxBufSize = UART1_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart1.usRxBufSize = UART1_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart1.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart1.usTxRead = 0;						/* ����FIFO������ */
	g_tUart1.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart1.usRxRead = 0;						/* ����FIFO������ */
	g_tUart1.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart1.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart1.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart1.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart1.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart1.Sending = 0;						/* ���ڷ����б�־ */
#endif

#if UART2_FIFO_EN == 1
	g_tUart2.uart = USART2;						/* STM32 �����豸 */
	g_tUart2.pTxBuf = g_TxBuf2;					/* ���ͻ�����ָ�� */
	g_tUart2.pRxBuf = g_RxBuf2;					/* ���ջ�����ָ�� */
	g_tUart2.usTxBufSize = UART2_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart2.usRxBufSize = UART2_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart2.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart2.usTxRead = 0;						/* ����FIFO������ */
	g_tUart2.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart2.usRxRead = 0;						/* ����FIFO������ */
	g_tUart2.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart2.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart2.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart2.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart2.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart2.Sending = 0;						/* ���ڷ����б�־ */
#endif

/*ʹ��RS485������*/
#if UART3_FIFO_EN == 1
	g_tUart3.uart = USART3;						/* STM32 �����豸 */
	g_tUart3.pTxBuf = g_TxBuf3;					/* ���ͻ�����ָ�� */
	g_tUart3.pRxBuf = g_RxBuf3;					/* ���ջ�����ָ�� */
	g_tUart3.usTxBufSize = UART3_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart3.usRxBufSize = UART3_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart3.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart3.usTxRead = 0;						/* ����FIFO������ */
	g_tUart3.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart3.usRxRead = 0;						/* ����FIFO������ */
	g_tUart3.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart3.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart3.SendBefor = RS485_SendBefor;		/* ��������ǰ�Ļص����� */
	g_tUart3.SendOver = RS485_SendOver;			/* ������Ϻ�Ļص����� */
	g_tUart3.ReciveNew = RS485_ReciveNew;		/* ���յ������ݺ�Ļص����� */
	g_tUart3.Sending = 0;						/* ���ڷ����б�־ */
#endif

#if UART4_FIFO_EN == 1
	g_tUart4.uart = UART4;						/* STM32 �����豸 */
	g_tUart4.pTxBuf = g_TxBuf4;					/* ���ͻ�����ָ�� */
	g_tUart4.pRxBuf = g_RxBuf4;					/* ���ջ�����ָ�� */
	g_tUart4.usTxBufSize = UART4_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart4.usRxBufSize = UART4_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart4.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart4.usTxRead = 0;						/* ����FIFO������ */
	g_tUart4.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart4.usRxRead = 0;						/* ����FIFO������ */
	g_tUart4.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart4.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart4.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart4.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart4.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart4.Sending = 0;						/* ���ڷ����б�־ */
#endif

#if UART5_FIFO_EN == 1
	g_tUart5.uart = UART5;						/* STM32 �����豸 */
	g_tUart5.pTxBuf = g_TxBuf5;					/* ���ͻ�����ָ�� */
	g_tUart5.pRxBuf = g_RxBuf5;					/* ���ջ�����ָ�� */
	g_tUart5.usTxBufSize = UART5_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart5.usRxBufSize = UART5_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart5.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart5.usTxRead = 0;						/* ����FIFO������ */
	g_tUart5.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart5.usRxRead = 0;						/* ����FIFO������ */
	g_tUart5.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart5.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart5.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart5.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart5.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart5.Sending = 0;						/* ���ڷ����б�־ */
#endif


#if UART6_FIFO_EN == 1
	g_tUart6.uart = USART6;						/* STM32 �����豸 */
	g_tUart6.pTxBuf = g_TxBuf6;					/* ���ͻ�����ָ�� */
	g_tUart6.pRxBuf = g_RxBuf6;					/* ���ջ�����ָ�� */
	g_tUart6.usTxBufSize = UART6_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart6.usRxBufSize = UART6_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart6.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart6.usTxRead = 0;						/* ����FIFO������ */
	g_tUart6.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart6.usRxRead = 0;						/* ����FIFO������ */
	g_tUart6.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart6.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart6.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart6.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart6.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart6.Sending = 0;						/* ���ڷ����б�־ */
#endif

#if UART7_FIFO_EN == 1
	g_tUart7.uart = UART7;						/* STM32 �����豸 */
	g_tUart7.pTxBuf = g_TxBuf7;					/* ���ͻ�����ָ�� */
	g_tUart7.pRxBuf = g_RxBuf7;					/* ���ջ�����ָ�� */
	g_tUart7.usTxBufSize = UART7_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart7.usRxBufSize = UART7_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart7.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart7.usTxRead = 0;						/* ����FIFO������ */
	g_tUart7.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart7.usRxRead = 0;						/* ����FIFO������ */
	g_tUart7.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart7.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart7.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart7.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart7.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart7.Sending = 0;						/* ���ڷ����б�־ */
#endif

#if UART8_FIFO_EN == 1
	g_tUart8.uart = UART8;						/* STM32 �����豸 */
	g_tUart8.pTxBuf = g_TxBuf8;					/* ���ͻ�����ָ�� */
	g_tUart8.pRxBuf = g_RxBuf8;					/* ���ջ�����ָ�� */
	g_tUart8.usTxBufSize = UART8_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart8.usRxBufSize = UART8_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart8.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart8.usTxRead = 0;						/* ����FIFO������ */
	g_tUart8.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart8.usRxRead = 0;						/* ����FIFO������ */
	g_tUart8.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart8.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart8.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart8.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart8.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
	g_tUart8.Sending = 0;						/* ���ڷ����б�־ */
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: InitHardUart
*	����˵��: ���ô��ڵ�Ӳ�������������ʣ�����λ��ֹͣλ����ʼλ��У��λ���ж�ʹ�ܣ��ʺ���STM32-H7������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void InitHardUart(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;


#if UART1_FIFO_EN == 1		/* ����1 */
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	// USART_CR1_PEIE | USART_CR1_RXNEIE
	SET_BIT(USART1->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif

#if UART2_FIFO_EN == 1		/* ����2 */
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(USART2->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif

#if UART3_FIFO_EN == 1			/* ����3 */

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(USART3->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif

#if UART4_FIFO_EN == 1			/* ����4 TX = PC10   RX = PC11 */	

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(UART4->CR1, USART_CR1_RXNEIE);	/* ʹ��RX�����ж� */
#endif

#if UART5_FIFO_EN == 1			/* ����5 TX = PC12   RX = PD2 */
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(UART5->CR1, USART_CR1_RXNEIE);	/* ʹ��RX�����ж� */
#endif

#if UART6_FIFO_EN == 1			/* USART6 */	

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(USART6->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif

#if UART7_FIFO_EN == 1			/* UART7 */
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(UART7->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif

#if UART8_FIFO_EN == 1			/* UART8 */
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* ���TC������ɱ�־ */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* ���RXNE���ձ�־ */
	SET_BIT(UART8->CR1, USART_CR1_RXNEIE);	/* ʹ��PE. RX�����ж� */
#endif
}


/*
*********************************************************************************************************
*	�� �� ��: ComToUart
*	����˵��: ��COM�˿ں�ת��ΪUART���ṹ�壩ָ��(��ʹ����غ�����ʱ���õ���COM�˿ں�)
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*	�� �� ֵ: uartָ��
*********************************************************************************************************
*/
UART_T *ComToUart(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return &g_tUart1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return &g_tUart2;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return &g_tUart3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return &g_tUart4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return &g_tUart5;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM6)
	{
		#if UART6_FIFO_EN == 1
			return &g_tUart6;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM7)
	{
		#if UART7_FIFO_EN == 1
			return &g_tUart7;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM8)
	{
		#if UART8_FIFO_EN == 1
			return &g_tUart8;
		#else
			return 0;
		#endif
	}	
	else
	{
		Error_Handler();
		return 0;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: ComToUart
*	����˵��: ��COM�˿ں�ת��Ϊ USART_TypeDef* USARTx��HAL���е���ؼĴ����ṹ�壬�Ľ��ṹ����Ҫ�����
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*	�� �� ֵ: USART_TypeDef*,  USART1, USART2, USART3, UART4, UART5��USART6��UART7��UART8��
*********************************************************************************************************
*/
USART_TypeDef *ComToUSARTx(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return USART1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return USART2;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return USART3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return UART4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return UART5;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM6)
	{
		#if UART6_FIFO_EN == 1
			return USART6;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM7)
	{
		#if UART7_FIFO_EN == 1
			return UART7;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM8)
	{
		#if UART8_FIFO_EN == 1
			return UART8;
		#else
			return 0;
		#endif
	}	
	
	else
	{
		/* �����κδ��� */
		return 0;
	}
}


/*
*********************************************************************************************************
*	�� �� ��: UartSend
*	����˵��: ��д���ݵ�UART���ͻ�����,�����������жϡ��жϴ�����������Ϻ��Զ��رշ����ж�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen)
{
	uint16_t i;

	for (i = 0; i < _usLen; i++)
	{
		/* ������ͻ������Ѿ����ˣ���ȴ��������� */
		while (1)
		{
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = _pUart->usTxCount;
			ENABLE_INT();

			if (usCount < _pUart->usTxBufSize)
			{
				break;
			}
			else if(usCount == _pUart->usTxBufSize)/* ���������������� */
			{
				if((_pUart->uart->CR1 & USART_CR1_TXEIE) == 0)
				{
					SET_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);
				}  
			}
		}

		/* �����������뷢�ͻ����� */
		_pUart->pTxBuf[_pUart->usTxWrite] = _ucaBuf[i];

		DISABLE_INT();
		if (++_pUart->usTxWrite >= _pUart->usTxBufSize)
		{
			_pUart->usTxWrite = 0;
		}
		_pUart->usTxCount++;
		ENABLE_INT();
	}

	SET_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);	/* ʹ�ܷ����жϣ��������գ� */
}

/*
*********************************************************************************************************
*	�� �� ��: UartGetChar
*	����˵��: �Ӵ��ڽ��ջ�������ȡ1�ֽ����� ��������������ã�
*	��    ��: _pUart : �����豸
*			  _pByte : ��Ŷ�ȡ���ݵ�ָ��
*	�� �� ֵ: 0 ��ʾ������  1��ʾ��ȡ������
*********************************************************************************************************
*/
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte)
{
	uint16_t usCount;

	/* usRxWrite �������жϺ����б���д���������ȡ�ñ���ʱ����������ٽ������� */
	DISABLE_INT();
	usCount = _pUart->usRxCount;
	ENABLE_INT();

	/* �������д������ͬ���򷵻�0 */
	//if (_pUart->usRxRead == usRxWrite)
	if (usCount == 0)	/* �Ѿ�û������ */
	{
		return 0;
	}
	else
	{
		*_pByte = _pUart->pRxBuf[_pUart->usRxRead];		/* �Ӵ��ڽ���FIFOȡ1������ */

		/* ��дFIFO������ */
		DISABLE_INT();
		if (++_pUart->usRxRead >= _pUart->usRxBufSize)
		{
			_pUart->usRxRead = 0;
		}
		_pUart->usRxCount--;
		ENABLE_INT();
		return 1;
	}
}

/*
*********************************************************************************************************
*   �� �� ��: UartTxEmpty
*   ����˵��: �жϷ��ͻ������Ƿ�Ϊ�ա�
*   ��    ��:  _pUart : �����豸
*   �� �� ֵ: 1Ϊ�ա�0Ϊ���ա�
*********************************************************************************************************
*/
uint8_t UartTxEmpty(COM_PORT_E _ucPort)
{
   UART_T *pUart;
   uint8_t Sending;
   
   pUart = ComToUart(_ucPort);
   if (pUart == 0)
   {
      return 0;
   }

   Sending = pUart->Sending;

   if (Sending != 0)
   {
      return 0;
   }
   return 1;
}




/*
*********************************************************************************************************
*	�� �� ��: UartIRQ
*	����˵��: ���жϷ��������ã�ͨ�ô����жϴ�����
*	��    ��: _pUart : �����豸
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void UartIRQ(UART_T *_pUart)
{
	uint32_t isrflags   = READ_REG(_pUart->uart->SR);
	uint32_t cr1its     = READ_REG(_pUart->uart->CR1);
	uint32_t cr3its     = READ_REG(_pUart->uart->CR3);
	
	/* ��������ж�  */
	if ((isrflags & USART_SR_RXNE) != RESET)
	{
		/* �Ӵ��ڽ������ݼĴ�����ȡ���ݴ�ŵ�����FIFO */
		uint8_t ch;

		ch = READ_REG(_pUart->uart->DR);
		_pUart->pRxBuf[_pUart->usRxWrite] = ch;
		if (++_pUart->usRxWrite >= _pUart->usRxBufSize)
		{
			_pUart->usRxWrite = 0;
		}
		if (_pUart->usRxCount < _pUart->usRxBufSize)
		{
			_pUart->usRxCount++;
		}

		/* �ص�����,֪ͨӦ�ó����յ�������,һ���Ƿ���1����Ϣ��������һ����� */
		//if (_pUart->usRxWrite == _pUart->usRxRead)
		//if (_pUart->usRxCount == 1)
		{
			if (_pUart->ReciveNew)
			{
				_pUart->ReciveNew(ch); /* ���磬����MODBUS����������ֽ��� */
			}
		}
	}

	/* �����ͻ��������ж� */
	if ( ((isrflags & USART_SR_TXE) != RESET) && (cr1its & USART_CR1_TXEIE) != RESET)
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
			/* ���ͻ�������������ȡ��ʱ�� ��ֹ���ͻ��������ж� ��ע�⣺��ʱ���1�����ݻ�δ����������ϣ�*/
			//USART_ITConfig(_pUart->uart, USART_IT_TXE, DISABLE);
			CLEAR_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);

			/* ʹ�����ݷ�������ж� */
			//USART_ITConfig(_pUart->uart, USART_IT_TC, ENABLE);
			SET_BIT(_pUart->uart->CR1, USART_CR1_TCIE);
		}
		else
		{
			_pUart->Sending = 1;
			
			/* �ӷ���FIFOȡ1���ֽ�д�봮�ڷ������ݼĴ��� */
			//USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			_pUart->uart->DR = _pUart->pTxBuf[_pUart->usTxRead];
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}

	}
	/* ����bitλȫ��������ϵ��ж� */
	if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
			/* �������FIFO������ȫ��������ϣ���ֹ���ݷ�������ж� */
			//USART_ITConfig(_pUart->uart, USART_IT_TC, DISABLE);
			CLEAR_BIT(_pUart->uart->CR1, USART_CR1_TCIE);

			/* �ص�����, һ����������RS485ͨ�ţ���RS485оƬ����Ϊ����ģʽ��������ռ���� */
			if (_pUart->SendOver)
			{
				_pUart->SendOver();
			}
			
			_pUart->Sending = 0;
		}
		else
		{
			/* ��������£��������˷�֧ */

			/* �������FIFO�����ݻ�δ��ϣ���ӷ���FIFOȡ1������д�뷢�����ݼĴ��� */
			//USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			_pUart->uart->DR = _pUart->pTxBuf[_pUart->usTxRead];
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}
	}
}


/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler��
*	����˵��: USART�жϷ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UartIRQ(&g_tUart1);
}
#endif

#if UART2_FIFO_EN == 1
void USART2_IRQHandler(void)
{
	UartIRQ(&g_tUart2);
}
#endif

#if UART3_FIFO_EN == 1
void USART3_IRQHandler(void)
{
	UartIRQ(&g_tUart3);
}
#endif

#if UART4_FIFO_EN == 1
void UART4_IRQHandler(void)
{
	UartIRQ(&g_tUart4);
}
#endif

#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	UartIRQ(&g_tUart5);
}
#endif

#if UART6_FIFO_EN == 1
void USART6_IRQHandler(void)
{
	UartIRQ(&g_tUart6);
}
#endif

#if UART7_FIFO_EN == 1
void UART7_IRQHandler(void)
{
	UartIRQ(&g_tUart7);
}
#endif

#if UART8_FIFO_EN == 1
void UART8_IRQHandler(void)
{
	UartIRQ(&g_tUart8);
}
#endif




/*
*********************************************************************************************************
*	�� �� ��: comSendBuf
*	����˵��: �򴮿ڷ���һ�����ݡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*			  _ucaBuf: �����͵����ݻ�����
*			  _usLen : ���ݳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	if (pUart->SendBefor != 0)
	{
		pUart->SendBefor();		/* �����RS485ͨ�ţ���������������н�RS485����Ϊ����ģʽ */
	}

	UartSend(pUart, _ucaBuf, _usLen);
}

/*
*********************************************************************************************************
*	�� �� ��: comSendChar
*	����˵��: �򴮿ڷ���1���ֽڡ����ݷŵ����ͻ��������������أ����жϷ�������ں�̨��ɷ���
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*			  _ucByte: �����͵�����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte)
{
	comSendBuf(_ucPort, &_ucByte, 1);
}
/*
*********************************************************************************************************
*	�� �� ��: comGetChar
*	����˵��: �ӽ��ջ�������ȡ1�ֽڣ��������������������ݾ��������ء�
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*			  _pByte: ���յ������ݴ���������ַ
*	�� �� ֵ: 0 ��ʾ������, 1 ��ʾ��ȡ����Ч�ֽ�
*********************************************************************************************************
*/
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return 0;
	}

	return UartGetChar(pUart, _pByte);
}

/*
*********************************************************************************************************
*	�� �� ��: comClearTxFifo
*	����˵��: ���㴮�ڷ��ͻ�����
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void comClearTxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usTxWrite = 0;
	pUart->usTxRead = 0;
	pUart->usTxCount = 0;
}

/*
*********************************************************************************************************
*	�� �� ��: comClearRxFifo
*	����˵��: ���㴮�ڽ��ջ�����
*	��    ��: _ucPort: �˿ں�(COM1 - COM8)
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void comClearRxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usRxWrite = 0;
	pUart->usRxRead = 0;
	pUart->usRxCount = 0;
}




/*
*********************************************************************************************************
*	�� �� ��: fputc
*	����˵��: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int fputc(int ch, FILE *f)
{
#if 1	/* ����Ҫprintf���ַ�ͨ�������ж�FIFO���ͳ�ȥ��printf�������������� */
	comSendChar(COM1, ch);
	
	return ch;
#else	/* ����������ʽ����ÿ���ַ�,�ȴ����ݷ������ */
	/* дһ���ֽڵ�USART1 */
	USART1->DR = ch;
	
	/* �ȴ����ͽ��� */
	while((USART1->SR & USART_SR_TC) == 0)
	{}
	
	return ch;
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: fgetc
*	����˵��: �ض���getc��������������ʹ��getchar�����Ӵ���1��������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int fgetc(FILE *f)
{

#if 1	/* �Ӵ��ڽ���FIFO��ȡ1������, ֻ��ȡ�����ݲŷ��� */
	uint8_t ucData;

	while(comGetChar(COM1, &ucData) == 0);

	return ucData;
#else
	/* �ȴ����յ����� */
	while((USART1->SR & USART_SR_RXNE) == 0)
	{}

	return (int)USART1->DR;
#endif
}











