#include "flash_if.h"

#define ADDR_FLASH_SECTOR_0      ((uint32_t)0x08000000) /* Base address of Sector 0, 16 K bytes   */
#define ADDR_FLASH_SECTOR_1      ((uint32_t)0x08004000) /* Base address of Sector 1, 16 K bytes   */
#define ADDR_FLASH_SECTOR_2      ((uint32_t)0x08008000) /* Base address of Sector 2, 16 K bytes   */
#define ADDR_FLASH_SECTOR_3      ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 K bytes   */
#define ADDR_FLASH_SECTOR_4      ((uint32_t)0x08010000) /* Base address of Sector 4, 64 K bytes   */
#define ADDR_FLASH_SECTOR_5      ((uint32_t)0x08020000) /* Base address of Sector 5, 128 K bytes  */
#define ADDR_FLASH_SECTOR_6      ((uint32_t)0x08040000) /* Base address of Sector 6, 128 K bytes  */
#define ADDR_FLASH_SECTOR_7      ((uint32_t)0x08060000) /* Base address of Sector 7, 128 K bytes  */
#define ADDR_FLASH_SECTOR_8      ((uint32_t)0x08080000) /* Base address of Sector 8, 128 K bytes  */
#define ADDR_FLASH_SECTOR_9      ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 K bytes  */
#define ADDR_FLASH_SECTOR_10     ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 K bytes */
#define ADDR_FLASH_SECTOR_11     ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 K bytes */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base address of Sector 12, 16 K bytes  */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base address of Sector 13, 16 K bytes  */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base address of Sector 14, 16 K bytes  */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base address of Sector 15, 16 K bytes  */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base address of Sector 16, 64 K bytes  */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base address of Sector 17, 128 K bytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base address of Sector 18, 128 K bytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base address of Sector 19, 128 K bytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base address of Sector 20, 128 K bytes */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base address of Sector 21, 128 K bytes */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base address of Sector 22, 128 K bytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base address of Sector 23, 128 K bytes */

uint8_t flash_if_read(uint32_t addr, uint32_t *buf, uint32_t size) {
    uint8_t result = 0;
    uint8_t *buf_8 = (uint8_t *)buf;
    uint32_t i;

    /*copy from flash to ram */
    for (i = 0; i < size; i++, addr ++, buf_8++) {
        *buf_8 = *(uint8_t *) addr;
    }

    return result;
}

uint32_t FLASH_If_GetSectorNb(uint32_t Address)
{
	uint32_t SectorNb = 0xFFFFFFFF;
	
	if(Address >= ADDR_FLASH_SECTOR_0 && Address < ADDR_FLASH_SECTOR_1)
	{
		SectorNb = 0;
	}
	else if(Address >= ADDR_FLASH_SECTOR_1 && Address < ADDR_FLASH_SECTOR_2)
	{
		SectorNb = 1;
	}
	else if(Address >= ADDR_FLASH_SECTOR_2 && Address < ADDR_FLASH_SECTOR_3)
	{
		SectorNb = 2;
	}
	else if(Address >= ADDR_FLASH_SECTOR_3 && Address < ADDR_FLASH_SECTOR_4)
	{
		SectorNb = 3;
	}
	else if(Address >= ADDR_FLASH_SECTOR_4 && Address < ADDR_FLASH_SECTOR_5)
	{
		SectorNb = 4;
	}
	else if(Address >= ADDR_FLASH_SECTOR_5 && Address < ADDR_FLASH_SECTOR_6)
	{
		SectorNb = 5;
	}
	else if(Address >= ADDR_FLASH_SECTOR_6 && Address < ADDR_FLASH_SECTOR_7)
	{
		SectorNb = 6;
	}
	else if(Address >= ADDR_FLASH_SECTOR_7 && Address < ADDR_FLASH_SECTOR_8)
	{
		SectorNb = 7;
	}
	else if(Address >= ADDR_FLASH_SECTOR_8 && Address < ADDR_FLASH_SECTOR_9)
	{
		SectorNb = 8;
	}
	else if(Address >= ADDR_FLASH_SECTOR_9 && Address < ADDR_FLASH_SECTOR_10)
	{
		SectorNb = 9;
	}
	else if(Address >= ADDR_FLASH_SECTOR_10 && Address < ADDR_FLASH_SECTOR_11)
	{
		SectorNb = 10;
	}
	else if(Address >= ADDR_FLASH_SECTOR_11 && Address < ADDR_FLASH_SECTOR_12)
	{
		SectorNb = 11;
	}
	else if(Address >= ADDR_FLASH_SECTOR_12 && Address < ADDR_FLASH_SECTOR_13)
	{
		SectorNb = 12;
	}
	else if(Address >= ADDR_FLASH_SECTOR_13 && Address < ADDR_FLASH_SECTOR_14)
	{
		SectorNb = 13;
	}
	else if(Address >= ADDR_FLASH_SECTOR_14 && Address < ADDR_FLASH_SECTOR_15)
	{
		SectorNb = 14;
	}
	else if(Address >= ADDR_FLASH_SECTOR_15 && Address < ADDR_FLASH_SECTOR_16)
	{
		SectorNb = 15;
	}
	else if(Address >= ADDR_FLASH_SECTOR_16 && Address < ADDR_FLASH_SECTOR_17)
	{
		SectorNb = 16;
	}
	else if(Address >= ADDR_FLASH_SECTOR_17 && Address < ADDR_FLASH_SECTOR_18)
	{
		SectorNb = 17;
	}
	else if(Address >= ADDR_FLASH_SECTOR_18 && Address < ADDR_FLASH_SECTOR_19)
	{
		SectorNb = 18;
	}
	else if(Address >= ADDR_FLASH_SECTOR_19 && Address < ADDR_FLASH_SECTOR_20)
	{
		SectorNb = 19;
	}
	else if(Address >= ADDR_FLASH_SECTOR_20 && Address < ADDR_FLASH_SECTOR_21)
	{
		SectorNb = 20;
	}
	else if(Address >= ADDR_FLASH_SECTOR_21 && Address < ADDR_FLASH_SECTOR_22)
	{
		SectorNb = 21;
	}
	else if(Address >= ADDR_FLASH_SECTOR_22 && Address < ADDR_FLASH_SECTOR_23)
	{
		SectorNb = 22;
	}
	else if(Address >= ADDR_FLASH_SECTOR_23 && Address < 0x08200000)
	{
		SectorNb = 23;
	}
	else
	{
		SectorNb = 0xffffffff;
	}
	return SectorNb;
}

