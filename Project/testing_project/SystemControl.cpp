#include "SystemControl.h"

std::expected<HardwareInterface*, SystemControl::Error> SystemControl::GetHardwareInterface(const int hardware_index)
{
	if (hardware_index < 0 or hardware_index >= m_hardware_connections.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_hardware_connections[hardware_index].get();
}

std::expected<VacuumInterface*, SystemControl::Error> SystemControl::GetVacuumInterface(const int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_vacuum_interface[vacuum_index];
}

std::expected<XRFInterface*, SystemControl::Error> SystemControl::GetXRFInterface(const int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index];
}

std::expected<FilterInterface*, SystemControl::Error> SystemControl::GetFilterInterface(const int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_filter_interface[filter_index];
}

std::expected<VacuumSensorInterface*, SystemControl::Error> SystemControl::GetVacuumSensorInterface(const int vacuum_sensor_index)
{
	if (vacuum_sensor_index < 0 or vacuum_sensor_index >= m_vacuum_sensor_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_vacuum_sensor_interface[vacuum_sensor_index];
}

std::expected<ChamberLightInterface*, SystemControl::Error> SystemControl::GetChamberLightInterface(const int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_chamber_light_interface[chamber_light_index];
}

std::expected<CeilingLaserInterface*, SystemControl::Error> SystemControl::GetCeilingLaserInterface(const int ceiling_laser_index)
{
	if (ceiling_laser_index < 0 or ceiling_laser_index >= m_ceiling_laser_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_ceiling_laser_interface[ceiling_laser_index];
}

std::expected<SpotLaserInterface*, SystemControl::Error>  SystemControl::GetSpotLaserInterface(const int spot_laser_index)
{
	if (spot_laser_index < 0 or spot_laser_index >= m_spot_laser_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_spot_laser_interface[spot_laser_index];
}

// std::expected<CameraInterface*, SystemControl::Error> SystemControl::GetCameraInterface(const int camera_index)
// {
// 	if (camera_index < 0 or camera_index >= m_camera_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

// 	return m_camera_interface[camera_index];
// }

std::expected<DistanceSensorInterface*, SystemControl::Error> SystemControl::GetDistanceSensorInterface(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

	return m_distance_sensor_interface[distance_sensor_index];
}

// std::expected<DPPInterface*, SystemControl::Error> SystemControl::GetDPPInterface(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(SystemControl::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index];
// }

StageControlInterface* SystemControl::GetStageControlInterface()
{
	return m_stage_control_interface.get();
}

HardwareInterface::Error SystemControl::Reconnect(int hardware_index)
{
	if (hardware_index < 0 or hardware_index >= m_hardware_connections.size()) { return HardwareInterface::Error::index_out_of_range; }

	return m_hardware_connections[hardware_index]->Reconnect();
}

int SystemControl::GetNumberOfHardwareElements()
{
	return m_hardware_connections.size();
}

VacuumInterface::Error SystemControl::SetVacuum(VacuumInterface::VacuumType vacuum_type, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	return m_vacuum_interface[vacuum_index]->SetVacuum(vacuum_type);
}

std::expected<VacuumInterface::VacuumType, VacuumInterface::Error> SystemControl::GetVacuum(int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return std::unexpected(VacuumInterface::Error::index_out_of_range); }

	return m_vacuum_interface[vacuum_index]->GetVacuum();
}

std::expected<BOOL, VacuumInterface::Error> SystemControl::IsVentValveOpen(int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return std::unexpected(VacuumInterface::Error::index_out_of_range); }

	return m_vacuum_interface[vacuum_index]->IsVentValveOpen();
}

VacuumInterface::Error SystemControl::SetVentValveOpen(BOOL open, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	return m_vacuum_interface[vacuum_index]->SetVentValveOpen(open);
}

std::expected<BOOL, VacuumInterface::Error> SystemControl::IsEvacValveOpen(int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return std::unexpected(VacuumInterface::Error::index_out_of_range); }

	return m_vacuum_interface[vacuum_index]->IsEvacValveOpen();
}

VacuumInterface::Error SystemControl::SetEvacValveOpen(BOOL open, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	return m_vacuum_interface[vacuum_index]->SetEvacValveOpen(open);
}

VacuumInterface::Error SystemControl::SetPump(BOOL enable, int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return VacuumInterface::Error::index_out_of_range; }

	return m_vacuum_interface[vacuum_index]->SetPump(enable);
}

std::expected<BOOL, VacuumInterface::Error> SystemControl::IsPumping(int vacuum_index)
{
	if (vacuum_index < 0 or vacuum_index >= m_vacuum_interface.size()) { return std::unexpected(VacuumInterface::Error::index_out_of_range); }

	return m_vacuum_interface[vacuum_index]->IsPumping();
}

std::expected<double, XRFInterface::Error> SystemControl::GetkV(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetkV();
}

