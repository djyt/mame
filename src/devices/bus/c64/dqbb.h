// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Brown Boxes Double Quick Brown Box emulation

**********************************************************************/

#pragma once

#ifndef __DQBB__
#define __DQBB__


#include "emu.h"
#include "exp.h"
#include "machine/nvram.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> c64_dqbb_cartridge_device

class c64_dqbb_cartridge_device : public device_t,
									public device_c64_expansion_card_interface,
									public device_nvram_interface
{
public:
	// construction/destruction
	c64_dqbb_cartridge_device(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_nvram_interface overrides
	virtual void nvram_default() override { }
	virtual void nvram_read(emu_file &file) override { if (m_nvram != nullptr) { file.read(m_nvram, m_nvram.bytes()); } }
	virtual void nvram_write(emu_file &file) override { if (m_nvram != nullptr) { file.write(m_nvram, m_nvram.bytes()); } }

	// device_c64_expansion_card_interface overrides
	virtual UINT8 c64_cd_r(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;
	virtual void c64_cd_w(address_space &space, offs_t offset, UINT8 data, int sphi2, int ba, int roml, int romh, int io1, int io2) override;

private:
	int m_cs;
	int m_we;
};


// device type definition
extern const device_type C64_DQBB;


#endif
