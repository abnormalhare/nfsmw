#ifndef PHYSICS_BEHAVIORS_RBTRACTOR_H
#define PHYSICS_BEHAVIORS_RBTRACTOR_H

#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

#include "RBVehicle.h"
#include "Speed/Indep/Src/Interfaces/SimActivities/IVehicleCache.h"
#include "Speed/Indep/Src/Interfaces/Simables/IArticulatedVehicle.h"
#include "Speed/Indep/Src/Interfaces/Simables/IINput.h"

// total size: 0x1E4
class RBTractor : public RBVehicle, public IArticulatedVehicle, public IVehicleCache {
  public:
    static Behavior *Construct(const BehaviorParams &params);

    // Methods
    RBTractor(const BehaviorParams &bp, const RBComplexParams &params);
    void UpdateTrailer(float dT);

    // Overrides
    // IUnknown
    override virtual ~RBTractor();

    // IRigidBody
    override virtual void PlaceObject(const UMath::Matrix4 &orientMat, const UMath::Vector3 &initPos);

    // RigidBody
    override virtual void ModifyCollision(const RigidBody &other, const Dynamics::Collision::Plane &plane, Dynamics::Collision::Moment &myMoment);
    override virtual bool CanCollideWith(const struct RigidBody &other) const;

    // Behavior
    override virtual void OnBehaviorChange(const UCrc32 &mechanic);
    override virtual void OnOwnerDetached(IAttachable *pOther);

    // IVehicleCache
    override virtual eVehicleCacheResult OnQueryVehicleCache(const IVehicle *removethis, const IVehicleCache *whosasking) const;
    override virtual void OnRemovedVehicleCache(IVehicle *ivehicle);

    // IArticulatedVehicle
    override virtual void SetHitch(bool hitched);
    override virtual bool Pose();

    // ITaskable
    override bool OnTask(HSIMTASK htask, float dT);

    // Inline overrides
    // IArticulatedVehicle
    override virtual IVehicle *GetTrailer() const {
        return mTrailer;
    }

    override virtual bool IsHitched() const {
        return mHitched;
    }

    // IVehicleCache
    override virtual const char *GetCacheName() const {
        return "RBTractor";
    }

  private:
    IVehicle *mTrailer;              // offset 0x1B8, size 0x4
    IInput *mIInput;                 // offset 0x1BC, size 0x4
    HSIMTASK mTrailerTask;           // offset 0x1C0, size 0x4
    bool mHitched;                   // offset 0x1C4, size 0x1
    UMath::Vector3 m5thWheel;        // offset 0x1C8, size 0xC
    UMath::Vector3 mTrailer5thWheel; // offset 0x1D4, size 0xC
    float mDetachTimer;              // offset 0x1E0, size 0x4
};

// total size: 0x1A4
class RBTrailer : public RBVehicle {
  public:
    static Behavior *Construct(const BehaviorParams &params);

    RBTrailer(const BehaviorParams &bp, const RBComplexParams &params);

    // Overrides
    // RigidBody
    override virtual void ModifyCollision(const RigidBody &other, const Dynamics::Collision::Plane &plane, Dynamics::Collision::Moment &myMoment);
};

#endif
