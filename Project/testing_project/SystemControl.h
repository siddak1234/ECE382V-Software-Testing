#pragma once
#include "HardwareInterface.h"
#include "StageControl.h"
#include "XRFInterface.h"
#include "VacuumInterface.h"
//#include "CameraInterface.h"
#include <memory>
//#include "OpenCVVideo.h"
//#include "OpenCVDinoCam.h"
//#include "DinoCam32bitVideo.h"
#include "DistanceSensorInterface.h"
//#include "DPPInterface.h"

#include<expected>


//additional questions that can be asked
class HasCurrentBeam
{
public:
	virtual int GetInUseBeam() = 0;
	virtual BOOL HasPrimary() = 0;
	virtual BOOL HasSecondary() = 0;
};

class IsDistanceSensorAnOption
{
public:
	virtual BOOL HasDistanceSensor() = 0;
};

class  SystemControl
{
protected:
	std::vector<std::unique_ptr<HardwareInterface>> m_hardware_connections;
	std::vector<VacuumInterface*> m_vacuum_interface;
	std::vector<XRFInterface*> m_xrf_interface;
	std::vector<FilterInterface*> m_filter_interface;
	std::vector<VacuumSensorInterface*> m_vacuum_sensor_interface;
	std::vector<ChamberLightInterface*> m_chamber_light_interface;
	std::vector<CeilingLaserInterface*> m_ceiling_laser_interface;
	std::vector<SpotLaserInterface*> m_spot_laser_interface;
	//std::vector<CameraInterface*> m_camera_interface;
	std::vector<DistanceSensorInterface*> m_distance_sensor_interface;
	//std::vector<DPPInterface*> m_dpp_interface;
	std::unique_ptr<StageControlInterface> m_stage_control_interface;
	

public:
	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		index_out_of_range, //the provided index is out of range
	};

	SystemControl() {}
	virtual ~SystemControl() {}

	//getters for the interfaces
	virtual std::expected<HardwareInterface*, SystemControl::Error> GetHardwareInterface(const int hardware_index);
	virtual std::expected<VacuumInterface*, SystemControl::Error> GetVacuumInterface(const int vacuum_index);
	virtual std::expected<XRFInterface*, SystemControl::Error> GetXRFInterface(const int xrf_index);
	virtual std::expected<FilterInterface*, SystemControl::Error> GetFilterInterface(const int filter_index);
	virtual std::expected<VacuumSensorInterface*, SystemControl::Error> GetVacuumSensorInterface(const int vacuum_sensor_index);
	virtual std::expected<ChamberLightInterface*, SystemControl::Error> GetChamberLightInterface(const int chamber_light_index);
	virtual std::expected<CeilingLaserInterface*, SystemControl::Error> GetCeilingLaserInterface(const int ceiling_laser_index);
	virtual std::expected<SpotLaserInterface*, SystemControl::Error>  GetSpotLaserInterface(const int spot_laser_index);
	//virtual std::expected<CameraInterface*, SystemControl::Error> GetCameraInterface(const int camera_index);
	virtual std::expected<DistanceSensorInterface*, SystemControl::Error> GetDistanceSensorInterface(const int distance_sensor_index);
	//virtual std::expected<DPPInterface*, SystemControl::Error> GetDPPInterface(const int dpp_index);
	virtual StageControlInterface* GetStageControlInterface();

	//hardware interface
	virtual SystemControl::Error InitializeSystem() = 0;
	virtual SystemControl::Error DeInitializeSystem() = 0;
	virtual HardwareInterface::Error Reconnect(const int hardware_index);
	virtual int GetNumberOfHardwareElements();

	//vacuum interface
	virtual VacuumInterface::Error SetVacuum(const VacuumInterface::VacuumType vacuum_type, const int vacuum_index);
	virtual std::expected<VacuumInterface::VacuumType, VacuumInterface::Error> GetVacuum(const int vacuum_index);

	virtual std::expected<BOOL, VacuumInterface::Error> IsVentValveOpen(const int vacuum_index);
	virtual VacuumInterface::Error SetVentValveOpen(const BOOL open, const int vacuum_index);

	virtual std::expected<BOOL, VacuumInterface::Error> IsEvacValveOpen(const int vacuum_index);
	virtual VacuumInterface::Error SetEvacValveOpen(const BOOL open, const int vacuum_index);

	virtual VacuumInterface::Error SetPump(const BOOL enable, const int vacuum_index);
	virtual std::expected<BOOL, VacuumInterface::Error> IsPumping(const int vacuum_index);

	//xrf interface
	virtual std::expected<double, XRFInterface::Error> GetkV(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetTargetkV(const int xrf_index);
	virtual XRFInterface::Error SetkV(const double new_kv, const int xrf_index);

	virtual std::expected<double, XRFInterface::Error> GetuA(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetTargetuA(const int xrf_index);
	virtual XRFInterface::Error SetuA(const double new_uA, const int xrf_index);

	virtual XRFInterface::Error EnableBeam(const int xrf_index);
	virtual XRFInterface::Error DisableBeam(const int xrf_index);
	virtual std::expected<BOOL, XRFInterface::Error> IsBeamEmittingXrays(const int xrf_index);

	virtual std::expected<BOOL, XRFInterface::Error> HasShutter(const int xrf_index);
	virtual std::expected<BOOL, XRFInterface::Error> IsShutterOpen(const int xrf_index);
	virtual XRFInterface::Error SetShutter(const BOOL open, const int xrf_index);

	virtual std::expected<double, XRFInterface::Error> GetMaxkV(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetMinkV(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetMaxuA(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetMinuA(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetMaxWatts(const int xrf_index);
	virtual std::expected<double, XRFInterface::Error> GetWattAdjustedMaxuA(const int xrf_index);

	//filter interface
	virtual FilterInterface::Error SetFilter(const int filter_position, const int filter_index);
	virtual std::expected<int, FilterInterface::Error> GetFilter(const int filter_index);
	virtual std::expected<int, FilterInterface::Error> GetNumberOfFilters(const int filter_index);
	std::expected<int, FilterInterface::Error> FindIndexOfFilter(std::string name, int filter_index);

	virtual std::expected<FilterInterface::FilterStats, FilterInterface::Error> GetFilterStats(const int filter_position, const int filter_index);

	//vacuum sensor interface
	virtual std::expected<double, VacuumSensorInterface::Error> GetATM(const int vacuum_sensor_index);

	//chamber light interface
	virtual ChamberLightInterface::Error SetChamberLightBrightness(const int brightness, const int chamber_light_index);
	virtual std::expected<int, ChamberLightInterface::Error> GetChamberLightBrightness(const int chamber_light_index);
	virtual std::expected<int, ChamberLightInterface::Error> GetChamberLightMaxBrightness(const int chamber_light_index);

	virtual ChamberLightInterface::Error SetChamberLightColor(const ChamberLightInterface::LightColor color, const int chamber_light_index);
	virtual std::expected<ChamberLightInterface::LightColor, ChamberLightInterface::Error> GetChamberLightColor(const int chamber_light_index);

	//ceiling laser interface
	virtual CeilingLaserInterface::Error SetCeilingLaser(const BOOL enable, const int ceiling_laser_index);
	virtual std::expected<BOOL, CeilingLaserInterface::Error> GetCeilingLaserEnabled(const int ceiling_laser_index);
	virtual std::expected<CeilingLaserInterface::CeilingLaserState, CeilingLaserInterface::Error> GetCeilingLaserState(const int ceiling_laser_index);

	//spot laser interface
	virtual SpotLaserInterface::Error SetSpotLaser(const BOOL enable, const int spot_laser_interface_index);
	virtual std::expected<BOOL, SpotLaserInterface::Error> GetSpotLaserEnabled(const int spot_laser_interface_index);

	//camera interface
	// virtual std::expected<int, SystemControl::Error> FindCameraFromDeviceIndex(const int device_index);
	// virtual int GetNumberOfCameras();

	//distance sensor interface
	virtual std::expected<millimeters, DistanceSensorInterface::Error> GetDistance(const int distance_sensor_index);
	virtual DistanceSensorInterface::Error StartDistanceStream(const int distance_sensor_index);
	virtual std::expected<BOOL, DistanceSensorInterface::Error> IsDistanceStreamRunning(const int distance_sensor_index);
	virtual DistanceSensorInterface::Error StopDistanceStream(const int distance_sensor_index);
	virtual DistanceSensorInterface::Error ResetSensor(const int distance_sensor_index);

	//stage controller interface
	virtual std::vector<std::recursive_timed_mutex*> GetStageControlLockingList(const std::optional<BOOL> include_x_stage, const std::optional<BOOL> include_y_stage, const std::optional<BOOL> include_z_stage);

	virtual StageValueReturn<StageControlInterface::Error> SetStagePosition(const std::optional<millimeters> x_stage_position, const std::optional<millimeters> y_stage_position, const std::optional<millimeters> z_stage_position);
	virtual StageValueReturn<StageControlInterface::Error> SetStageSlewSpeed(const std::optional<millimeters> x_slew_speed, const std::optional<millimeters> y_slew_speed, const std::optional<millimeters> z_slew_speed);
	virtual StageValueReturn<StageControlInterface::Error> SetStageToHome(const std::optional<BOOL> home_x_stage, const std::optional<BOOL> home_y_stage, const std::optional<BOOL> home_z_stage);
	virtual StageValueReturn<StageControlInterface::Error> SetStageToStop(const std::optional<BOOL> stop_x_stage, const std::optional<BOOL> stop_y_stage, const std::optional<BOOL> stop_z_stage);
	virtual StageValueReturn<StageControlInterface::Error> SetStageTrigger(const std::optional<DPPTriggerParameters> x_setup_parameters, const std::optional<DPPTriggerParameters> y_setup_parameters, const std::optional<DPPTriggerParameters> z_setup_parameters);
	virtual StageValueReturn<StageControlInterface::Error> SetStageExternalControl(const std::optional<BOOL> enable_external_x_control, const std::optional<BOOL> enable_external_y_control, const std::optional<BOOL> enable_external_z_control);

	virtual StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> GetMovingStages(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> GetStagesLimits(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesPosition(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesSlewSpeed(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage);

	virtual StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> GetStageParameterOverhead(const std::optional<millimeters> x_stage_final_speed, const std::optional<millimeters> y_stage_final_speed, const std::optional<millimeters> z_stage_final_speed);

	//dpp controller interface
	// virtual std::expected<std::vector<DPP::DppReadout>, DPPInterface::Error> GetDppCustomReadouts(const int dpp_index);
	// virtual std::expected<std::vector<DPP::DppReadout>, DPPInterface::Error> GetDppSymbols(const int dpp_index);
	// virtual DPPInterface::Error SetDppSymbols(DPP::DppReadout symbol_to_set, const int dpp_index);

	// virtual std::expected<std::array<double, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetAllDetectorsDeadtime(const int dpp_index);
	// virtual std::expected<std::array<LONGLONG, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetAllDetectorsCPS(const int dpp_index);
	// virtual std::expected<std::array<seconds, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetAllDetectorsRealTime(const int dpp_index);
	// virtual std::expected<std::array<seconds, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetAllDetectorsLiveTime(const int dpp_index);

	// virtual DPPInterface::Error GetLiveSpectrum(DPP::PixelData& spectra, const int dpp_index);

	// virtual DPPInterface::Error SetEnergyCalibration(const int detector, const double TC, const DPP::EnergyCalibration energy_calibration, const int dpp_index);
	// virtual std::expected<DPP::EnergyCalibration, DPPInterface::Error> GetEnergyCalibration(const int detector, const double TC, const int dpp_index);

	// virtual DPPInterface::Error SetPolyEnergyCal(const int detector, const double TC, DPP::CPolyCal polyCal, const int dpp_index);
	// virtual std::expected<DPP::CPolyCal, DPPInterface::Error> GetPolyEnergyCal(const int detector, const double TC, const int dpp_index);

	// virtual std::expected<double, DPPInterface::Error> GetCurrentTC(const int dpp_index);
	// virtual DPPInterface::Error SetTC(const double new_TC, const int dpp_index);

	// virtual DPPInterface::Error PrepareForFastMapScan(const DPP::SetupMapSettings settings, const int dpp_index);
	// virtual DPPInterface::Error PrepareForLineScan(const DPP::SetupLineScanSettings settings, const int dpp_index);
	// virtual DPPInterface::Error PrepareForSpectrum(const DPP::SetupSpectrumSettings settings, const int dpp_index);

	// virtual DPPInterface::Error AcquireLine(const DPP::DppLineSettings settings, const int dpp_index);
	// virtual DPPInterface::Error AcquireSpectrum(const DPP::DppSpectrumSettings settings, const int dpp_index);

	// virtual DPPInterface::Error EndAcquisitionSequence(const int dpp_index);
	// virtual std::expected<DPP::acquisition_mode, DPPInterface::Error> GetCurrentAcquisitionMode(const int dpp_index);

	// virtual DPPInterface::Error SetCurrentDetectors(const std::array<BOOL, MAX_DETECTOR_COUNT> used_detectors, const int dpp_index);
	// virtual std::expected<std::array<BOOL, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetCurrentDetectors(const int dpp_index);

	// virtual DPPInterface::Error SetAvailableDetectors(const std::array<BOOL, MAX_DETECTOR_COUNT> available_detectors, const int dpp_index);
	// virtual std::expected<std::array<BOOL, MAX_DETECTOR_COUNT>, DPPInterface::Error> GetAvailableDetectors(const int dpp_index);

	// virtual DPPInterface::Error StopAcquisition(const int dpp_index);

	// virtual std::expected<double, DPPInterface::Error> GeteVPerChannel(const int dpp_index);

	// virtual std::expected<seconds, DPPInterface::Error> GetMaxDwell(const int dpp_index);

	// virtual DPPInterface::Error SubscribeToData(DPP::PixelDataQueue* queue, const int dpp_index);
	// virtual DPPInterface::Error UnSubscribeToData(DPP::PixelDataQueue* queue, const int dpp_index);
};

static std::unique_ptr<SystemControl> g_system_controller;

namespace Hardware
{
	// IXRF_SYSTEMINTERFACE_PROC HardwareInterface::Error GenericInitializeCameras(std::vector<std::unique_ptr<HardwareInterface>>& hardware_connections, std::vector<CameraInterface*>& camera_interface);

	// //has GUI elements
	// IXRF_SYSTEMINTERFACE_PROC HardwareInterface::Error EnsureDinocamLightState(BOOL enabled);

	// IXRF_SYSTEMINTERFACE_PROC StageControlInterface::Error DriveStageTo(millimeters mmTargetX, millimeters mmTargetY, std::atomic<BOOL>& abort);
	// IXRF_SYSTEMINTERFACE_PROC StageControlInterface::Error EnsureStagesStoped(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage, milliseconds wait_until, std::atomic<BOOL>& abort);
	// IXRF_SYSTEMINTERFACE_PROC StageControlInterface::Error EnsureStagesMoving(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage, milliseconds wait_until, std::atomic<BOOL>& abort);


	// struct SetParameters
	// {
	// 	std::optional<int> m_xrf_index = {};
	// 	std::optional<double> m_set_kv = {};
	// 	std::optional<double> m_set_ua = {};

	// 	std::optional<int> m_filter_index = {};
	// 	std::optional<double> m_filter_position = {};
	// };
	// IXRF_SYSTEMINTERFACE_PROC HardwareInterface::Error ResponsiveSetSystemParameters(SetParameters parameters, std::atomic<BOOL>& abort);
}