std::expected<double, XRFInterface::Error> SystemControl::GetTargetkV(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetTargetkV();
}

XRFInterface::Error SystemControl::SetkV(double new_kv, int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	return m_xrf_interface[xrf_index]->SetkV(new_kv);
}

std::expected<double, XRFInterface::Error> SystemControl::GetuA(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetuA();
}

std::expected<double, XRFInterface::Error> SystemControl::GetTargetuA(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetTargetuA();
}

XRFInterface::Error SystemControl::SetuA(double new_uA, int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	return m_xrf_interface[xrf_index]->SetuA(new_uA);
}

XRFInterface::Error SystemControl::EnableBeam(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	return m_xrf_interface[xrf_index]->EnableBeam();
}

XRFInterface::Error SystemControl::DisableBeam(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	return m_xrf_interface[xrf_index]->DisableBeam();
}

std::expected<BOOL, XRFInterface::Error> SystemControl::IsBeamEmittingXrays(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->IsBeamEmittingXrays();
}

std::expected<BOOL, XRFInterface::Error> SystemControl::HasShutter(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->HasShutter();
}

std::expected<BOOL, XRFInterface::Error> SystemControl::IsShutterOpen(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->IsShutterOpen();
}

XRFInterface::Error SystemControl::SetShutter(BOOL open, int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return XRFInterface::Error::index_out_of_range; }

	return m_xrf_interface[xrf_index]->SetShutter(open);
}

std::expected<double, XRFInterface::Error> SystemControl::GetMaxkV(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetMaxkV();
}

std::expected<double, XRFInterface::Error> SystemControl::GetMinkV(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetMinkV();
}

std::expected<double, XRFInterface::Error> SystemControl::GetMaxuA(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetMaxuA();
}

std::expected<double, XRFInterface::Error> SystemControl::GetMinuA(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetMinuA();
}

std::expected<double, XRFInterface::Error> SystemControl::GetMaxWatts(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetMaxWatts();
}

std::expected<double, XRFInterface::Error> SystemControl::GetWattAdjustedMaxuA(int xrf_index)
{
	if (xrf_index < 0 or xrf_index >= m_xrf_interface.size()) { return std::unexpected(XRFInterface::Error::index_out_of_range); }

	return m_xrf_interface[xrf_index]->GetWattAdjustedMaxuA();
}

FilterInterface::Error SystemControl::SetFilter(const int filter_position, int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return FilterInterface::Error::index_out_of_range; }

	return m_filter_interface[filter_index]->SetFilter(filter_position);
}

std::expected<int, FilterInterface::Error> SystemControl::GetFilter(int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return std::unexpected(FilterInterface::Error::index_out_of_range); }

	return m_filter_interface[filter_index]->GetFilter();
}

std::expected<int, FilterInterface::Error> SystemControl::GetNumberOfFilters(int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return std::unexpected(FilterInterface::Error::index_out_of_range); }

	return m_filter_interface[filter_index]->GetNumberOfFilters();
}

std::expected<int, FilterInterface::Error> SystemControl::FindIndexOfFilter(std::string name, int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return std::unexpected(FilterInterface::Error::index_out_of_range); }

	auto filter_count = g_system_controller->GetNumberOfFilters(filter_index);
	if (!filter_count.has_value()) { return std::unexpected(filter_count.error()); }

	for (int index = 0; index < filter_count.value(); index++)
	{
		auto filter_stat = g_system_controller->GetFilterStats(index, filter_index);
		if (!filter_stat.has_value()) { return std::unexpected(filter_stat.error()); }

		if (filter_stat.value().label == name) { return index; }
		if (filter_stat.value().name == name) { return index; }
	}

	return std::unexpected(FilterInterface::Error::generic_error);
}

std::expected<FilterInterface::FilterStats, FilterInterface::Error> SystemControl::GetFilterStats(int filter_position, int filter_index)
{
	if (filter_index < 0 or filter_index >= m_filter_interface.size()) { return std::unexpected(FilterInterface::Error::index_out_of_range); }

	return m_filter_interface[filter_index]->GetFilterStats(filter_position);
}

std::expected<double, VacuumSensorInterface::Error> SystemControl::GetATM(int vacuum_sensor_index)
{
	if (vacuum_sensor_index < 0 or vacuum_sensor_index >= m_vacuum_sensor_interface.size()) { return std::unexpected(VacuumSensorInterface::Error::index_out_of_range); }

	return m_vacuum_sensor_interface[vacuum_sensor_index]->GetATM();
}

ChamberLightInterface::Error SystemControl::SetChamberLightBrightness(int brightness, int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return ChamberLightInterface::Error::index_out_of_range; }

	return m_chamber_light_interface[chamber_light_index]->SetChamberLightBrightness(brightness);
}

