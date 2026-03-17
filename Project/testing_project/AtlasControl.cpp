#include "AtlasControl.h"
//#include "../XRFController/ATLASXRFControl.h"
//#include "../Stages/ThorStage.h"
//#include "../XRFController/Moxtek Usb.h"
//#include "ATLASStageController.h"
#include "VirtualHardwareElement.h"
//#include "LCDController.h"
//#include <HardwareInter.hxx>
//#include "../HardwareInter/C500iDeprecationContainer.h"
//#include "../HardwareInter/ModelDante.h"
//#include "../HardwareInter/ModelKetek.h"
//#include "../HardwareInter/VirtualDPP.h"

SystemControl::Error AtlasControl::SetupAsVIRTUAL()
{
	m_stage_control_interface = std::make_unique<VirtualATLASHardwareElement>();
	m_hardware_connections.push_back(std::make_unique<VirtualATLASHardwareElement>());

	//xrf controller
	m_xrf_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));
	m_filter_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));

	//vacuum controller
	m_vacuum_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));
	m_vacuum_sensor_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));
	m_chamber_light_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));
	m_ceiling_laser_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));
	m_spot_laser_interface.push_back(static_cast<VirtualATLASHardwareElement*>(m_hardware_connections.back().get()));

	return SystemControl::Error::no_error;
}

SystemControl::Error AtlasControl::SetupAsATLAS()
{
	// //stage control
	// m_stage_control_interface = std::make_unique<ATLASStageController>();

	// //xrf controller
	// m_hardware_connections.push_back(std::make_unique<ATLASXRFControl>());
	// m_xrf_interface.push_back(static_cast<ATLASXRFControl*>(m_hardware_connections.back().get()));
	// m_filter_interface.push_back(static_cast<ATLASXRFControl*>(m_hardware_connections.back().get()));

	// //vacuum controller
	// m_hardware_connections.push_back(std::make_unique<CAtlasVacuum>());
	// m_vacuum_interface.push_back(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// m_vacuum_sensor_interface.push_back(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// m_chamber_light_interface.push_back(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// m_ceiling_laser_interface.push_back(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// m_spot_laser_interface.push_back(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_z_stage = static_cast<CAtlasVacuum*>(m_hardware_connections.back().get());

	// //secondary system
	// if (g_cfg.GetBOOL(VACUUM_SECTION, L"Fx Available", FALSE, TRUE))
	// {
	// 	SystemControl::Error rule_return = SetupSecondarySystem(static_cast<CAtlasVacuum*>(m_hardware_connections.back().get()));
	// 	if (rule_return != SystemControl::Error::no_error)
	// 	{
	// 		//LogError(L"The system has failed a rule and is unable to connect to hardware");
	// 		return rule_return;
	// 	}
	// }

	// //stages
	// m_hardware_connections.push_back(std::make_unique<CThorStage>());
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_x_stage = static_cast<CThorStage*>(m_hardware_connections.back().get());
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_y_stage = static_cast<CThorStage*>(m_hardware_connections.back().get());

	return SystemControl::Error::no_error;
}

SystemControl::Error AtlasControl::SetupAsAPEX()
{
	// //stage control
	// m_stage_control_interface = std::make_unique<ATLASStageController>();

	// //xrf controller
	// m_hardware_connections.push_back(std::make_unique<CLCDController>());//LCD panel needs to be the first hardware object
	// m_filter_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// m_xrf_interface.push_back(&static_cast<CLCDController*>(m_hardware_connections.back().get())->m_primary_beam);

	// //secondary system
	// if (g_cfg.GetBOOL(VACUUM_SECTION, L"Fx Available", FALSE, TRUE))
	// {
	// 	m_xrf_interface.push_back(&static_cast<CLCDController*>(m_hardware_connections.back().get())->m_secondary_beam);
	// }

	// //vacuum controller
	// m_vacuum_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// m_vacuum_sensor_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// m_chamber_light_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// m_ceiling_laser_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// m_spot_laser_interface.push_back(static_cast<CLCDController*>(m_hardware_connections.back().get()));
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_z_stage = static_cast<CLCDController*>(m_hardware_connections.back().get());

	// //stages
	// m_hardware_connections.push_back(std::make_unique<CThorStage>());
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_x_stage = static_cast<CThorStage*>(m_hardware_connections.back().get());
	// static_cast<ATLASStageController*>(m_stage_control_interface.get())->m_y_stage = static_cast<CThorStage*>(m_hardware_connections.back().get());

	return SystemControl::Error::no_error;
}

