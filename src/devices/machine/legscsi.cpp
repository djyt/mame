// license:BSD-3-Clause
// copyright-holders:smf
#include "legscsi.h"

legacy_scsi_host_adapter::legacy_scsi_host_adapter(const machine_config &mconfig, device_type type, std::string name, std::string tag, device_t *owner, UINT32 clock, std::string shortname, std::string source) :
	device_t(mconfig, type, name, tag, owner, clock, shortname, source),
	m_selected(0),
	m_scsi_port(*this)
{
}

void legacy_scsi_host_adapter::device_start()
{
}

void legacy_scsi_host_adapter::reset_bus()
{
	for (int i = 0; i <= 7; i++)
	{
		scsihle_device *scsidev = get_device(i);
		if (scsidev != nullptr)
		{
			scsidev->reset();
		}
	}
}

bool legacy_scsi_host_adapter::select(int id)
{
	m_selected = id;

	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		return true;
	}

	return false;
}

void legacy_scsi_host_adapter::send_command(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		scsidev->SetCommand(data, bytes);
		scsidev->ExecCommand();
	}
	else
	{
		logerror("%s: send_command unknown SCSI id %d\n", tag().c_str(), m_selected);
	}
}

int legacy_scsi_host_adapter::get_length(void)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		int length;
		scsidev->GetLength(&length);
		return length;
	}
	else
	{
		logerror("%s: get_length unknown SCSI id %d\n", tag().c_str(), m_selected);
		return 0;
	}
}

int legacy_scsi_host_adapter::get_phase(void)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		int phase;
		scsidev->GetPhase(&phase);
		return phase;
	}
	else
	{
		logerror("%s: get_phase unknown SCSI id %d\n", tag().c_str(), m_selected);
		return 0;
	}
}

void legacy_scsi_host_adapter::read_data(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		scsidev->ReadData(data, bytes);
	}
	else
	{
		logerror("%s: read_data unknown SCSI id %d\n", tag().c_str(), m_selected);
	}
}

void legacy_scsi_host_adapter::write_data(UINT8 *data, int bytes)
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		scsidev->WriteData(data, bytes);
	}
	else
	{
		logerror("%s: write_data unknown SCSI id %d\n", tag().c_str(), m_selected);
	}
}

UINT8 legacy_scsi_host_adapter::get_status()
{
	scsihle_device *scsidev = get_device(m_selected);
	if (scsidev != nullptr)
	{
		void *image;

		scsidev->GetDevice(&image);
		if (image != nullptr)
			return 0x00;

		return 0x02;
	}
	else
	{
		logerror("%s: get_status unknown SCSI id %d\n", tag().c_str(), m_selected);
		return 0;
	}
}

scsihle_device *legacy_scsi_host_adapter::get_device(int id)
{
	// steal scsi devices from bus
	for (device_t *device = m_scsi_port->first_subdevice(); device != nullptr; device = device->next())
	{
		SCSI_PORT_SLOT_device *slot = dynamic_cast<SCSI_PORT_SLOT_device *>(device);
		if (slot != nullptr)
		{
			scsihle_device *scsidev = dynamic_cast<scsihle_device *>(slot->dev());
			if (scsidev != nullptr)
			{
				if (scsidev->GetDeviceID() == id)
				{
					return scsidev;
				}
			}
		}
	}

	return nullptr;
}
