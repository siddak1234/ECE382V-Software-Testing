#pragma once

//#include "../IXRFUtility.hxx"
#include "HardwareInterface.h"
#include <expected>

class  DistanceSensorInterface
{
CLASSES_ALLOWED_INTERFACE_ACCESS
private:
	std::recursive_timed_mutex* m_object_lock;
public:
	
	const std::string m_id;

	enum class Error
	{
		no_error,      //no error detected
		peak_behind,   //the sensor sees the laser after its measurement range
		peak_before,   //the sensor sees the laser before its measurement range
		no_peak,       //the sensor cannot see the laser at all (to close or to far away)
		laser_off,     //the sensor laser is off and cannot get a measurement
		generic_error, //general sensor error meant to catch anything that the sensor throws that doesn�t have purpose yet
		failed_to_align_with_buffer,  //the read of the buffer failed because it couldn't find the starting section of a packet
		error_cannot_recover,  //a error has happened and the device is unable to attempt a recovery
		error_attempting_to_recover,  //a error has happened and the device is attempting to recover
		recovering_from_previous_error, //a error has happened on some previous call and the device is still attempting to recover
		already_connected, //the device is already connected too
		index_out_of_range, //for when the requested interface at the system control level is out of range of the vector
	};

	DistanceSensorInterface(const std::string id, std::recursive_timed_mutex* object_lock) : m_id(id), m_object_lock(object_lock) {}
	virtual ~DistanceSensorInterface() {}
	std::recursive_timed_mutex* GetInterfaceObjectLock() { return m_object_lock; }

	virtual std::expected<millimeters, Error> GetDistance() = 0;//gets the last read distance of the sensor
protected:
	virtual Error StartDistanceStream() = 0;//starts the streaming of distance values
	virtual std::expected<BOOL, DistanceSensorInterface::Error> IsDistanceStreamRunning() = 0;
	virtual Error StopDistanceStream() = 0;//stops the streaming of distance values
	virtual Error ResetSensor() = 0;//resets the sensor
};