SystemControl::Error AtlasControl::SetupDPP()
{
	// CString str;
	// g_cfg.GetString(CONFIG_SECTION, L"Electronics", MERC_550I, str, TRUE);
	// LogInfo(db::s::dpp, db::l::highest, L"Attempting to initialize '%s' electronics", (LPCTSTR)str);

	// if (g_cfg.IsVirtual())
	// {
	// 	m_hardware_connections.push_back(std::make_unique<VirtualDPP>());
	// 	m_dpp_interface.push_back(static_cast<VirtualDPP*>(m_hardware_connections.back().get()));
		
	// 	return SystemControl::Error::no_error;
	// }

	// if (str.CompareNoCase(SATURN_550I) == 0)
	// {
	// 	m_hardware_connections.push_back(std::make_unique<Model550iDeprecationContainer>("Saturn"));
	// 	m_dpp_interface.push_back(static_cast<Model550iDeprecationContainer*>(m_hardware_connections.back().get()));
		
	// }
	// else if ((str.CompareNoCase(L"550m") == 0)
	// 	|| (str.CompareNoCase(MERC_550I) == 0)
	// 	|| (str.CompareNoCase(MERC_D_550I) == 0))
	// {
	// 	m_hardware_connections.push_back(std::make_unique<Model550iDeprecationContainer>("Mercury"));
	// 	m_dpp_interface.push_back(static_cast<Model550iDeprecationContainer*>(m_hardware_connections.back().get()));
	// }
	// else if (str.CompareNoCase(L"Ketek") == 0)
	// {
	// 	m_hardware_connections.push_back(std::make_unique<CModelKetek>());
	// 	m_dpp_interface.push_back(static_cast<CModelKetek*>(m_hardware_connections.back().get()));
	// }
	// else if (str.CompareNoCase(DANTE) == 0 || str.CompareNoCase(DANTE_4572) == 0)
	// {
	// 	m_hardware_connections.push_back(std::make_unique<CModelDante>());
	// 	m_dpp_interface.push_back(static_cast<CModelDante*>(m_hardware_connections.back().get()));
	// }
	// else if ((str.CompareNoCase(L"Digital") == 0) || (str.CompareNoCase(L"7000") == 0)
	// 	|| (str.CompareNoCase(L"8000") == 0) || (str.CompareNoCase(L"Canberra") == 0)
	// 	|| (str.CompareNoCase(L"Rontec") == 0) || (str.CompareNoCase(L"Imaging") == 0)
	// 	|| (str.CompareNoCase(L"Fake") == 0) || (str.CompareNoCase(L"TxBRT") == 0)
	// 	|| (str.CompareNoCase(L"IXRFDP4") == 0) || str.CompareNoCase(MERC_4) == 0
	// 	|| str.CompareNoCase(AMPTEK) == 0 || str.CompareNoCase(XMAP) == 0
	// 	|| str.CompareNoCase(L"Handel") == 0)
	// {
	// 	//Deprecated electronics
	// 	ErrorMessage(IDS_UNKNOWN_ELEC, std::source_location::current(), (LPCTSTR)str);
	// 	return SystemControl::Error::not_supported;
	// }

	return SystemControl::Error::no_error;
}

void AtlasControl::APEXUpdateThread()
{
	// SetThreadDescription(GetCurrentThread(), L"APEX Current Beam Update Thread");

	// while (m_run_update_thread)
	// {
	// 	std::this_thread::sleep_for(seconds(1));
	// 	if (static_cast<CLCDController*>(m_hardware_connections[0].get())->PrimaryActive()) { m_in_use_beam = 0; }
	// 	else if (static_cast<CLCDController*>(m_hardware_connections[0].get())->SecondaryActive()) { m_in_use_beam = 1; }
	// }
}

