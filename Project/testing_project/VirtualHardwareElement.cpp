#include "VirtualHardwareElement.h"


//hardware interface
HardwareInterface::Error VirtualATLASHardwareElement::Connect()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return HardwareInterface::Error::generic_error; }

	return HardwareInterface::Error::no_error;
}

HardwareInterface::Error VirtualATLASHardwareElement::Disconnect()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return HardwareInterface::Error::generic_error; }

	return HardwareInterface::Error::no_error;
}

HardwareInterface::Error VirtualATLASHardwareElement::Reconnect()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return HardwareInterface::Error::generic_error; }

	return HardwareInterface::Error::no_error;
}

//vacuum interface
VacuumInterface::Error VirtualATLASHardwareElement::SetVacuum(const VacuumInterface::VacuumType vacuum_type)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

m_current_vacuum = vacuum_type;

return VacuumInterface::Error::no_error;
}

std::expected<VacuumInterface::VacuumType, VacuumInterface::Error> VirtualATLASHardwareElement::GetVacuum()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(VacuumInterface::Error::generic_error); }

	return m_current_vacuum;
}

std::expected<BOOL, VacuumInterface::Error> VirtualATLASHardwareElement::IsVentValveOpen()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(VacuumInterface::Error::generic_error); }

	return m_vent_open;
}

VacuumInterface::Error VirtualATLASHardwareElement::SetVentValveOpen(const BOOL open)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	m_vent_open = open;

	return VacuumInterface::Error::no_error;
}

std::expected<BOOL, VacuumInterface::Error> VirtualATLASHardwareElement::IsEvacValveOpen()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(VacuumInterface::Error::generic_error); }

	return m_evac_open;
}

VacuumInterface::Error VirtualATLASHardwareElement::SetEvacValveOpen(const BOOL open)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	m_evac_open = open;

	return VacuumInterface::Error::no_error;
}

VacuumInterface::Error VirtualATLASHardwareElement::SetPump(const BOOL enable)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return VacuumInterface::Error::generic_error; }

	m_is_pumping = enable;

	return VacuumInterface::Error::no_error;
}

std::expected<BOOL, VacuumInterface::Error> VirtualATLASHardwareElement::IsPumping()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(VacuumInterface::Error::generic_error); }

	return m_is_pumping;
}

//xrf interface
std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetkV()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return m_set_kv;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetTargetkV()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return m_set_kv;
}

XRFInterface::Error VirtualATLASHardwareElement::SetkV(const double new_kv)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	auto max_kv = GetMaxkV();
	auto min_kv = GetMinkV();
	auto max_watt = GetMaxWatts();

	if (!min_kv.has_value() or !max_kv.has_value() or !max_watt.has_value()) { return XRFInterface::Error::generic_error; }
	if (new_kv < min_kv.value() or new_kv > max_kv.value()) { return XRFInterface::Error::failed_rule; }

	m_set_kv = new_kv;

	return XRFInterface::Error::no_error;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetuA()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return m_set_ua;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetTargetuA()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return m_set_ua;
}

XRFInterface::Error VirtualATLASHardwareElement::SetuA(const double new_uA)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	auto max_ua = GetWattAdjustedMaxuA();
	auto min_ua = GetMinuA();
	auto max_watt = GetMaxWatts();

	if (!max_ua.has_value() or !min_ua.has_value() or !max_watt.has_value()) { return XRFInterface::Error::generic_error; }
	if (new_uA < min_ua.value() or new_uA > max_ua.value()) { return XRFInterface::Error::failed_rule; }

	m_set_ua = new_uA;

	return XRFInterface::Error::no_error;
}

XRFInterface::Error VirtualATLASHardwareElement::EnableBeam()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

return XRFInterface::Error::no_error;
}

XRFInterface::Error VirtualATLASHardwareElement::DisableBeam()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	return XRFInterface::Error::no_error;
}

std::expected<BOOL, XRFInterface::Error> VirtualATLASHardwareElement::IsBeamEmittingXrays()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return TRUE;
}

std::expected<BOOL, XRFInterface::Error> VirtualATLASHardwareElement::HasShutter()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return TRUE;
}

