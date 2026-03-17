#pragma once
//#include "../IXRFUtility.hxx"
#include "HardwareInterface.h"
#include <expected>

struct DPPTriggerParameters
{
	millimeters startPosition{ 0 };
	millimeters endPosition{ 0 };
	millimeters pixelSize{ 0 };
	long int numberOfPixels{ 0 };
};

struct StageLimits
{
	millimeters m_min_stage_position{ 0 };
	millimeters m_max_stage_position{ 0 };

	millimeters m_min_stage_speed{ 0 };
	millimeters m_max_stage_speed{ 0 };

	millimeters m_min_stage_acceleration{ 0 };
	millimeters m_max_stage_acceleration{ 0 };
};

struct SlewOverhead
{
	milliseconds m_time;
	millimeters m_distance;
};

template<typename Value>
class StageValueReturn
{
public:
	Value m_x_value;
	Value m_y_value;
	Value m_z_value;

	StageValueReturn() {};
	StageValueReturn(Value x_value, Value y_value)
	{
		m_x_value = x_value;
		m_y_value = y_value;
	}
	StageValueReturn(Value x_value, Value y_value, Value z_value)
	{
		m_x_value = x_value;
		m_y_value = y_value;
		m_z_value = z_value;
	}

	StageValueReturn(const StageValueReturn& copy)
	{
		m_x_value = copy.m_x_value;
		m_y_value = copy.m_y_value;
		m_z_value = copy.m_z_value;
	}
};

#define CLASSES_ALLOWED_STAGE_INTERFACE_ACCESS friend StageControlInterface;friend ATLASStageController;

class  StageControlInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
public:
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		stage_is_in_error, //the stage has an error
	};

	StageControlInterface(const std::string id) : m_id(id) { };
	virtual ~StageControlInterface() {};

	virtual std::vector<std::recursive_timed_mutex*> GetStageControlLockingList(const std::optional<BOOL> include_x_stage, const std::optional<BOOL> include_y_stage, const std::optional<BOOL> include_z_stage) = 0;
protected:
	
	virtual StageValueReturn<StageControlInterface::Error> SetStagePosition(const std::optional<millimeters> x_stage_position, const std::optional<millimeters> y_stage_position, const std::optional<millimeters> z_stage_position) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageSlewSpeed(const std::optional<millimeters> x_slew_speed, const std::optional<millimeters> y_slew_speed, const std::optional<millimeters> z_slew_speed) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageAcceleration(const std::optional<millimeters> x_acceleration, const std::optional<millimeters> y_acceleration, const std::optional<millimeters> z_acceleration) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageToHome(const std::optional<BOOL> home_x_stage, const std::optional<BOOL> home_y_stage, const std::optional<BOOL> home_z_stage) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageToStop(const std::optional<BOOL> stop_x_stage, const std::optional<BOOL> stop_y_stage, const std::optional<BOOL> stop_z_stage) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageTrigger(const std::optional<DPPTriggerParameters> x_setup_parameters, const std::optional<DPPTriggerParameters> y_setup_parameters, const std::optional<DPPTriggerParameters> z_setup_parameters) = 0;
	virtual StageValueReturn<StageControlInterface::Error> SetStageExternalControl(const std::optional<BOOL> enable_external_x_control, const std::optional<BOOL> enable_external_y_control, const std::optional<BOOL> enable_external_z_control) = 0;

	virtual StageValueReturn<std::expected<BOOL, StageControlInterface::Error>> GetMovingStages(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage) = 0;
	virtual StageValueReturn<std::expected<StageLimits, StageControlInterface::Error>> GetStagesLimits(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage) = 0;
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesPosition(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage) = 0;
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesSlewSpeed(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage) = 0;
	virtual StageValueReturn<std::expected<millimeters, StageControlInterface::Error>> GetStagesAcceleration(const std::optional<BOOL> check_x_stage, const std::optional<BOOL> check_y_stage, const std::optional<BOOL> check_z_stage) = 0;

	virtual StageValueReturn<std::expected<SlewOverhead, StageControlInterface::Error>> GetStageParameterOverhead(const std::optional<millimeters> x_stage_final_speed, const std::optional<millimeters> y_stage_final_speed, const std::optional<millimeters> z_stage_final_speed) = 0;
};