SystemControl::Error AtlasControl::InitializeSystem()
{
	//m_has_primary_beam = g_cfg.GetBOOL(XRF_CTRL_SECTION, _T("Primary Available"), TRUE, TRUE);
	if (TRUE)//g_cfg.IsVirtual()) 
	{ 
		auto setup_return = SetupAsVIRTUAL(); 
		if (setup_return != SystemControl::Error::no_error) { return setup_return; }
	}
	// else if (g_cfg.GetBOOL(CONFIG_SECTION, _T("AtlasApex"), FALSE, TRUE))
	// {
	// 	auto setup_return = SetupAsAPEX();
	// 	if (setup_return != SystemControl::Error::no_error) { return setup_return; }
	// }
	// else
	// {
	// 	auto setup_return = SetupAsATLAS();
	// 	if (setup_return != SystemControl::Error::no_error) { return setup_return; }
	// }

	// auto setup_dpp_return = SetupDPP();
	// if (setup_dpp_return != SystemControl::Error::no_error) { return setup_dpp_return; }

	//connect to all the hardware
	BOOL issues_connecting = FALSE;
	for (auto& hardware : m_hardware_connections) 
	{ 
		if (hardware->Connect() != HardwareInterface::Error::no_error)
		{
			////LogError("Failed to connect to " + hardware->m_id);
			issues_connecting = TRUE;
		}
	}

	//cameras
	// if (Hardware::GenericInitializeCameras(m_hardware_connections, m_camera_interface) != HardwareInterface::Error::no_error)
	// {
	// 	////LogError(L"The system ran into issue connecting to the cameras");
	// 	issues_connecting = TRUE;
	// }

	if (issues_connecting) { return SystemControl::Error::generic_error; }

	// if (g_cfg.GetBOOL(CONFIG_SECTION, _T("AtlasApex"), FALSE, TRUE))
	// {
	// 	//start an update thread to update the active beam
	// 	m_run_update_thread = TRUE;
	// 	m_APEX_update_thread = std::thread(&AtlasControl::APEXUpdateThread, this);
	// }

	return SystemControl::Error::no_error;
}

SystemControl::Error AtlasControl::DeInitializeSystem()
{
	for (auto& hardware : m_hardware_connections) { hardware->Disconnect(); }

	return SystemControl::Error::no_error;
}

VacuumInterface::Error AtlasControl::SetVacuum(VacuumInterface::VacuumType vacuum_type, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	std::vector<std::recursive_timed_mutex*> needed_locks;
	needed_locks = m_stage_control_interface->GetStageControlLockingList({}, {}, TRUE);
	needed_locks.push_back(m_vacuum_interface[vacuum_index]->GetInterfaceObjectLock());
	HardwareMultiLockGuard lock(needed_locks);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	if (!CheckZStageIsNearHome()) { return VacuumInterface::Error::failed_rule; }

	return m_vacuum_interface[vacuum_index]->SetVacuum(vacuum_type);
}

VacuumInterface::Error AtlasControl::SetVentValveOpen(BOOL open, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	std::vector<std::recursive_timed_mutex*> needed_locks;
	needed_locks = m_stage_control_interface->GetStageControlLockingList({}, {}, TRUE);
	needed_locks.push_back(m_vacuum_interface[vacuum_index]->GetInterfaceObjectLock());
	HardwareMultiLockGuard lock(needed_locks);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	if (!CheckZStageIsNearHome()) { return VacuumInterface::Error::failed_rule; }

	return m_vacuum_interface[vacuum_index]->SetVentValveOpen(open);
}

VacuumInterface::Error AtlasControl::SetEvacValveOpen(BOOL open, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	std::vector<std::recursive_timed_mutex*> needed_locks;
	needed_locks = m_stage_control_interface->GetStageControlLockingList({}, {}, TRUE);
	needed_locks.push_back(m_vacuum_interface[vacuum_index]->GetInterfaceObjectLock());
	HardwareMultiLockGuard lock(needed_locks);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	if (!CheckZStageIsNearHome()) { return VacuumInterface::Error::failed_rule; }

	return m_vacuum_interface[vacuum_index]->SetEvacValveOpen(open);
}

XRFInterface::Error AtlasControl::EnableBeam(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	std::vector<std::recursive_timed_mutex*> needed_locks;
	for (int index = 0; index < m_xrf_interface.size(); index++) { needed_locks.push_back(m_xrf_interface[index]->GetInterfaceObjectLock()); }
	HardwareMultiLockGuard lock(needed_locks);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	XRFInterface::Error rule_return = EnforceOnlyOneBeamOn(xrf_index);
	if (rule_return != XRFInterface::Error::no_error) { return rule_return; }

	m_in_use_beam = xrf_index;

	return m_xrf_interface[xrf_index]->EnableBeam();
}

