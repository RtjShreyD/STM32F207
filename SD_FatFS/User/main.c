/*********************************************************************************************************
*
* File                : main.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "sdcard.h"
#include "usart.h"
#include "string.h"
#include "diskio.h"
#include "ff.h"




/* Private functions ---------------------------------------------------------*/
FATFS fs;            // Work area (file system object) for logical drive
FIL fsrc, fdst;      // file objects
BYTE buffer[512]; // file copy buffer
FRESULT res;         // FatFs function common result code
UINT br, bw;         // File R/W count

#if _USE_LFN
char Fs_LongFileName[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
#endif
/*******************************************************************************
* Function Name  : NVIC_Config
* Description    : Configures SDIO IRQ channel.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);
}

//20141130
/*------------------------------------------------------------/
/ Open or create a file in append mode
/------------------------------------------------------------*/

FRESULT open_append (
    FIL* fp,            /* [OUT] File object to create */
    const char* path    /* [IN]  File name to be opened */
)
{
    FRESULT fr;

    /* Opens an existing file. If not exist, creates a new file. */
    fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
    if (fr == FR_OK) {
        /* Seek to end of the file to append data */
        fr = f_lseek(fp, f_size(fp));
        if (fr != FR_OK)
            f_close(fp);
    }
    return fr;
}
//20141130




 
void OutPutFile(void)
{ 
	unsigned int a;
	FRESULT res;
	FILINFO finfo;
	DIR dirs;
	char path[]={"This file is Log.\r\n"};  

    //20141130
    FRESULT fr;
    FATFS fs;
    FIL fil;
	DWORD size;
	//unsigned char Mday=0, Mon=0, Year=0, Hour=0, Min=0;
/*	
#if _USE_LFN
    finfo.lfname = Fs_LongFileName;
    finfo.lfsize = sizeof(Fs_LongFileName);
#endif

	printf(" 磁盘初始化:%d\r\n",disk_initialize(0));
	printf("挂载磁盘:%d\r\n",f_mount(0, &fs));

	if (f_opendir(&dirs, path) == FR_OK) 
	{
    	while (f_readdir(&dirs, &finfo) == FR_OK)  
    	{
      		if (finfo.fattrib & AM_ARC) 
      		{
        		if(!finfo.fname[0]) break;        
        		printf("短文件名:%s\r\n",finfo.fname);
#if _USE_LFN
        		printf("长文件名:%s\r\n",finfo.lfname);
#endif
        		res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
        		br=1;
				a=0;
				printf("文件头255字节内容:");
					for(a=0; a<512; a++) buffer[a]=0; 
		    	    res = f_read(&fsrc, buffer, sizeof(buffer), &br);
					printf("%s\r\n",buffer);	
		    	    if (res || br == 0) break;   // error or eof
				f_close(&fsrc);             
			}
		} 
	}

*/	
    /* Open or create a log file and ready to append */
	USART_SendData(USART1,0X0C); //CLEAR DISPLAY
	printf("Disk Initialize:%d\r\n",disk_initialize(0));
    f_mount(0,&fs);
    fr = open_append(&fil, "logfile.txt");
    if (fr != FR_OK) printf("logfile.txt Make err\r\n");
	else{printf("File Make Success\r\n");}
    /* Append a line */
   // if (EOF != f_printf(&fil, "%02u/%02u/%u, %2u:%02u\n", Mday, Mon, Year, Hour, Min))

	/*
	if (EOF != f_printf(&fil, "%d",128))
    	{printf("File Write Success\r\n");}
	else{printf("File Write Fail\r\n");}
    */
    size = (&fil)->fsize;
	fr= f_lseek(&fil,size);
    fr=f_write(&fil,&path,sizeof(path),&bw);	
 	printf("f_write Return : %d\r\n",fr);
//    fr= f_write(&fil,"\n",1,&bw);


	//
   // printf("f_sync Return :%d\r\n",f_sync(&fil));


    /* Close the file */
   fr= f_close(&fil);
	printf("f_close Return :%d\r\n",fr);


  
	while(1);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{    
  SystemInit();/* Clock Config */
  SystemCoreClockUpdate();
  
  NVIC_Configuration();/* Interrupt Config */

  USART_Configuration();  

  OutPutFile();
  
  /* Infinite loop */
  while (1)
  {}
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
