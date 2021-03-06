// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Wang PC-PM043 Multiport Communications Controller emulation

**********************************************************************/

#pragma once

#ifndef __WANGPC_MCC__
#define __WANGPC_MCC__

#include "emu.h"
#include "wangpc.h"
#include "machine/z80dart.h"



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> wangpc_mcc_device

class wangpc_mcc_device : public device_t,
							public device_wangpcbus_card_interface
{
public:
	// construction/destruction
	wangpc_mcc_device(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const override;

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// device_wangpcbus_card_interface overrides
	virtual UINT16 wangpcbus_iorc_r(address_space &space, offs_t offset, UINT16 mem_mask) override;
	virtual void wangpcbus_aiowc_w(address_space &space, offs_t offset, UINT16 mem_mask, UINT16 data) override;

private:
	inline void set_irq(int state);

	required_device<z80dart_device> m_sio;
	required_device<z80dart_device> m_dart;

	UINT8 m_option;
	int m_irq;
};


// device type definition
extern const device_type WANGPC_MCC;


#endif