uint8_t flash_if_erase(uint32_t addr, uint32_t size) {
    uint8_t result = 0;
		uint32_t Erase_Error;
		HAL_StatusTypeDef status;
		uint32_t Start_SectorNb,End_SectorNb;
		FLASH_EraseInitTypeDef FLASH_Erase;
	
	
		//根据起始地址确定需要擦除的首扇区号
		Start_SectorNb = FLASH_If_GetSectorNb(addr);
		if(Start_SectorNb == 0xffffffff)
		{
			//地址错误
			return 1;
		}
		//当size=1时，addr仍然是addr,并没有加1
		End_SectorNb = FLASH_If_GetSectorNb(addr + size - 1);
		if(Start_SectorNb == 0xffffffff)
		{
			//地址错误
			return 1;
		}
		
		HAL_FLASH_Unlock();
		
		//从第二扇区开始即0x0800 8000开始，擦除8个扇区
		FLASH_Erase.NbSectors = (End_SectorNb - Start_SectorNb+1);
		FLASH_Erase.Sector = Start_SectorNb;
		FLASH_Erase.TypeErase = FLASH_TYPEERASE_SECTORS;
		FLASH_Erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	
		status = HAL_FLASHEx_Erase(&FLASH_Erase,&Erase_Error);
		
		HAL_FLASH_Lock();
	
    if(Erase_Error == 0xFFFFFFFF && status == HAL_OK)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}

    return result;
}

uint8_t flash_if_write(uint32_t addr, const uint32_t *buf, uint32_t size) 
{
        uint8_t result = 0;	
		uint32_t i = 0;
		uint32_t read_data;
		
		size /= 4;
	
		/* Unlock the Flash to enable the flash control register access *************/
		HAL_FLASH_Unlock();
		
		/* DataLength must be a multiple of 32 bit */
		for (i = 0; i<size; i++)
		{
			/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
				 be done by word */ 
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *(buf+i)) == HAL_OK)      
			{
			 /* Check the written value */
				read_data = *(uint32_t *) addr;
				
				if (read_data != *(uint32_t *)(buf+i))
				{
					/* Flash content doesn't match SRAM content */
					result = 1;
					break;
				}
				/* Increment FLASH destination address */
				addr += 4;
			}
			else
			{
				/* Error occurred while writing data in Flash memory */
				result = 1;
				break;
			}
		}

		/* Lock the Flash to disable the flash control register access (recommended
			 to protect the FLASH memory against possible unwanted operation) *********/
		HAL_FLASH_Lock();

    return result;
}


