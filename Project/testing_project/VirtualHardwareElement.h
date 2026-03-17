#pragma once
#include "HardwareInterface.h"
#include "VacuumInterface.h"
#include "XRFInterface.h"
#include "StageControl.h"


class  VirtualATLASHardwareElement :
	public HardwareInterface,
	public VacuumInterface,
	public XRFInterface,
	public FilterInterface,
	public VacuumSensorInterface,
	public ChamberLightInterface,
	public CeilingLaserInterface,
	public SpotLaserInterface,
	public StageControlInterface

{


protected:
	//hardware interface
	virtual HardwareInterface::Error Connect();
	virtual HardwareInterface::Error Disconnect();
	virtual HardwareInterface::Error Reconnect();

	//vacuum interface
	BOOL m_evac_open = FALSE;
	BOOL m_vent_open = FALSE;
	BOOL m_is_pumping = FALSE;
	VacuumInterface::VacuumType m_current_vacuum = VacuumInterface::VacuumType::Vented;

	virtual VacuumInterface::Error SetVacuum(const VacuumInterface::VacuumType vacuum_type);
	virtual std::expected<VacuumInterface::VacuumType, VacuumInterface::Error> GetVacuum();

	virtual std::expected<BOOL, VacuumInterface::Error> IsVentValveOpen();
	virtual VacuumInterface::Error SetVentValveOpen(const BOOL open);

	virtual std::expected<BOOL, VacuumInterface::Error> IsEvacValveOpen();
	virtual VacuumInterface::Error SetEvacValveOpen(const BOOL open);

	virtual VacuumInterface::Error SetPump(const BOOL enable);
	virtual std::expected<BOOL, VacuumInterface::Error> IsPumping();

	//xrf interface
	double m_set_kv = 50;
	double m_set_ua = 1'000;
	BOOL m_shutter = FALSE;

	virtual std::expected<double, XRFInterface::Error> GetkV();
	virtual std::expected<double, XRFInterface::Error> GetTargetkV();
	virtual XRFInterface::Error SetkV(const double new_kv);

	virtual std::expected<double, XRFInterface::Error> GetuA();
	virtual std::expected<double, XRFInterface::Error> GetTargetuA();
	virtual XRFInterface::Error SetuA(const double new_uA);

	virtual XRFInterface::Error EnableBeam();
	virtual XRFInterface::Error DisableBeam();
	virtual std::expected<BOOL, XRFInterface::Error> IsBeamEmittingXrays();

	virtual std::expected<BOOL, XRFInterface::Error> HasShutter();
	virtual std::expected<BOOL, XRFInterface::Error> IsShutterOpen();
	virtual XRFInterface::Error SetShutter(const BOOL open);

	virtual std::expected<double, XRFInterface::Error> GetMaxkV();
	virtual std::expected<double, XRFInterface::Error> GetMinkV();
	virtual std::expected<double, XRFInterface::Error> GetMaxuA();
	virtual std::expected<double, XRFInterface::Error> GetMinuA();
	virtual std::expected<double, XRFInterface::Error> GetMaxWatts();
	virtual std::expected<double, XRFInterface::Error> GetWattAdjustedMaxuA();

	//filter interface
	int m_filter = 0;
	virtual FilterInterface::Error SetFilter(const int filter_position);
	virtual std::expected<int, FilterInterface::Error> GetFilter();
	virtual std::expected<int, FilterInterface::Error> GetNumberOfFilters();

	virtual std::expected<FilterInterface::FilterStats, FilterInterface::Error> GetFilterStats(const int filter_position);

	//vacuum sensor interface
	virtual std::expected<double, VacuumSensorInterface::Error> GetATM();

	//chamber light interface
	int m_chamber_brightness = 255;
	virtual ChamberLightInterface::Error SetChamberLightBrightness(const int brightness);
	virtual std::expected<int, ChamberLightInterface::Error> GetChamberLightBrightness();
	virtual std::expected<int, ChamberLightInterface::Error> GetChamberLightMaxBrightness();

	virtual ChamberLightInterface::Error SetChamberLightColor(const ChamberLightInterface::LightColor color);
	virtual std::expected<ChamberLightInterface::LightColor, ChamberLightInterface::Error> GetChamberLightColor();

	//ceiling laser interface
	BOOL m_ceiling_laser = FALSE;
	virtual CeilingLaserInterface::Error SetCeilingLaser(const BOOL enable);
	virtual std::expected<BOOL, CeilingLaserInterface::Error> GetCeilingLaserEnabled();
	virtual std::expected<CeilingLaserInterface::CeilingLaserState, CeilingLaserInterface::Error> GetCeilingLaserState();

	//spot laser interface
	BOOL m_spot_laser = FALSE;
	virtual SpotLaserInterface::Error SetSpotLaser(const BOOL enable);
	virtual std::expected<BOOL, SpotLaserInterface::Error> GetSpotLaserEnabled();

	//stage controller interface
	millimeters m_x_position = millimeters(50);
	millimeters m_y_position = millimeters(50);
	millimeters m_z_position = millimeters(50);

	millimeters m_x_slew = millimeters(50);
	millimeters m_y_slew = millimeters(50);
	millimeters m_z_slew = millimeters(50);

	millimeters m_x_acceleration = millimeters(50);
	millimeters m_y_acceleration = millimeters(50);
	millimeters m_z_acceleration = millimeters(50);

	virtual std::vector<std::recursive_timed_mutex*> GetStageControlLockingList(const std::optional<BOOL> include_x_stage, const std::optional<BOOL> include_y_stage, const std::optional<BOOL> include_z_stage);

	virtual StageValueReturn<StageControlInterface::Error> SetStagePosition(const std::optional<millimeters> x_stage_position, const std::optional<millimeters> y_stage_position, const std::optional<millimeters> z_stage_position);
	virtual StageValueReturn<StageControlInterface::Error> SetStageSlewSpeed(const std::optional<millimeters> x_slew_speed, const std::optional<millimeters> y_slew_speed, const std::optional<millimeters> z_slew_speed);
	virtual StageValueReturn<StageControlInterface::Error> SetStageAcceleration(const std::optional<millimeters> x_acceleration, const std::optional<millimeters> y_acceleration, const std::optional<millimeters> z_acceleration);
	virtual StageValueReturn<StageControlInterface::Error> SetStageToHome(const std::optional<BOOL> home_x_stage, const std::optional<BOOL> home_y_stage, const std::optional<BOOL> home_z_stage);
	virtual StageValueReturn<StageControlInterface::Error> SetStageToStop(const std::optional<BOOL> stop_x_stage, const std::optional<BOOL> stop_y_stage, const std::optional<BOOL> stop_z_stage);
	virtual StageValueReturn<StageControlInterface::Error> SetStageTrigger(const std::optional<DPPTriggerParameters> x_setup_parameters, const std::optional<DPPTriggerParameters> y_setup_parameters, const std::optional<DPPTriggerParameters> z_setup_parameters);
	virtual StageValueReturn<StageControlInterface::Error> SetStageExternalControl(const std::optional<BOOL> enable_external_x_control, const std::optional<BOOL> enable_external_y_control, const std::optional<BOOL> enable_external_z_control);

	virtual StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> GetMovingStages(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> GetStagesLimits(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesPosition(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesSlewSpeed(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesAcceleration(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);

	virtual StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> GetStageParameterOverhead(const std::optional<millimeters> x_stage_final_speed, const std::optional<millimeters> y_stage_final_speed, const std::optional<millimeters> z_stage_final_speed);

public:

	VirtualATLASHardwareElement() :
		HardwareInterface("Virtual Atlas Hardware"),
		VacuumInterface("Virtual Atlas Vacuum", &m_hardware_lock),
		XRFInterface("Virtual Atlas XRF", &m_hardware_lock),
		FilterInterface("Virtual Atlas Filter", &m_hardware_lock),
		VacuumSensorInterface("Virtual Atlas Vacuum Sensor", &m_hardware_lock),
		ChamberLightInterface("Virtual Atlas Chamber Light", &m_hardware_lock),
		CeilingLaserInterface("Virtual Atlas Ceiling Laser", &m_hardware_lock),
		SpotLaserInterface("Virtual Atlas Spot Laser", &m_hardware_lock),
		StageControlInterface("Virtual Atlas Stage Control")
	{

	}
	virtual ~VirtualATLASHardwareElement() {}
};

