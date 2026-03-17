#pragma once
#include "SystemControl.h"
#include <thread>
//#include "AtlasVacuum.h"
//#include "../xrfcontroller.hxx"

// #ifdef _BUILD_ATLASCONTROLLER
// #define IXRF_ATLASCONTROLLER_CLASS_DECL AFX_CLASS_EXPORT
// #define IXRF_ATLASCONTROLLER_PROC extern "C" __declspec( dllexport)
// #define IXRF_ATLASCONTROLLER_DATA extern __declspec (dllexport)
// #else
// #define IXRF_ATLASCONTROLLER_CLASS_DECL AFX_CLASS_IMPORT
// #define IXRF_ATLASCONTROLLER_PROC extern "C" __declspec( dllimport)
// #define IXRF_ATLASCONTROLLER_DATA extern __declspec (dllimport)
// #pragma comment(lib,"AtlasController.lib")
// #pragma message("Automatically linking with AtlasController.lib")
// #endif

class AtlasControl : 
	public SystemControl,
	public HasCurrentBeam,
	public IsDistanceSensorAnOption
{
private:
	std::atomic<int> m_in_use_beam = 0;
	BOOL m_has_distance_sensor = FALSE;
	BOOL m_has_primary_beam = FALSE;
	BOOL m_has_secondary_beam = FALSE;

	std::atomic<BOOL> m_run_update_thread = FALSE;
	std::thread m_APEX_update_thread;

	SystemControl::Error SetupAsVIRTUAL();
	SystemControl::Error SetupAsATLAS();
	SystemControl::Error SetupAsAPEX();
	SystemControl::Error SetupDPP();

	void APEXUpdateThread();

public:
	//hardware interface
	virtual SystemControl::Error InitializeSystem();
	virtual SystemControl::Error DeInitializeSystem();

	//vacuum interface
	virtual VacuumInterface::Error SetVacuum(VacuumInterface::VacuumType vacuum_type, int vacuum_index);

	virtual VacuumInterface::Error SetVentValveOpen(BOOL open, int vacuum_index);
	virtual VacuumInterface::Error SetEvacValveOpen(BOOL open, int vacuum_index);

	//xrf interface

	virtual XRFInterface::Error EnableBeam(int xrf_index);

	virtual XRFInterface::Error SetShutter(BOOL open, int xrf_index);

	XRFInterface::Error EnforceOnlyOneBeamOn(int xrf_index);
	BOOL CheckZStageIsNearHome();
	//SystemControl::Error SetupSecondarySystem(CAtlasVacuum* vacuum_controller_index);

	int GetInUseBeam();
	BOOL HasPrimary();
	BOOL HasSecondary();
	BOOL HasDistanceSensor();

	//millimeters GetSecondaryOffset(SECONDARYOFFSET idx, CString szSpotSize);
};