std::expected<BOOL, XRFInterface::Error> VirtualATLASHardwareElement::IsShutterOpen()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return m_shutter;
}

XRFInterface::Error VirtualATLASHardwareElement::SetShutter(const BOOL open)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return XRFInterface::Error::generic_error; }

	m_shutter = open;

	return XRFInterface::Error::no_error;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetMaxkV()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 50;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetMinkV()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 10;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetMaxuA()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 1'000;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetMinuA()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 0;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetMaxWatts()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 15;
}

std::expected<double, XRFInterface::Error> VirtualATLASHardwareElement::GetWattAdjustedMaxuA()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(XRFInterface::Error::generic_error); }

	return 1'000;
}

//filter interface
FilterInterface::Error VirtualATLASHardwareElement::SetFilter(const int filter_position)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return FilterInterface::Error::generic_error; }

	m_filter = filter_position;

	return FilterInterface::Error::no_error;
}

std::expected<int, FilterInterface::Error> VirtualATLASHardwareElement::GetFilter()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(FilterInterface::Error::generic_error); }

	return m_filter;
}

std::expected<int, FilterInterface::Error> VirtualATLASHardwareElement::GetNumberOfFilters()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(FilterInterface::Error::generic_error); }

	return 9;
}

std::expected<FilterInterface::FilterStats, FilterInterface::Error> VirtualATLASHardwareElement::GetFilterStats(const int filter_position)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(FilterInterface::Error::generic_error); }

	FilterInterface::FilterStats filter_stat;
	filter_stat.description = "test";
	filter_stat.label = "blue";
	filter_stat.name = "AlCr";
	filter_stat.thickness = 10;

	return filter_stat;
}

//vacuum sensor interface
std::expected<double, VacuumSensorInterface::Error> VirtualATLASHardwareElement::GetATM()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(VacuumSensorInterface::Error::generic_error); }

	return 100;
}

//chamber light interface
ChamberLightInterface::Error VirtualATLASHardwareElement::SetChamberLightBrightness(const int brightness)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return ChamberLightInterface::Error::generic_error; }

	m_chamber_brightness = brightness;

	return ChamberLightInterface::Error::no_error;
}

std::expected<int, ChamberLightInterface::Error> VirtualATLASHardwareElement::GetChamberLightBrightness()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(ChamberLightInterface::Error::generic_error); }

	return m_chamber_brightness;
}

std::expected<int, ChamberLightInterface::Error> VirtualATLASHardwareElement::GetChamberLightMaxBrightness()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(ChamberLightInterface::Error::generic_error); }

	return 255;
}

ChamberLightInterface::Error VirtualATLASHardwareElement::SetChamberLightColor(const ChamberLightInterface::LightColor color)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return ChamberLightInterface::Error::generic_error; }

	return ChamberLightInterface::Error::no_error;
}

std::expected<ChamberLightInterface::LightColor, ChamberLightInterface::Error> VirtualATLASHardwareElement::GetChamberLightColor()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(ChamberLightInterface::Error::generic_error); }

	return std::unexpected(ChamberLightInterface::Error::not_supported);
}

//ceiling laser interface
CeilingLaserInterface::Error VirtualATLASHardwareElement::SetCeilingLaser(const BOOL enable)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return CeilingLaserInterface::Error::generic_error; }

	m_ceiling_laser = enable;

	return CeilingLaserInterface::Error::no_error;
}

std::expected<BOOL, CeilingLaserInterface::Error> VirtualATLASHardwareElement::GetCeilingLaserEnabled()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(CeilingLaserInterface::Error::generic_error); }

	return m_ceiling_laser;
}

std::expected<CeilingLaserInterface::CeilingLaserState, CeilingLaserInterface::Error> VirtualATLASHardwareElement::GetCeilingLaserState()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(CeilingLaserInterface::Error::generic_error); }

	return CeilingLaserInterface::CeilingLaserState::no_issue;
}

//spot laser interface
SpotLaserInterface::Error VirtualATLASHardwareElement::SetSpotLaser(const BOOL enable)
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return SpotLaserInterface::Error::generic_error; }

	m_spot_laser = enable;

	return SpotLaserInterface::Error::no_error;
}