XRFInterface::Error AtlasControl::SetShutter(BOOL open, int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	std::vector<std::recursive_timed_mutex*> beam_locks;
	for (int index = 0; index < m_xrf_interface.size(); index++) { beam_locks.push_back(m_xrf_interface[index]->GetInterfaceObjectLock()); }
	HardwareMultiLockGuard lock(beam_locks);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	if (open)
	{
		XRFInterface::Error rule_return = EnforceOnlyOneBeamOn(xrf_index);
		if (rule_return != XRFInterface::Error::no_error) { return rule_return; }

		m_xrf_interface[xrf_index]->SetShutter(TRUE);
	}
	else
	{
		m_xrf_interface[xrf_index]->SetShutter(FALSE);
	}

	return XRFInterface::Error::no_error;
}

XRFInterface::Error AtlasControl::EnforceOnlyOneBeamOn(int xrf_index)
{
	for (int index = 0; index < m_xrf_interface.size(); index++)
	{
		if (index == xrf_index) { continue; }

		auto has_shutter = m_xrf_interface[index]->HasShutter();
		if (!has_shutter.has_value()) { return XRFInterface::Error::failed_rule; }

		if (!has_shutter.value())
		{
			XRFInterface::Error beam_off_return = m_xrf_interface[index]->DisableBeam();
			if (beam_off_return != XRFInterface::Error::no_error) { return XRFInterface::Error::failed_rule; }
		}
		else
		{
			auto shutter_close_return = m_xrf_interface[index]->SetShutter(FALSE);
			auto low_kv = m_xrf_interface[index]->GetMinkV();
			auto low_ua = m_xrf_interface[index]->GetMinuA();
			if (!low_kv.has_value() or !low_ua.has_value()) { return XRFInterface::Error::failed_rule; }

			auto set_kv_return = m_xrf_interface[index]->SetkV(low_kv.value());
			auto set_ua_return = m_xrf_interface[index]->SetuA(low_ua.value());

			if (shutter_close_return != XRFInterface::Error::no_error or set_kv_return != XRFInterface::Error::no_error or set_ua_return != XRFInterface::Error::no_error)
			{
				return XRFInterface::Error::failed_rule;
			}
		}
	}

	return XRFInterface::Error::no_error;
}

BOOL AtlasControl::CheckZStageIsNearHome()
{
	auto z_stage_positions = GetStagesPosition({}, {}, TRUE).m_z_value.value();
	if (z_stage_positions > millimeters(.01))
	{
		return FALSE;
	}

	return TRUE;
}

// SystemControl::Error AtlasControl::SetupSecondarySystem(CAtlasVacuum* vacuum_controller)
// {
// 	if (g_cfg.GetBOOL(XRF_CTRL_SECTION, _T("Moxtek 2nd"), FALSE, TRUE))
// 	{
// 		m_hardware_connections.push_back(std::make_unique<CMoxtekUsb>());
// 		m_xrf_interface.push_back(static_cast<CMoxtekUsb*>(m_hardware_connections.back().get()));
// 	}
// 	else
// 	{
// 		m_xrf_interface.push_back(vacuum_controller);
// 	}
// 	m_has_secondary_beam = TRUE;

// 	return SystemControl::Error::no_error;
// }

int AtlasControl::GetInUseBeam()
{
	return m_in_use_beam;
}

BOOL AtlasControl::HasPrimary()
{
	return m_has_primary_beam;
}

BOOL AtlasControl::HasSecondary()
{
	return m_has_secondary_beam;
}

BOOL AtlasControl::HasDistanceSensor()
{
	return m_has_distance_sensor;
}

// millimeters AtlasControl::GetSecondaryOffset(SECONDARYOFFSET idx, CString szSpotSize)
// {
// 	CString key;
// 	for (unsigned int i = 0; i < g_cfg.GetInt(XRF_CTRL_SECTION, _T("SecondaryOffsetCount"), 0); i++)
// 	{
// 		key.Format(_T("SecondaryOffset %d"), i);
// 		CStringArray fields;
// 		g_cfg.GetStringArray(XRF_CTRL_SECTION, key, _T(""), fields);
// 		size_t const fieldCount = fields.GetCount();
// 		if ((fieldCount == NUM_FIELDS) && (fields[SPOTSIZE] == szSpotSize))
// 		{
// 			return millimeters(std::stof(fields[idx].GetBuffer()));
// 		}
// 	}

// 	return millimeters(0);
// }