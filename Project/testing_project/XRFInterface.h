#pragma once

//#include "../IXRFUtility.hxx"
#include "HardwareInterface.h"
#include <expected>

class  XRFInterface
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

	XRFInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~XRFInterface() {};
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual std::expected<double, Error> GetkV() = 0;
	virtual std::expected<double, Error> GetTargetkV() = 0;
	virtual Error SetkV(const double new_kv) = 0;

	virtual std::expected<double, Error> GetuA() = 0;
	virtual std::expected<double, Error> GetTargetuA() = 0;
	virtual Error SetuA(const double new_uA) = 0;

	virtual Error EnableBeam() = 0;
	virtual Error DisableBeam() = 0;
	virtual std::expected<BOOL, Error> IsBeamEmittingXrays() = 0;

	virtual std::expected<BOOL, Error> HasShutter() = 0;
	virtual std::expected<BOOL, Error> IsShutterOpen() = 0;
	virtual Error SetShutter(const BOOL open) = 0;

	virtual std::expected<double, Error> GetMaxkV() = 0;
	virtual std::expected<double, Error> GetMinkV() = 0;
	virtual std::expected<double, Error> GetMaxuA() = 0;
	virtual std::expected<double, Error> GetMinuA() = 0;
	virtual std::expected<double, Error> GetMaxWatts() = 0;
	virtual std::expected<double, Error> GetWattAdjustedMaxuA() = 0;
};


class  FilterInterface
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
		moving,        //the filter wheel is moving
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	struct FilterStats
	{
		std::string name;
		std::string label;
		double thickness;
		//COLORREF color;
		std::string description;
	};

	FilterInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~FilterInterface() {}
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

protected:
	virtual Error SetFilter(const int filter_index) = 0;
	virtual std::expected<int, Error> GetFilter() = 0;
	virtual std::expected<int, Error> GetNumberOfFilters() = 0;

	virtual std::expected<FilterStats, Error> GetFilterStats(const int filter_position) = 0;
};