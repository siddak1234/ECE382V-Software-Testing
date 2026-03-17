#pragma once

#include <chrono>
// #ifdef _BUILD_SYSTEMINTERFACES
// #define  AFX_CLASS_EXPORT
// #define IXRF_SYSTEMINTERFACE_PROC extern "C" __declspec( dllexport)
// #define IXRF_SYSTEMINTERFACE_DATA __declspec (dllexport)
// #else
// #define  AFX_CLASS_IMPORT
// #define IXRF_SYSTEMINTERFACE_PROC extern "C" __declspec( dllimport)
// #define IXRF_SYSTEMINTERFACE_DATA __declspec (dllimport)
// #pragma comment(lib,"SystemInterfaces.lib")
// #pragma message("Automatically linking with SystemInterfaces.lib")
// #endif

#define BOOL bool
#define TRUE true
#define FALSE false

using nanometers = std::chrono::duration<double, std::nano>;
using micrometers = std::chrono::duration<double, std::micro>;
using millimeters = std::chrono::duration<double, std::milli>;
using centimeters = std::chrono::duration<double, std::ratio<1, 100>>;
using meters = std::chrono::duration<double>;
using kilometers = std::chrono::duration<double, std::ratio<1000>>;

using inches = std::chrono::duration<double, std::ratio<254, 10000>>;

using microseconds = std::chrono::duration<double, std::micro>;
using milliseconds = std::chrono::duration<double, std::milli>;
using seconds = std::chrono::duration<double>;
using minutes = std::chrono::duration<double, std::ratio<60>>;
using hours = std::chrono::duration<double, std::ratio<3600>>;
using days = std::chrono::duration<double, std::ratio<86400>>;
using weeks = std::chrono::duration<double, std::ratio<604800>>;
using months = std::chrono::duration<double, std::ratio<2629746>>;
using years = std::chrono::duration<double, std::ratio<31556952>>;


//#include "IXRFUtility.hxx"
#include <expected>
#include <vector>
#include <source_location>
#include <atomic>
#include <mutex>
#include <optional>
#include <string>

//pre-declare are controller classes that should access protected members
class SystemControl;
class ATLASStageController;
class AtlasControl;
#define ATLAS_BASE_INTERFACE_CLASSES friend ATLASStageController;friend AtlasControl;
#define CLASSES_ALLOWED_INTERFACE_ACCESS friend SystemControl; ATLAS_BASE_INTERFACE_CLASSES

class  HardwareLockGuard
{
private:
	std::recursive_timed_mutex* m_hardware_mutex = nullptr;
public:
	HardwareLockGuard(std::recursive_timed_mutex& hardware_mutex, seconds timeout = seconds(10), const std::source_location source = std::source_location::current())
	{
		if (!hardware_mutex.try_lock_for(timeout))
		{
			//LogError(L"Failed to acquire hardware lock, early exiting", source);
			return;
		}

		m_hardware_mutex = &hardware_mutex;
	}
	~HardwareLockGuard()
	{
		if (m_hardware_mutex) { m_hardware_mutex->unlock(); }
	}

	BOOL IsLocked() { return m_hardware_mutex != nullptr; }
};

class  HardwareMultiLockGuard
{
private:
	std::vector<std::recursive_timed_mutex*> m_hardware_mutexes;
public:
	HardwareMultiLockGuard(std::vector<std::recursive_timed_mutex*> mutexes, const std::source_location source = std::source_location::current())
	{
		//yes this is silly but due to C++ not supporting dynamic deadlock avoidance locking we have to do it this way
		switch (mutexes.size())
		{
		case 1: { mutexes[0]->lock(); break; }
		case 2: { std::lock(*mutexes[0], *mutexes[1]); break; }
		case 3: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2]); break; }
		case 4: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3]); break; }
		case 5: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4]); break; }
		case 6: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5]); break; }
		case 7: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5], *mutexes[6]); break; }
		case 8: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5], *mutexes[6], *mutexes[7]); break; }
		case 9: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5], *mutexes[6], *mutexes[7], *mutexes[8]); break; }
		case 10: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5], *mutexes[6], *mutexes[7], *mutexes[8], *mutexes[9]); break; }
		case 11: { std::lock(*mutexes[0], *mutexes[1], *mutexes[2], *mutexes[3], *mutexes[4], *mutexes[5], *mutexes[6], *mutexes[7], *mutexes[8], *mutexes[9], *mutexes[10]); break; }
		default: 
		{
			//LogError(L"Failed to have a default implementation that supports your amount of locks", source);
			return;
			break;
		}
		}

		m_hardware_mutexes = mutexes;
	}
	~HardwareMultiLockGuard()
	{
		if (m_hardware_mutexes.size()) 
		{
			for (auto& mutex : m_hardware_mutexes) { mutex->unlock(); }
		}
	}

	BOOL IsLocked() { return m_hardware_mutexes.size() != 0; }
};

class  HardwareInterface
{
public:
	CLASSES_ALLOWED_INTERFACE_ACCESS
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		failed_rule,   //failed a rule check
		generic_error, //general error meant to indicate a failure to proceed with the function
		not_supported, //the action is not supported by the hardware
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	HardwareInterface(const std::string id) : m_id(id) {}
	virtual ~HardwareInterface() {};

	std::recursive_timed_mutex m_hardware_lock;

protected:
	virtual Error Connect() = 0;
	virtual Error Disconnect() = 0;
	virtual Error Reconnect() = 0;
};