std::expected<int, ChamberLightInterface::Error> SystemControl::GetChamberLightBrightness(int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return std::unexpected(ChamberLightInterface::Error::index_out_of_range); }

	return m_chamber_light_interface[chamber_light_index]->GetChamberLightBrightness();
}

std::expected<int, ChamberLightInterface::Error> SystemControl::GetChamberLightMaxBrightness(const int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return std::unexpected(ChamberLightInterface::Error::index_out_of_range); }

	return m_chamber_light_interface[chamber_light_index]->GetChamberLightMaxBrightness();
}

ChamberLightInterface::Error SystemControl::SetChamberLightColor(ChamberLightInterface::LightColor color, int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return ChamberLightInterface::Error::index_out_of_range; }

	return m_chamber_light_interface[chamber_light_index]->SetChamberLightColor(color);
}

std::expected<ChamberLightInterface::LightColor, ChamberLightInterface::Error> SystemControl::GetChamberLightColor(int chamber_light_index)
{
	if (chamber_light_index < 0 or chamber_light_index >= m_chamber_light_interface.size()) { return std::unexpected(ChamberLightInterface::Error::index_out_of_range); }

	return m_chamber_light_interface[chamber_light_index]->GetChamberLightColor();
}

CeilingLaserInterface::Error SystemControl::SetCeilingLaser(BOOL enable, int ceiling_laser_index)
{
	if (ceiling_laser_index < 0 or ceiling_laser_index >= m_ceiling_laser_interface.size()) { return CeilingLaserInterface::Error::index_out_of_range; }

	return m_ceiling_laser_interface[ceiling_laser_index]->SetCeilingLaser(enable);
}

std::expected<BOOL, CeilingLaserInterface::Error> SystemControl::GetCeilingLaserEnabled(int ceiling_laser_index)
{
	if (ceiling_laser_index < 0 or ceiling_laser_index >= m_ceiling_laser_interface.size()) { return std::unexpected(CeilingLaserInterface::Error::index_out_of_range); }

	return m_ceiling_laser_interface[ceiling_laser_index]->GetCeilingLaserEnabled();
}

std::expected<CeilingLaserInterface::CeilingLaserState, CeilingLaserInterface::Error> SystemControl::GetCeilingLaserState(int ceiling_laser_index)
{
	if (ceiling_laser_index < 0 or ceiling_laser_index >= m_ceiling_laser_interface.size()) { return std::unexpected(CeilingLaserInterface::Error::index_out_of_range); }

	return m_ceiling_laser_interface[ceiling_laser_index]->GetCeilingLaserState();
}

SpotLaserInterface::Error SystemControl::SetSpotLaser(BOOL enable, int spot_laser_interface_index)
{
	if (spot_laser_interface_index < 0 or spot_laser_interface_index >= m_spot_laser_interface.size()) { return SpotLaserInterface::Error::index_out_of_range; }

	return m_spot_laser_interface[spot_laser_interface_index]->SetSpotLaser(enable);
}

std::expected<BOOL, SpotLaserInterface::Error> SystemControl::GetSpotLaserEnabled(int spot_laser_interface_index)
{
	if (spot_laser_interface_index < 0 or spot_laser_interface_index >= m_spot_laser_interface.size()) { return std::unexpected(SpotLaserInterface::Error::index_out_of_range); }

	return m_spot_laser_interface[spot_laser_interface_index]->GetSpotLaserEnabled();
}

// std::expected<int, SystemControl::Error> SystemControl::FindCameraFromDeviceIndex(const int device_index)
// {
// 	for (int index = 0; index < static_cast<int>(m_camera_interface.size()); index++)
// 	{
// 		if (m_camera_interface[index]->GetDeviceIndex() == device_index) { return index; }
// 	}
// 	return std::unexpected(SystemControl::Error::generic_error);
// }

// int SystemControl::GetNumberOfCameras()
// {
// 	return m_camera_interface.size();
// }

std::expected<millimeters, DistanceSensorInterface::Error> SystemControl::GetDistance(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return std::unexpected(DistanceSensorInterface::Error::index_out_of_range); }

	return m_distance_sensor_interface[distance_sensor_index]->GetDistance();
}

DistanceSensorInterface::Error SystemControl::StartDistanceStream(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return DistanceSensorInterface::Error::index_out_of_range; }

	return m_distance_sensor_interface[distance_sensor_index]->StartDistanceStream();
}

std::expected<BOOL, DistanceSensorInterface::Error> SystemControl::IsDistanceStreamRunning(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return std::unexpected(DistanceSensorInterface::Error::index_out_of_range); }

	return m_distance_sensor_interface[distance_sensor_index]->IsDistanceStreamRunning();
}

DistanceSensorInterface::Error SystemControl::StopDistanceStream(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return DistanceSensorInterface::Error::index_out_of_range; }

	return m_distance_sensor_interface[distance_sensor_index]->StopDistanceStream();
}

