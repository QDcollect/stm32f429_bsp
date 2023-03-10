/*
*********************************************************************************************************
*	��Ҫ���ܣ�
*			ʵ��FMC��չSDRAM�ĳ�ʼ��
*	ʹ��������
*			1����Ҫ��main.h���� #include "bsp_fmc_sdram.h"
*			2����Ҫ���������е���		SDRAM_Initialization(); ͬʱ����MX_FMC_Init();
*			3�������Ӧ�ĳ�ʼ������
*				��MX�Զ����ɵĲ�ͬ�����ŷֱ��ǣ�GPIOH ֮�е�PIN_2|3|5
*	
*********************************************************************************************************
*/
#include "main.h"

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);


//ɾ��main�����MX_FMC_Init();
//hsdram1������һ�� ���� �˼Ұ���������
void SDRAM_Initialization(void)
{
		MX_FMC_Init();
		FMC_SDRAM_CommandTypeDef command = {0};
		SDRAM_Initialization_Sequence(&hsdram1, &command);//�����������þ��Ƕ����COMMAND���в�����Ŷ�������������
}

/*
*********************************************************************************************************
*	�� �� ��: SDRAM��ʼ������
*	����˵��: ���SDRAM���г�ʼ��
*	��    ��: hsdram: SDRAM���
*			  Command: ����ṹ��ָ��
*	�� �� ֵ: None
*********************************************************************************************************
*/
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
	__IO uint32_t tmpmrd =0;
 
    /*##-1- ʱ��ʹ������ ##################################################*/
	Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	/* �������� */
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /*##-2- �����ӳ٣�����100us ##################################################*/
	HAL_Delay(1);

    /*##-3- ����SDRAMԤ������PALL(precharge all) #############################*/
	Command->CommandMode = FMC_SDRAM_CMD_PALL;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = 0;

	/* �������� */
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /*##-4- �Զ�ˢ������ #######################################################*/
	Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 8;
	Command->ModeRegisterDefinition = 0;

	/* �������� */
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /*##-5- ����SDRAMģʽ�Ĵ��� ###############################################*/
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_3           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command->AutoRefreshNumber = 1;
	Command->ModeRegisterDefinition = tmpmrd;

	/* �������� */
	HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

    /*##-6- ������ˢ���� ####################################################*/
    /*
        SDRAM refresh period / Number of rows��*SDRAMʱ���ٶ� �C 20
      = 64ms / 4096 *84MHz - 20
      = 1292.5 ȡֵ1293
    */
	HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT); 
}




/*
*********************************************************************************************************
*	�� �� ��: bsp_TestExtSDRAM
*	����˵��: ɨ������ⲿSDRAM��ȫ����Ԫ��
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ����ͨ���� ����0��ʾ����Ԫ�ĸ�����
*********************************************************************************************************
*/
uint32_t bsp_TestExtSDRAM1(void)
{
	uint32_t i;
	uint32_t *pSRAM;
	uint8_t *pBytes;
	uint32_t err;
	const uint8_t ByteBuf[4] = {0x55, 0xA5, 0x5A, 0xAA};

	/* дSRAM */
	pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
	{
		*pSRAM++ = i;
	}

	/* ��SRAM */
	err = 0;
	pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
	{
		if (*pSRAM++ != i)
		{
			err++;
		}
	}

	if (err >  0)
	{
		return  (4 * err);
	}

	/* ��SRAM �������󷴲�д�� */
	pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
	{
		*pSRAM = ~*pSRAM;
		pSRAM++;
	}

	/* �ٴαȽ�SDRAM������ */
	err = 0;
	pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < EXT_SDRAM_SIZE / 4; i++)
	{
		if (*pSRAM++ != (~i))
		{
			err++;
		}
	}

	if (err >  0)
	{
		return (4 * err);
	}

	/* ���԰��ֽڷ�ʽ����, Ŀ������֤ FSMC_NBL0 �� FSMC_NBL1 ���� */
	pBytes = (uint8_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < sizeof(ByteBuf); i++)
	{
		*pBytes++ = ByteBuf[i];
	}

	/* �Ƚ�SDRAM������ */
	err = 0;
	pBytes = (uint8_t *)EXT_SDRAM_ADDR;
	for (i = 0; i < sizeof(ByteBuf); i++)
	{
		if (*pBytes++ != ByteBuf[i])
		{
			err++;
		}
	}
	if (err >  0)
	{
		return err;
	}
	return 0;
}


/*
*********************************************************************************************************
*	�� �� ��: ReadWriteTest
*	����˵��: �����ݣ�����ӡ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ReadWriteTest(void)
{
	uint32_t i;
	uint32_t *pBuf;
	

	/* д���������0xAAAA5555 */
	pBuf = (uint32_t *)(EXT_SDRAM_ADDR + TEST_ADDRESS);
	for (i = 0; i < TEST_BUF_SIZE; i++)		
	{
		pBuf[i] = 0xAAAA5555;
	}
	
	printf("�����ַ��0x%08X  ��С: %d�ֽ�  ��ʾ: %d�ֽ�  ��������: \r\n", EXT_SDRAM_ADDR + TEST_ADDRESS, EXT_SDRAM_SIZE, TEST_BUF_SIZE*4);
	
	/* ��ӡ���� */
	pBuf = (uint32_t *)(EXT_SDRAM_ADDR + TEST_ADDRESS);
	for (i = 0; i < TEST_BUF_SIZE; i++)
	{
		printf(" %04X", pBuf[i]);

		if ((i & 7) == 7)
		{
			printf("\r\n");		/* ÿ����ʾ32�ֽ����� */
		}
		else if ((i & 7) == 3)
		{
			printf(" - ");
		}
	}
}