std::expected<BOOL, SpotLaserInterface::Error> VirtualATLASHardwareElement::GetSpotLaserEnabled()
{
	HardwareLockGuard lock(m_hardware_lock);
	if (!lock.IsLocked()) { return std::unexpected(SpotLaserInterface::Error::generic_error); }

	return m_spot_laser;
}

std::vector<std::recursive_timed_mutex*> VirtualATLASHardwareElement::GetStageControlLockingList(const std::optional<BOOL> include_x_stage, const std::optional<BOOL> include_y_stage, const std::optional<BOOL> include_z_stage)
{
	return std::vector<std::recursive_timed_mutex*>();
}

//stage controller interface
StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStagePosition(const std::optional<millimeters> x_stage_position, const std::optional<millimeters> y_stage_position, const std::optional<millimeters> z_stage_position)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (x_stage_position.has_value())
	{
		m_x_position = x_stage_position.value();
		stage_return.m_x_value = StageControlInterface::Error::no_error;
	}
	if (y_stage_position.has_value())
	{
		m_y_position = y_stage_position.value();
		stage_return.m_y_value = StageControlInterface::Error::no_error;
	}
	if (z_stage_position.has_value())
	{
		if(z_stage_position.value() < millimeters(0)) { stage_return.m_z_value = StageControlInterface::Error::failed_rule; }
		else
		{ 
			m_z_position = z_stage_position.value();
			stage_return.m_z_value = StageControlInterface::Error::no_error;
		}
	}

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageSlewSpeed(const std::optional<millimeters> x_slew_speed, const std::optional<millimeters> y_slew_speed, const std::optional<millimeters> z_slew_speed)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (x_slew_speed.has_value())
	{
		m_x_slew = x_slew_speed.value();
		stage_return.m_x_value = StageControlInterface::Error::no_error;
	}
	if (y_slew_speed.has_value())
	{
		m_y_slew = y_slew_speed.value();
		stage_return.m_y_value = StageControlInterface::Error::no_error;
	}
	if (z_slew_speed.has_value())
	{
		m_z_slew = z_slew_speed.value();
		stage_return.m_z_value = StageControlInterface::Error::no_error;
	}

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageAcceleration(const std::optional<millimeters> x_acceleration, const std::optional<millimeters> y_acceleration, const std::optional<millimeters> z_acceleration)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (x_acceleration.has_value())
	{
		m_x_acceleration = x_acceleration.value();
		stage_return.m_x_value = StageControlInterface::Error::no_error;
	}
	if (y_acceleration.has_value())
	{
		m_y_acceleration = y_acceleration.value();
		stage_return.m_y_value = StageControlInterface::Error::no_error;
	}
	if (z_acceleration.has_value())
	{
		m_z_acceleration = z_acceleration.value();
		stage_return.m_z_value = StageControlInterface::Error::no_error;
	}

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageToHome(const std::optional<BOOL> home_x_stage, const std::optional<BOOL> home_y_stage, const std::optional<BOOL> home_z_stage)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (home_x_stage.has_value() and home_x_stage.value())
	{
		m_x_position = millimeters(50);
		stage_return.m_x_value = StageControlInterface::Error::no_error;
	}
	if (home_y_stage.has_value() and home_y_stage.value())
	{
		m_y_position = millimeters(50);
		stage_return.m_y_value = StageControlInterface::Error::no_error;
	}
	if (home_z_stage.has_value() and home_z_stage.value())
	{
		m_z_position = millimeters(0);;
		stage_return.m_z_value = StageControlInterface::Error::no_error;
	}

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageToStop(const std::optional<BOOL> stop_x_stage, const std::optional<BOOL> stop_y_stage, const std::optional<BOOL> stop_z_stage)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (stop_x_stage.has_value() and stop_x_stage.value()) { stage_return.m_x_value = StageControlInterface::Error::no_error; }
	if (stop_y_stage.has_value() and stop_y_stage.value()) { stage_return.m_y_value = StageControlInterface::Error::no_error; }
	if (stop_z_stage.has_value() and stop_z_stage.value()) { stage_return.m_z_value = StageControlInterface::Error::no_error; }

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageTrigger(const std::optional<DPPTriggerParameters> x_setup_parameters, const std::optional<DPPTriggerParameters> y_setup_parameters, const std::optional<DPPTriggerParameters> z_setup_parameters)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (x_setup_parameters.has_value()) { stage_return.m_x_value = StageControlInterface::Error::no_error; }
	if (y_setup_parameters.has_value()) { stage_return.m_y_value = StageControlInterface::Error::no_error; }
	if (z_setup_parameters.has_value()) { stage_return.m_z_value = StageControlInterface::Error::no_error; }

	return stage_return;
}