DistanceSensorInterface::Error SystemControl::ResetSensor(const int distance_sensor_index)
{
	if (distance_sensor_index < 0 or distance_sensor_index >= m_distance_sensor_interface.size()) { return DistanceSensorInterface::Error::index_out_of_range; }

	return m_distance_sensor_interface[distance_sensor_index]->ResetSensor();
}

std::vector<std::recursive_timed_mutex*> SystemControl::GetStageControlLockingList(const std::optional<BOOL> include_x_stage, const std::optional<BOOL> include_y_stage, const std::optional<BOOL> include_z_stage)
{
	return m_stage_control_interface->GetStageControlLockingList(include_x_stage, include_y_stage, include_z_stage);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStagePosition(const std::optional<millimeters> x_stage_position, const std::optional<millimeters> y_stage_position, const std::optional<millimeters> z_stage_position)
{
	return m_stage_control_interface->SetStagePosition(x_stage_position, y_stage_position, z_stage_position);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStageSlewSpeed(const std::optional<millimeters> x_slew_speed, const std::optional<millimeters> y_slew_speed, const std::optional<millimeters> z_slew_speed)
{
	return m_stage_control_interface->SetStageSlewSpeed(x_slew_speed, y_slew_speed, z_slew_speed);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStageToHome(const std::optional<BOOL> home_x_stage, const std::optional<BOOL> home_y_stage, const std::optional<BOOL> home_z_stage)
{
	return m_stage_control_interface->SetStageToHome(home_x_stage, home_y_stage, home_z_stage);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStageToStop(const std::optional<BOOL> stop_x_stage, const std::optional<BOOL> stop_y_stage, const std::optional<BOOL> stop_z_stage)
{
	return m_stage_control_interface->SetStageToStop(stop_x_stage, stop_y_stage, stop_z_stage);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStageTrigger(const std::optional<DPPTriggerParameters> x_setup_parameters, const std::optional<DPPTriggerParameters> y_setup_parameters, const std::optional<DPPTriggerParameters> z_setup_parameters)
{
	return m_stage_control_interface->SetStageTrigger(x_setup_parameters, y_setup_parameters, z_setup_parameters);
}

StageValueReturn<StageControlInterface::Error> SystemControl::SetStageExternalControl(const std::optional<BOOL> enable_external_x_control, const std::optional<BOOL> enable_external_y_control, const std::optional<BOOL> enable_external_z_control)
{
	return m_stage_control_interface->SetStageExternalControl(enable_external_x_control, enable_external_y_control, enable_external_z_control);
}

StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> SystemControl::GetMovingStages(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	return m_stage_control_interface->GetMovingStages(check_x_stage, check_y_stage, check_z_stage);
}

StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> SystemControl::GetStagesLimits(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	return m_stage_control_interface->GetStagesLimits(check_x_stage, check_y_stage, check_z_stage);
}

StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> SystemControl::GetStagesPosition(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	return m_stage_control_interface->GetStagesPosition(check_x_stage, check_y_stage, check_z_stage);
}

StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> SystemControl::GetStagesSlewSpeed(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage)
{
	return m_stage_control_interface->GetStagesSlewSpeed(check_x_stage, check_y_stage, check_z_stage);
}

StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> SystemControl::GetStageParameterOverhead(const std::optional<millimeters> x_stage_final_speed, const std::optional<millimeters> y_stage_final_speed, const std::optional<millimeters> z_stage_final_speed)
{
	return m_stage_control_interface->GetStageParameterOverhead(x_stage_final_speed, y_stage_final_speed, z_stage_final_speed);
}

// std::expected<std::vector<DPP::DppReadout>, DPPInterface::Error> SystemControl::GetDppCustomReadouts(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetDppCustomReadouts();
// }

// std::expected<std::vector<DPP::DppReadout>, DPPInterface::Error> SystemControl::GetDppSymbols(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetDppSymbols();
// }

// DPPInterface::Error SystemControl::SetDppSymbols(DPP::DppReadout symbol_to_set, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetDppSymbols(symbol_to_set);
// }

// std::expected<std::array<double, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetAllDetectorsDeadtime(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetAllDetectorsDeadtime();
// }

// std::expected<std::array<LONGLONG, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetAllDetectorsCPS(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetAllDetectorsCPS();
// }

// std::expected<std::array<seconds, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetAllDetectorsRealTime(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetAllDetectorsRealTime();
// }

// std::expected<std::array<seconds, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetAllDetectorsLiveTime(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetAllDetectorsLiveTime();
// }

// DPPInterface::Error SystemControl::GetLiveSpectrum(DPP::PixelData& spectra, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->GetLiveSpectrum(spectra);
// }

// DPPInterface::Error SystemControl::SetEnergyCalibration(const int detector, const double TC, const DPP::EnergyCalibration energy_calibration, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetEnergyCalibration(detector, TC, energy_calibration);
// }

// std::expected<DPP::EnergyCalibration, DPPInterface::Error> SystemControl::GetEnergyCalibration(const int detector, const double TC, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetEnergyCalibration(detector, TC);
// }

// DPPInterface::Error SystemControl::SetPolyEnergyCal(const int detector, const double TC, DPP::CPolyCal polyCal, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetPolyEnergyCal(detector, TC, polyCal);
// }

// std::expected<DPP::CPolyCal, DPPInterface::Error> SystemControl::GetPolyEnergyCal(const int detector, const double TC, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetPolyEnergyCal(detector, TC);
// }

// std::expected<double, DPPInterface::Error> SystemControl::GetCurrentTC(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetCurrentTC();
// }

// DPPInterface::Error SystemControl::SetTC(const double new_TC, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetTC(new_TC);
// }

// DPPInterface::Error SystemControl::PrepareForFastMapScan(const DPP::SetupMapSettings settings, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->PrepareForFastMapScan(settings);
// }

// DPPInterface::Error SystemControl::PrepareForLineScan(const DPP::SetupLineScanSettings settings, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->PrepareForLineScan(settings);
// }

// DPPInterface::Error SystemControl::PrepareForSpectrum(const DPP::SetupSpectrumSettings settings, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->PrepareForSpectrum(settings);
// }

// DPPInterface::Error SystemControl::AcquireLine(const DPP::DppLineSettings settings, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->AcquireLine(settings);
// }

// DPPInterface::Error SystemControl::AcquireSpectrum(const DPP::DppSpectrumSettings settings, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->AcquireSpectrum(settings);
// }

// DPPInterface::Error SystemControl::EndAcquisitionSequence(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->EndAcquisitionSequence();
// }

// std::expected<DPP::acquisition_mode, DPPInterface::Error> SystemControl::GetCurrentAcquisitionMode(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetCurrentAcquisitionMode();
// }

// DPPInterface::Error SystemControl::SetCurrentDetectors(const std::array<BOOL, MAX_DETECTOR_COUNT> used_detectors, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetCurrentDetectors(used_detectors);
// }

// std::expected<std::array<BOOL, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetCurrentDetectors(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetCurrentDetectors();
// }

// DPPInterface::Error SystemControl::SetAvailableDetectors(const std::array<BOOL, MAX_DETECTOR_COUNT> available_detectors, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->SetAvailableDetectors(available_detectors);
// }

// std::expected<std::array<BOOL, MAX_DETECTOR_COUNT>, DPPInterface::Error> SystemControl::GetAvailableDetectors(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetAvailableDetectors();
// }

// DPPInterface::Error SystemControl::StopAcquisition(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	return m_dpp_interface[dpp_index]->StopAcquisition();
// }

// std::expected<double, DPPInterface::Error> SystemControl::GeteVPerChannel(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GeteVPerChannel();
// }

// std::expected<seconds, DPPInterface::Error> SystemControl::GetMaxDwell(const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return std::unexpected(DPPInterface::Error::index_out_of_range); }

// 	return m_dpp_interface[dpp_index]->GetMaxDwell();
// }

// DPPInterface::Error SystemControl::SubscribeToData(DPP::PixelDataQueue* queue, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	m_dpp_interface[dpp_index]->SubscribeToData(queue);
// }

// DPPInterface::Error SystemControl::UnSubscribeToData(DPP::PixelDataQueue* queue, const int dpp_index)
// {
// 	if (dpp_index < 0 or dpp_index >= m_dpp_interface.size()) { return DPPInterface::Error::index_out_of_range; }

// 	m_dpp_interface[dpp_index]->UnSubscribeToData(queue);
// }

namespace Hardware
{
// 	HardwareInterface::Error GenericInitializeCameras(std::vector<std::unique_ptr<HardwareInterface>>& hardware_connections, std::vector<CameraInterface*>& camera_interface)
// 	{
// 		CStringArray names;
// 		int numCameras = ListCameras(names);

// 		int dinoIndex = 0;

// #ifdef _WIN64
// 		BOOL OpenCVOnly = g_cfg.GetBOOL(CAMERA_SECTION, L"OpenCV Only", FALSE);
// #else
// 		BOOL OpenCVOnly = g_cfg.GetBOOL(CAMERA_SECTION, L"OpenCV Only", TRUE);
// #endif

// 		for (int deviceIndex = 0; deviceIndex < numCameras; deviceIndex++)
// 		{
// 			if (-1 == names[deviceIndex].Find(L"Dino") or OpenCVOnly)
// 			{
// 				hardware_connections.push_back(std::make_unique<COpenCVVideo>(deviceIndex));
// 				camera_interface.push_back(static_cast<COpenCVVideo*>(hardware_connections.back().get()));
// 			}
// 			else
// 			{
// #ifdef _WIN64
// 				hardware_connections.push_back(std::make_unique<COpenCVDinoCam>(deviceIndex, dinoIndex));
// 				camera_interface.push_back(static_cast<COpenCVDinoCam*>(hardware_connections.back().get()));
// #else
// 				hardware_connections.push_back(std::make_unique<CDinoCam32bitVideo>(deviceIndex, dinoIndex));
// 				camera_interface.push_back(static_cast<CDinoCam32bitVideo*>(hardware_connections.back().get()));
// #endif
// 				dinoIndex++;
// 			}
// 		}

// 		return HardwareInterface::Error::no_error;
// 	}

// 	//has GUI elements
// 	HardwareInterface::Error EnsureDinocamLightState(BOOL enabled)
// 	{
// 		if (!g_cfg.GetInt(XMAP_SECTION, L"LightElementAcquire", BST_UNCHECKED) or g_cfg.GetInt(XMAP_SECTION, L"DontEnsureLightState", TRUE)) { return HardwareInterface::Error::no_error; }
// 		CStringArray names;
// 		int numCameras = ListCameras(names);
// 		int numberOfDinocams = 0;
// 		int previousDinoCamIndex = 0;
// 		for (int deviceIndex = 0; deviceIndex < numCameras; deviceIndex++)
// 		{
// 			if (-1 != names[deviceIndex].Find(L"Dino"))
// 			{
// 				if (previousDinoCamIndex and ((previousDinoCamIndex + 1) != deviceIndex))
// 				{
// 					//LogError(L"Dino Cameras are not on adjacent indexs, this can cause issues. Returning early from ensure dinolight light state call");
// 					return HardwareInterface::Error::generic_error;
// 				}

// 				previousDinoCamIndex = deviceIndex;
// 				numberOfDinocams++;
// 			}
// 		}

// 		CIXRFProgressDlg progressBar(L"Setting Camera Settings", L"...This will take a bit", FALSE);
// 		progressBar.SetRange(numberOfDinocams, 1);
// 		progressBar.Show(AfxGetMainWnd());

// 		CVideo dinoCamera;

// 		for (int index = 0; index < numberOfDinocams; index++)
// 		{
// 			dinoCamera.Create(nullptr, L"", WS_CHILD, CRect(0, 0, 100, 100), AfxGetMainWnd(), IDC_IMAGE);
// 			dinoCamera.SetVideoDeviceIndex(index);

// 			int fps = 1;
// 			dinoCamera.SetCaptureRate(fps);

// 			dinoCamera.SetConnected(TRUE);

// 			dinoCamera.SetPreviewScale(true);
// 			dinoCamera.SetPreview(TRUE);

// 			dinoCamera.LightOn(enabled);
// 			dinoCamera.SetPreview(FALSE);
// 			dinoCamera.SetConnected(FALSE);
// 			dinoCamera.DestroyWindow();

// 			ResponseLoop();//this is needed to ensure that the destroywindow call can be processed and that the stepit call does not slow this function down
// 			progressBar.StepIt();
// 		}

// 		return HardwareInterface::Error::no_error;
// 	}

// 	StageControlInterface::Error DriveStageTo(millimeters mmTargetX, millimeters mmTargetY, std::atomic<BOOL>& abort)
// 	{
// 		int loopCount = 0;
// 		while (loopCount < 7 and !abort)
// 		{
// 			auto set_stage_return = g_system_controller->SetStagePosition(mmTargetX, mmTargetY, {});
// 			if (set_stage_return.m_x_value != StageControlInterface::Error::no_error or set_stage_return.m_y_value != StageControlInterface::Error::no_error)
// 			{
// 				//LogError(L"Failed to set stage position, aborting drive stage to");
// 				return StageControlInterface::Error::generic_error;
// 			}

// 			milliseconds current_time = std::chrono::system_clock::now().time_since_epoch();
// 			milliseconds last_time_stage_had_no_errors = current_time;

// 			auto isStageMoving = g_system_controller->GetMovingStages(TRUE, TRUE, {});
// 			while (current_time - last_time_stage_had_no_errors < seconds(30) and !abort)
// 			{
// 				std::this_thread::sleep_for(milliseconds(50));

// 				isStageMoving = g_system_controller->GetMovingStages(TRUE, TRUE, {});
// 				current_time = std::chrono::system_clock::now().time_since_epoch();
// 				if (isStageMoving.m_x_value.has_value() and isStageMoving.m_y_value.has_value())
// 				{
// 					last_time_stage_had_no_errors = current_time;

// 					//if both stages are done moving break out of while loop
// 					if (!isStageMoving.m_x_value.value() and !isStageMoving.m_y_value.value()) { break; }
// 				}
// 			}

// 			if (!isStageMoving.m_x_value.has_value() or !isStageMoving.m_y_value.has_value())
// 			{
// 				LogWarning(db::s::map, db::l::highest, "Stages have been in error for " + std::to_string(seconds(current_time - last_time_stage_had_no_errors).count())
// 					+ " seconds, iteration " + std::to_string(loopCount));
// 			}

// 			double const mmMaxTolerance = g_cfg.GetFloat(MAP_SECTION, L"Slew tolerance mm", 0.015f);
// 			auto stage_position = g_system_controller->GetStagesPosition(TRUE, TRUE, {});
// 			if (!stage_position.m_x_value.has_value() or !stage_position.m_y_value.has_value())
// 			{
// 				//LogError(L"Failed to get stage position, aborting");
// 				return StageControlInterface::Error::generic_error;
// 			}
// 			else if ((std::abs((stage_position.m_x_value.value() - mmTargetX).count()) <= mmMaxTolerance) and std::abs(((stage_position.m_y_value.value() - mmTargetY).count()) <= mmMaxTolerance)) { return StageControlInterface::Error::no_error; }

// 			//if we failed to get to the position we need to wait a bit before trying again
// 			std::this_thread::sleep_for(seconds(loopCount));
// 			loopCount++;
// 		}

// 		return StageControlInterface::Error::generic_error;
// 	}

// 	IXRF_SYSTEMINTERFACE_PROC StageControlInterface::Error EnsureStagesStoped(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage, milliseconds wait_until, std::atomic<BOOL>& abort)
// 	{
// 		BOOL stage_is_moving = TRUE;
// 		milliseconds current_time = std::chrono::system_clock::now().time_since_epoch();
// 		milliseconds start_time = current_time;

// 		while (stage_is_moving)
// 		{
// 			stage_is_moving = FALSE;
// 			auto stage_return = g_system_controller->GetMovingStages(check_x_stage, check_y_stage, check_z_stage);
// 			if (check_x_stage.has_value())
// 			{
// 				if (stage_return.m_x_value.has_value())
// 				{
// 					if (stage_return.m_x_value.value()) { stage_is_moving = TRUE; }
// 				}
// 				else
// 				{
// 					//assume the stage is moving if we can't check
// 					stage_is_moving = TRUE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if X stage is moving");
// 				}
// 			}
// 			if (check_y_stage.has_value())
// 			{
// 				if (stage_return.m_y_value.has_value())
// 				{
// 					if (stage_return.m_y_value.value()) { stage_is_moving = TRUE; }
// 				}
// 				else
// 				{
// 					//assume the stage is moving if we can't check
// 					stage_is_moving = TRUE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if Y stage is moving");
// 				}
// 			}
// 			if (check_z_stage.has_value())
// 			{
// 				if (stage_return.m_z_value.has_value())
// 				{
// 					if (stage_return.m_z_value.value()) { stage_is_moving = TRUE; }
// 				}
// 				else
// 				{
// 					//assume the stage is moving if we can't check
// 					stage_is_moving = TRUE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if Z stage is moving");
// 				}
// 			}

// 			current_time = std::chrono::system_clock::now().time_since_epoch();
// 			if (current_time - start_time > wait_until or abort)
// 			{
// 				//LogError(L"Ensure stage stopped timed out");
// 				return StageControlInterface::Error::generic_error;
// 			}

// 			std::this_thread::sleep_for(std::chrono::milliseconds(50));
// 		}

// 		return StageControlInterface::Error::no_error;
// 	}

// 	IXRF_SYSTEMINTERFACE_PROC StageControlInterface::Error EnsureStagesMoving(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage, milliseconds wait_until, std::atomic<BOOL>& abort)
// 	{
// 		BOOL stage_is_moving = FALSE;
// 		milliseconds current_time = std::chrono::system_clock::now().time_since_epoch();
// 		milliseconds start_time = current_time;

// 		while (!stage_is_moving)
// 		{
// 			stage_is_moving = TRUE;
// 			auto stage_return = g_system_controller->GetMovingStages(check_x_stage, check_y_stage, check_z_stage);
// 			if (check_x_stage.has_value())
// 			{
// 				if (stage_return.m_x_value.has_value())
// 				{
// 					if (!stage_return.m_x_value.value()) { stage_is_moving = FALSE; }
// 				}
// 				else
// 				{
// 					//assume the stage is not moving if we can't check
// 					stage_is_moving = FALSE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if X stage is moving");
// 				}
// 			}
// 			if (check_y_stage.has_value())
// 			{
// 				if (stage_return.m_y_value.has_value())
// 				{
// 					if (!stage_return.m_y_value.value()) { stage_is_moving = FALSE; }
// 				}
// 				else
// 				{
// 					//assume the stage is not moving if we can't check
// 					stage_is_moving = FALSE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if Y stage is moving");
// 				}
// 			}
// 			if (check_z_stage.has_value())
// 			{
// 				if (stage_return.m_z_value.has_value())
// 				{
// 					if (!stage_return.m_z_value.value()) { stage_is_moving = FALSE; }
// 				}
// 				else
// 				{
// 					//assume the stage is not moving if we can't check
// 					stage_is_moving = FALSE;
// 					LogWarning(db::s::stage, db::l::highest, L"Failed to check if Z stage is moving");
// 				}
// 			}

// 			current_time = std::chrono::system_clock::now().time_since_epoch();
// 			if (current_time - start_time > wait_until or abort)
// 			{
// 				//LogError(L"Ensure stage stopped timed out");
// 				return StageControlInterface::Error::generic_error;
// 			}

// 			std::this_thread::sleep_for(std::chrono::milliseconds(50));
// 		}

// 		return StageControlInterface::Error::no_error;
// 	}

// 	IXRF_SYSTEMINTERFACE_PROC HardwareInterface::Error ResponsiveSetSystemParameters(SetParameters parameters, std::atomic<BOOL>& abort)
// 	{
// 		CIXRFProgressDlg wait_dialog(L"Setting System Parameters", L"Please wait while the system obtains the requested parameters", TRUE);
// 		wait_dialog.SetRange(2, 1);
// 		wait_dialog.Show(AfxGetMainWnd());

// 		//go through and set the parameters given
// 		if (parameters.m_xrf_index.has_value())
// 		{
// 			if(parameters.m_set_kv.has_value())
// 			{
// 				if (g_system_controller->SetkV(parameters.m_set_kv.value(), parameters.m_xrf_index.value()) != XRFInterface::Error::no_error)
// 				{
// 					//LogError(L"Failed to set kV");
// 					return HardwareInterface::Error::generic_error;
// 				}
// 			}
// 			if (parameters.m_set_ua.has_value())
// 			{
// 				if (g_system_controller->SetuA(parameters.m_set_ua.value(), parameters.m_xrf_index.value()) != XRFInterface::Error::no_error)
// 				{
// 					//LogError(L"Failed to set uA");
// 					return HardwareInterface::Error::generic_error;
// 				}
// 			}
// 		}

// 		if (parameters.m_filter_index.has_value() and parameters.m_filter_position.has_value())
// 		{
// 			if (g_system_controller->SetFilter(parameters.m_filter_position.value(), parameters.m_filter_index.value()) != FilterInterface::Error::no_error)
// 			{
// 				//LogError(L"Failed to set filter position");
// 				return HardwareInterface::Error::generic_error;
// 			}
// 		}
		
// 		wait_dialog.StepIt(FALSE);
// 		//wait for the parameters to reach their target values
// 		BOOL waiting_for_parameter = TRUE;
// 		while (waiting_for_parameter and !abort and !wait_dialog.IsCancelled())
// 		{
// 			waiting_for_parameter = FALSE;

// 			if (parameters.m_xrf_index.has_value())
// 			{
// 				if (parameters.m_set_kv.has_value())
// 				{
// 					auto kv_return = g_system_controller->GetkV(parameters.m_xrf_index.value());
// 					if (!kv_return.has_value())
// 					{
// 						//LogError(L"Failed to get kV");
// 						return HardwareInterface::Error::generic_error;
// 					}

// 					if (std::abs(kv_return.value() - parameters.m_set_kv.value()) > 5) { waiting_for_parameter = TRUE; }
// 				}
// 				if (parameters.m_set_ua.has_value())
// 				{
// 					auto ua_return = g_system_controller->GetuA(parameters.m_xrf_index.value());
// 					if (!ua_return.has_value())
// 					{
// 						//LogError(L"Failed to get uA");
// 						return HardwareInterface::Error::generic_error;
// 					}

// 					if (std::abs(ua_return.value() - parameters.m_set_ua.value()) > 2) { waiting_for_parameter = TRUE; }
// 				}
// 			}

// 			if (parameters.m_filter_index.has_value() and parameters.m_filter_position.has_value())
// 			{
// 				auto filter_return = g_system_controller->GetFilter(parameters.m_filter_index.value());
// 				if (!filter_return.has_value())
// 				{
// 					if (filter_return.error() == FilterInterface::Error::moving) { waiting_for_parameter = TRUE; }
// 					else
// 					{
// 						//LogError(L"Failed to get filter position");
// 						return HardwareInterface::Error::generic_error;
// 					}
// 				}
// 				else
// 				{
// 					if(filter_return.value() != parameters.m_filter_position) { waiting_for_parameter = TRUE; }
// 				}
// 			}

// 			ResponseLoop();
// 		}

// 		if(abort or wait_dialog.IsCancelled()) { return HardwareInterface::Error::generic_error; }

// 		return HardwareInterface::Error::no_error;
// 	}
}