/*
 * qspi_flash.h
 *
 *  Created on: 21 февр. 2019 г.
 *      Author: klen
 */

#ifndef __QSPI_FLASH_H__
#define __QSPI_FLASH_H__

#include "flash/qspi/sst26.h"

template<const serial_interface_t serial_interface, const qspi_t::control_t::flash_memory_selection_t::enum_t chip, const uint8_t prescaler>
class storage_4k_sector_t: protected sst26_t<serial_interface, chip, prescaler>
{
	typedef sst26_t<serial_interface, chip, prescaler> intf;

public:

	bool initialized = false;

	inline storage_4k_sector_t()
	{
	}
	inline ~storage_4k_sector_t()
	{
	}
	static constexpr uint32_t sector_size = 4096;
	static constexpr uint32_t page_size = 256;
	static constexpr uint32_t page_per_sector = sector_size / page_size;

	size_t sector_count;

	inline bool status()
	{
		return initialized;
	}

	inline int8_t initialize()
	{
		if(!initialized)
		{
			intf::init(sector_count);
			initialized = true;
		}
		return USBD_OK;
	}

	inline int8_t read(uint8_t *buff, const uint32_t sector, const uint32_t count)
	{
		intf::read_memory_high_speed_word(sector * sector_size, count * sector_size, buff);
		return USBD_OK;
	}

	inline int8_t write(const uint8_t *src, const uint32_t sector, const uint32_t count)
	{
		uint8_t *buff = (uint8_t*) src;
		uint32_t address = sector * sector_size;
		for(uint32_t sector_index = 0;sector_index < count;sector_index++)
		{
			// очистка сектора 4k
			intf::erase_4k_memry_array(address);
			for(uint32_t i = 0;i < page_per_sector;i++)
			{
				intf::page_programm_word(address + i * page_size, 256, buff + i * page_size);
			}

			buff += sector_size;
			address += sector_size;
		}
		return USBD_OK;
	}

	inline void erase(const uint32_t sector, const uint32_t count = 1)
	{
		uint32_t address = sector * sector_size;
		for(uint32_t sector_index = 0;sector_index < count;sector_index++)
		{
			// очистка сектора 4k
			intf::erase_4k_memry_array(address);
			address += sector_size;
		}
	}

	inline void erase()
	{
		intf::erase();
	}

};

#endif /* __QSPI_FLASH_H__ */
