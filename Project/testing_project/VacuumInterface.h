#pragma once
//#include "../IXRFUtility.hxx"
#include <expected>
#include "HardwareInterface.h"
#include <mutex>

class  VacuumInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
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
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	enum class VacuumType
	{
		Vented,
		Vacuum,
		HE_Flush
	};

	VacuumInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~VacuumInterface() {}
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual Error SetVacuum(const VacuumType vacuum_type) = 0;
	virtual std::expected<VacuumType, Error> GetVacuum() = 0;

	virtual std::expected<BOOL, Error> IsVentValveOpen() = 0;
	virtual Error SetVentValveOpen(const BOOL open) = 0;

	virtual std::expected<BOOL, Error> IsEvacValveOpen() = 0;
	virtual Error SetEvacValveOpen(const BOOL open) = 0;

	virtual Error SetPump(const BOOL enable) = 0;
	virtual std::expected<BOOL, Error> IsPumping() = 0;
};

//currently these classes are in the vacuum file due to them being on the samehardware element (vacuum controller) and being not very large

class  VacuumSensorInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
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
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	VacuumSensorInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~VacuumSensorInterface() {}
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual std::expected<double, Error> GetATM() = 0;
};

class  ChamberLightInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
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
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	struct LightColor
	{
		int red = 0;
		int green = 0;
		int blue = 0;
	};

	ChamberLightInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~ChamberLightInterface() {}
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual Error SetChamberLightBrightness(const int brightness) = 0;
	virtual std::expected<int, Error> GetChamberLightBrightness() = 0;
	virtual std::expected<int, Error> GetChamberLightMaxBrightness() = 0;

	virtual Error SetChamberLightColor(const LightColor color) = 0;
	virtual std::expected<LightColor, Error> GetChamberLightColor() = 0;
};

class  CeilingLaserInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
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
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	enum class CeilingLaserState
	{
		no_issue,
		tripped
	};

	CeilingLaserInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~CeilingLaserInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual Error SetCeilingLaser(const BOOL enable) = 0;
	virtual std::expected<BOOL, Error> GetCeilingLaserEnabled() = 0;
	virtual std::expected<CeilingLaserState, Error> GetCeilingLaserState() = 0;
};

class  SpotLaserInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
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
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	SpotLaserInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~SpotLaserInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual Error SetSpotLaser(const BOOL enable) = 0;
	virtual std::expected<BOOL, Error> GetSpotLaserEnabled() = 0;
};