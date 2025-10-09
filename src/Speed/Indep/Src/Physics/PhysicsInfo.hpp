#ifndef PHYSICS_PHYSICSINFO_H
#define PHYSICS_PHYSICSINFO_H

#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

#include "PhysicsTunings.h"
#include "PhysicsTypes.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/chassis.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/engine.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/induction.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/nos.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/pvehicle.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/tires.h"
#include "Speed/Indep/Src/Generated/AttribSys/Classes/transmission.h"

namespace Physics {
namespace Info {

enum eInductionType {
    INDUCTION_SUPER_CHARGER = 2,
    INDUCTION_TURBO_CHARGER = 1,
    INDUCTION_NONE = 0,
};

struct Performance {
    Performance(float topspeed, float handling, float accel) {
        TopSpeed = topspeed;
        Handling = handling;
        Acceleration = accel;
    }
    void Default();

    float TopSpeed;
    float Handling;
    float Acceleration;
};

float AerodynamicDownforce(const Attrib::Gen::chassis &chassis, const float speed);
float EngineInertia(const Attrib::Gen::engine &engine, const bool loaded);
eInductionType InductionType(const Attrib::Gen::induction &induction);
float NosBoost(const Attrib::Gen::nos &nos, const Tunings *tunings);
float NosCapacity(const Attrib::Gen::nos &nos, const Tunings *tunings);
float InductionRPM(const Attrib::Gen::engine &engine, const Attrib::Gen::induction &induction, const Tunings *tunings);
float InductionBoost(const Attrib::Gen::engine &engine, const Attrib::Gen::induction &induction, float rpm, float spool, const Tunings *tunings,
                     float *psi);
float WheelDiameter(const Attrib::Gen::tires &tires, bool front);
float Speedometer(const Attrib::Gen::transmission &transmission, const Attrib::Gen::engine &engine, const Attrib::Gen::tires &tires, float rpm,
                  GearID gear, const Tunings *tunings);
float Torque(const Attrib::Gen::engine &engine, float rpm);
bool ShiftPoints(const Attrib::Gen::transmission &transmission, const Attrib::Gen::engine &engine, const Attrib::Gen::induction &induction,
                 float *shift_up, float *shift_down, unsigned int numpts);
bool HasRunflatTires(const Attrib::Gen::pvehicle &pvehicle);
bool EstimatePerformance(Performance &perf);

extern Performance PerformanceWeights[7];

} // namespace Info
} // namespace Physics

#endif
