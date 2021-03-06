// license:BSD-3-Clause
// copyright-holders:S. Smith,David Haywood
#ifndef __NEOGEO_PCM2_CART_H
#define __NEOGEO_PCM2_CART_H

#include "neogeo_slot.h"
#include "banked_cart.h"
#include "pcm2_prot.h"
#include "cmc_prot.h"

// ======================> neogeo_pcm2_cart

class neogeo_pcm2_cart : public device_t,
						public device_neogeo_cart_interface
{
public:
	// construction/destruction
	neogeo_pcm2_cart(const machine_config &mconfig, device_type type, std::string name, std::string tag, device_t *owner, UINT16 clock, std::string shortname, std::string source);
	neogeo_pcm2_cart(const machine_config &mconfig, std::string tag, device_t *owner, UINT16 clock);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual machine_config_constructor device_mconfig_additions() const override;

	// reading and writing
	virtual DECLARE_READ16_MEMBER(read_rom) override;

	virtual void activate_cart(ACTIVATE_CART_PARAMS) override { m_banked_cart->install_banks(machine, maincpu, cpuregion, cpuregion_size); }
	virtual void decrypt_all(DECRYPT_ALL_PARAMS) override {}
	virtual int get_fixed_bank_type(void) override { return 0; }

	required_device<neogeo_banked_cart_device> m_banked_cart;
	required_device<cmc_prot_device> m_cmc_prot;
	required_device<pcm2_prot_device> m_pcm2_prot;
};



// device type definition
extern const device_type NEOGEO_PCM2_CART;


/*************************************************
 MSLUG4
**************************************************/

class neogeo_pcm2_mslug4_cart : public neogeo_pcm2_cart
{
public:
	neogeo_pcm2_mslug4_cart(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);
	virtual void decrypt_all(DECRYPT_ALL_PARAMS) override;
	virtual int get_fixed_bank_type(void) override { return 1; }
};
extern const device_type NEOGEO_PCM2_MSLUG4_CART;

class neogeo_pcm2_ms4plus_cart : public neogeo_pcm2_cart
{
public:
	neogeo_pcm2_ms4plus_cart(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);
	virtual void decrypt_all(DECRYPT_ALL_PARAMS) override;
	virtual int get_fixed_bank_type(void) override { return 0; }
};
extern const device_type NEOGEO_PCM2_MS4PLUS_CART;



/*************************************************
 ROTD
**************************************************/

class neogeo_pcm2_rotd_cart : public neogeo_pcm2_cart
{
public:
	neogeo_pcm2_rotd_cart(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);
	virtual void decrypt_all(DECRYPT_ALL_PARAMS) override;
	virtual int get_fixed_bank_type(void) override { return 1; }
};
extern const device_type NEOGEO_PCM2_ROTD_CART;


/*************************************************
 PNYAA
**************************************************/

class neogeo_pcm2_pnyaa_cart : public neogeo_pcm2_cart
{
public:
	neogeo_pcm2_pnyaa_cart(const machine_config &mconfig, std::string tag, device_t *owner, UINT32 clock);
	virtual void decrypt_all(DECRYPT_ALL_PARAMS) override;
	virtual int get_fixed_bank_type(void) override { return 1; }
};
extern const device_type NEOGEO_PCM2_PNYAA_CART;




#endif
