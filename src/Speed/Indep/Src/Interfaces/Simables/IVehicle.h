#ifndef INTTERFACES_SIMABLES_IVEHICLE_H
#define INTTERFACES_SIMABLES_IVEHICLE_H

#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

#include "Speed/Indep/Libs/Support/Utility/UCOM.h"
#include "Speed/Indep/Libs/Support/Utility/UCrc.h"
#include "Speed/Indep/Libs/Support/Utility/UListable.h"
#include "Speed/Indep/Src/AI/AIVehicle.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/pvehicle.h"
#include "Speed/Indep/Src/Interfaces/Simables/ISimable.h"
#include "Speed/Indep/Src/Physics/PhysicsTunings.h"
#include "Speed/Indep/Src/Physics/PhysicsTypes.h"

enum eVehicleList {
    VEHICLE_ALL,
    VEHICLE_PLAYERS,
    VEHICLE_AI,
    VEHICLE_AIRACERS,
    VEHICLE_AICOPS,
    VEHICLE_AITRAFFIC,
    VEHICLE_RACERS,
    VEHICLE_REMOTE,
    VEHICLE_INACTIVE,
    VEHICLE_TRAILERS,
    VEHICLE_MAX,
};

enum CarType {
    CARTYPE_NONE = -1,
    CARTYPE_911TURBO,
    CARTYPE_CARRERAGT,
    CARTYPE_VIPER,
    CARTYPE_COPMIDSIZE,
    CARTYPE_COPHELI,
    CARTYPE_RX8,
    CARTYPE_IMPREZAWRX,
    CARTYPE_LANCEREVO8,
    CARTYPE_MUSTANGGT,
    CARTYPE_CAMARO,
    CARTYPE_SEMI,
    CARTYPE_GTO,
    CARTYPE_SLR,
    CARTYPE_TRAILERA,
    CARTYPE_TRAILERB,
    CARTYPE_CORVETTE,
    CARTYPE_TRAFHA,
    CARTYPE_TRAFSUVA,
    CARTYPE_TRAF4DSEDB,
    CARTYPE_TRAFFICCOUP,
    CARTYPE_TT,
    CARTYPE_A3,
    CARTYPE_BMWM3GTR,
    CARTYPE_SL500,
    CARTYPE_997S,
    CARTYPE_TRAF4DSEDA,
    CARTYPE_TRAF4DSEDC,
    CARTYPE_TRAFCAMPER,
    CARTYPE_TRAFCEMTR,
    CARTYPE_TRAFDMPTR,
    CARTYPE_TRAFFIRE,
    CARTYPE_TRAFGARB,
    CARTYPE_TRAFMINIVAN,
    CARTYPE_TRAFNEWS,
    CARTYPE_TRAFPICKUPA,
    CARTYPE_TRAFSTWAG,
    CARTYPE_TRAFVANB,
    CARTYPE_TRAFTAXI,
    CARTYPE_TRAFCOURT,
    CARTYPE_TRAFPIZZA,
    CARTYPE_911GT2,
    CARTYPE_BMWM3GTRE46,
    CARTYPE_TRAFAMB,
    CARTYPE_TRAILERLOG,
    CARTYPE_TRAILERCON,
    CARTYPE_TRAILERCRATE,
    CARTYPE_TRAILERCMT,
    CARTYPE_IS300,
    CARTYPE_MONARO,
    CARTYPE_SL65,
    CARTYPE_ELISE,
    CARTYPE_COPMIDSIZEINT,
    CARTYPE_FORDGT,
    CARTYPE_ECLIPSEGT,
    CARTYPE_SUPRA,
    CARTYPE_CORVETTEC6R,
    CARTYPE_RX7,
    CARTYPE_COPSUV,
    CARTYPE_RX8SPEEDT,
    CARTYPE_MURCIELAGO,
    CARTYPE_A4,
    CARTYPE_COPSPORT,
    CARTYPE_GTI,
    CARTYPE_CAYMANS,
    CARTYPE_CLK500,
    CARTYPE_CTS,
    CARTYPE_DB9,
    CARTYPE_GALLARDO,
    CARTYPE_COBALTSS,
    CARTYPE_BMWM3,
    CARTYPE_CLIO,
    CARTYPE_COPGHOST,
    CARTYPE_COPSUVL,
    CARTYPE_COPGTO,
    CARTYPE_PUNTO,
    CARTYPE_COPGTOGHOST,
    CARTYPE_COPSPORTHENCH,
    CARTYPE_COPSPORTGHOST,
    CARTYPE_CEMTR,
    CARTYPE_GARB,
    CARTYPE_PIZZA,
    CARTYPE_TAXI,
    CARTYPE_MINIVAN,
    CARTYPE_PICKUPA,
    NUM_CARTYPES = 84,
};