StageValueReturn<StageControlInterface::Error> VirtualATLASHardwareElement::SetStageExternalControl(const std::optional<BOOL> enable_external_x_control, const std::optional<BOOL> enable_external_y_control, const std::optional<BOOL> enable_external_z_control)
{
	StageValueReturn<StageControlInterface::Error> stage_return;
	if (enable_external_x_control.has_value()) { stage_return.m_x_value = StageControlInterface::Error::no_error; }
	if (enable_external_y_control.has_value()) { stage_return.m_y_value = StageControlInterface::Error::no_error; }
	if (enable_external_z_control.has_value()) { stage_return.m_z_value = StageControlInterface::Error::no_error; }

	return stage_return;
}

StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> VirtualATLASHardwareElement::GetMovingStages(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> stage_return;
	if (check_x_stage.has_value() and check_x_stage.value()) { stage_return.m_x_value = FALSE; }
	if (check_y_stage.has_value() and check_y_stage.value()) { stage_return.m_y_value = FALSE; }
	if (check_z_stage.has_value() and check_z_stage.value()) { stage_return.m_z_value = FALSE; }

	return stage_return;
}

StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> VirtualATLASHardwareElement::GetStagesLimits(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> stage_return;
	StageLimits limits;
	limits.m_min_stage_position = millimeters(0);
	limits.m_max_stage_position = millimeters(500);
	limits.m_max_stage_acceleration = millimeters(500);
	limits.m_min_stage_acceleration = millimeters(0);
	limits.m_max_stage_speed = millimeters(300);
	limits.m_min_stage_speed = millimeters(0);

	if (check_x_stage.has_value() and check_x_stage.value()) { stage_return.m_x_value = limits; }
	if (check_y_stage.has_value() and check_y_stage.value()) { stage_return.m_y_value = limits; }
	if (check_z_stage.has_value() and check_z_stage.value()) { stage_return.m_z_value = limits; }

	return stage_return;
}

StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> VirtualATLASHardwareElement::GetStagesPosition(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> stage_return;
	if (check_x_stage.has_value() and check_x_stage.value()) { stage_return.m_x_value = m_x_position; }
	if (check_y_stage.has_value() and check_y_stage.value()) { stage_return.m_y_value = m_y_position; }
	if (check_z_stage.has_value() and check_z_stage.value()) { stage_return.m_z_value = m_z_position; }

	return stage_return;
}

StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> VirtualATLASHardwareElement::GetStagesSlewSpeed(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> stage_return;
	if (check_x_stage.has_value() and check_x_stage.value()) { stage_return.m_x_value = m_x_slew; }
	if (check_y_stage.has_value() and check_y_stage.value()) { stage_return.m_y_value = m_y_slew; }
	if (check_z_stage.has_value() and check_z_stage.value()) { stage_return.m_z_value = m_z_slew; }

	return stage_return;
}

StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> VirtualATLASHardwareElement::GetStagesAcceleration(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> return_values;
	if (check_x_stage.has_value() and check_x_stage.value()) { return_values.m_x_value = m_x_acceleration; }
	if (check_y_stage.has_value() and check_y_stage.value()) { return_values.m_y_value = m_y_acceleration; }
	if (check_z_stage.has_value() and check_z_stage.value()) { return_values.m_z_value = m_z_acceleration; }

	return return_values;
}

StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> VirtualATLASHardwareElement::GetStageParameterOverhead(const std::optional<millimeters> x_stage_final_speed, const std::optional<millimeters> y_stage_final_speed, const std::optional<millimeters> z_stage_final_speed)
{
	StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> stage_return;

	return stage_return;
}