class  ZStageInterface
{
CLASSES_ALLOWED_STAGE_INTERFACE_ACCESS
private:
	std::recursive_timed_mutex* m_object_lock;

public:
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		position_unknown, //the current stage position is not known
		stage_is_in_error, //the stage has an error
	};

	ZStageInterface(std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {};
	virtual ~ZStageInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual std::expected<millimeters, Error> GetZStagePosition() = 0;
	virtual std::expected<StageLimits, Error> GetZStageLimits() = 0;
	virtual std::expected<SlewOverhead, Error> GetZStageParameterOverhead(const millimeters speed) = 0;
	virtual std::expected<millimeters, Error> GetZSlewSpeed() = 0;
	virtual std::expected<millimeters, Error> GetZAcceleration() = 0;

	virtual Error SetZStagePosition(const millimeters stage_position_mm) = 0;
	virtual Error SetZSlewSpeed(const millimeters new_slew_speed) = 0;
	virtual Error SetZAcceleration(const millimeters new_acceleration) = 0;
	virtual Error SetupZDPPTrigger(const DPPTriggerParameters setupParameters) = 0;
	virtual Error SetZStageExternalControl(const BOOL enable_external_control) = 0;

	virtual std::expected<BOOL, Error> IsZStageMoving() = 0;
	virtual Error HomeZStage() = 0;
	virtual Error StopZStage() = 0;
};

class  XStageInterface
{
CLASSES_ALLOWED_STAGE_INTERFACE_ACCESS
private:
	std::recursive_timed_mutex* m_object_lock;

public:
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		position_unknown, //the current stage position is not known
		stage_is_in_error, //the stage has an error
	};

	XStageInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {};
	virtual ~XStageInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual std::expected<millimeters, Error> GetXStagePosition() = 0;
	virtual std::expected<StageLimits, Error> GetXStageLimits() = 0;
	virtual std::expected<SlewOverhead, Error> GetXStageParameterOverhead(const millimeters speed) = 0;
	virtual std::expected<millimeters, Error> GetXSlewSpeed() = 0;
	virtual std::expected<millimeters, Error> GetXAcceleration() = 0;

	virtual Error SetXStagePosition(const millimeters stage_position_mm) = 0;
	virtual Error SetXSlewSpeed(millimeters new_slew_speed) = 0;
	virtual Error SetXAcceleration(const millimeters new_acceleration) = 0;
	virtual Error SetupXDPPTrigger(DPPTriggerParameters setupParameters) = 0;
	virtual Error SetXStageExternalControl(BOOL enable_external_control) = 0;

	virtual std::expected<BOOL, Error> IsXStageMoving() = 0;
	virtual Error HomeXStage() = 0;
	virtual Error StopXStage() = 0;
};

class  YStageInterface
{
CLASSES_ALLOWED_STAGE_INTERFACE_ACCESS
private:
	std::recursive_timed_mutex* m_object_lock;

public:
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		position_unknown, //the current stage position is not known
		stage_is_in_error, //the stage has an error
	};

	YStageInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {};
	virtual ~YStageInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual std::expected<millimeters, Error> GetYStagePosition() = 0;
	virtual std::expected<StageLimits, Error> GetYStageLimits() = 0;
	virtual std::expected<SlewOverhead, Error> GetYStageParameterOverhead(const millimeters speed) = 0;
	virtual std::expected<millimeters, Error> GetYSlewSpeed() = 0;
	virtual std::expected<millimeters, Error> GetYAcceleration() = 0;

	virtual Error SetYStagePosition(millimeters stage_position_mm) = 0;
	virtual Error SetYSlewSpeed(const millimeters new_slew_speed) = 0;
	virtual Error SetYAcceleration(const millimeters new_acceleration) = 0;
	virtual Error SetupYDPPTrigger(const DPPTriggerParameters setupParameters) = 0;
	virtual Error SetYStageExternalControl(const BOOL enable_external_control) = 0;

	virtual std::expected<BOOL, Error> IsYStageMoving() = 0;
	virtual Error HomeYStage() = 0;
	virtual Error StopYStage() = 0;
};