enum DriverClass {
    DRIVER_HUMAN,
    DRIVER_TRAFFIC,
    DRIVER_COP,
    DRIVER_RACER,
    DRIVER_NONE,
    DRIVER_NIS,
    DRIVER_REMOTE,
};

class IVehicle : public UTL::COM::IUnknown, public UTL::Collections::ListableSet<IVehicle, 10, eVehicleList, VEHICLE_MAX> {
  public:
    static HINTERFACE _IHandle() {
        return (HINTERFACE)_IHandle;
    }

    IVehicle(UTL::COM::Object *owner) : UTL::COM::IUnknown(owner, _IHandle()) {}

    virtual ~IVehicle() {}
    virtual const ISimable *GetSimable() const = 0;
    virtual ISimable *GetSimable() = 0;
    virtual UMath::Vector3 &GetPosition() = 0;
    virtual void SetBehaviorOverride(UCrc32 mechanic, UCrc32 behavior) = 0;
    virtual void RemoveBehaviorOverride(UCrc32 mechanic) = 0;
    virtual void CommitBehaviorOverrides() = 0;
    virtual void SetStaging(bool staging) = 0;
    virtual bool IsStaging() = 0;
    virtual void Launch() = 0;
    virtual float GetPerfectLaunch() = 0;
    virtual void SetDriverStyle(DriverStyle style) = 0;
    virtual DriverStyle GetDriverStyle() = 0;
    virtual void SetPhysicsMode(PhysicsMode mode) = 0;
    virtual PhysicsMode GetPhysicsMode() const = 0;
    virtual CarType GetModelType() = 0;
    virtual bool IsSpooled() = 0;
    virtual const UCrc32 GetVehicleClass() = 0;
    virtual Attrib::Gen::pvehicle &GetVehicleAttributes() = 0;
    virtual const char *GetVehicleName() = 0;
    virtual unsigned int GetVehicleKey() = 0;
    virtual void SetDriverClass(DriverClass dc) = 0;
    virtual DriverClass GetDriverClass() = 0;
    virtual bool IsLoading() const = 0;
    virtual float GetOffscreenTime() = 0;
    virtual float GetOnScreenTime() = 0;
    virtual bool SetVehicleOnGround(const UMath::Vector3 &resetPos, const UMath::Vector3 &initialVec) = 0;
    virtual void ForceStopOn(char forceStopBits) = 0;
    virtual void ForceStopOff(char forceStopBits) = 0;
    virtual bool GetForceStop() = 0;
    virtual bool InShock() = 0;
    virtual bool IsDestroyed() = 0;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    virtual bool IsActive() const = 0;
    virtual float GetSpeedometer() = 0;
    virtual float GetSpeed() = 0;
    virtual void SetSpeed(float speed) = 0;
    virtual float GetAbsoluteSpeed() = 0;
    virtual bool IsGlareOn(int glare) = 0;
    virtual void GlareOn(int glare) = 0; // TODO "ID" enum
    virtual void GlareOff(int glare) = 0;
    virtual bool IsCollidingWithSoftBarrier() = 0;
    virtual IVehicleAI *GetAIVehiclePtr() = 0;
    virtual float GetSlipAngle() = 0;
    virtual UMath::Vector3 &GetLocalVelocity() = 0;
    virtual void ComputeHeading(UMath::Vector3 *v) = 0;
    virtual bool IsAnimating() = 0;
    virtual void SetAnimating(bool animate) = 0;
    virtual bool IsOffWorld() = 0;
    virtual struct FECustomizationRecord *GetCustomizations() = 0;
    virtual Physics::Tunings *GetTunings() = 0;
    virtual void SetTunings(const Physics::Tunings &tunings) = 0;
    virtual bool GetPerformance(struct Performance &performance) = 0;
    virtual const char *GetCacheName() = 0;
};

#endif
