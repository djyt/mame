// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
#ifndef __ASTROCADE_ROM_H
#define __ASTROCADE_ROM_H

#include "slot.h"


// ======================> astrocade_rom_device

class astrocade_rom_device : public device_t,
						public device_astrocade_cart_interface
{
public:
	// construction/destruction
	astrocade_rom_device(const machine_config &mconfig, device_type type, std::string name, std::string tag, device_t *owner, UINT32 clock, std::string shortname, std::string source);
	astrocade_rom_device(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start() override {}
	virtual void device_reset() override {}

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;
};

// ======================> astrocade_rom_256k_device

class astrocade_rom_256k_device : public astrocade_rom_device
{
public:
	// construction/destruction
	astrocade_rom_256k_device(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

private:
	UINT8 m_base_bank;
};

// ======================> astrocade_rom_512k_device

class astrocade_rom_512k_device : public astrocade_rom_device
{
public:
	// construction/destruction
	astrocade_rom_512k_device(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);

	virtual void device_start() override;
	virtual void device_reset() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_rom) override;

private:
	UINT8 m_base_bank;
};





// device type definition
extern const device_type ASTROCADE_ROM_STD;
extern const device_type ASTROCADE_ROM_256K;
extern const device_type ASTROCADE_ROM_512K;


#endif
