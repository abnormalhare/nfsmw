#ifndef WORLD_CARRENDER_H
#define WORLD_CARRENDER_H

#include "Speed/Indep/Src/Ecstasy/Ecstasy.hpp"
#include "Speed/Indep/bWare/Inc/bMath.hpp"
#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

enum CarEffectPosition {
    CARFXPOS_NONE,
    CARFXPOS_FRONT_TIRES,
    CARFXPOS_REAR_TIRES,
    CARFXPOS_LEFT_TIRES,
    CARFXPOS_RIGHT_TIRES,
    CARFXPOS_TIRE_FL,
    CARFXPOS_TIRE_FR,
    CARFXPOS_TIRE_RR,
    CARFXPOS_TIRE_RL,
    CARFXPOS_ENGINE,
    CARFXPOS_EXHAUST,
    CARFXPOS_RADIATOR,
    CARFXPOS_WINDSHIELD,
    CARFXPOS_WINDOW_REAR,
    CARFXPOS_WINDOW_LEFT_FRONT,
    CARFXPOS_WINDOW_LEFT_REAR,
    CARFXPOS_WINDOW_RIGHT_FRONT,
    CARFXPOS_WINDOW_RIGHT_REAR,
    CARFXPOS_HEADLIGHT,
    CARFXPOS_HEADLIGHT_LEFT,
    CARFXPOS_HEADLIGHT_RIGHT,
    CARFXPOS_BRAKELIGHT,
    CARFXPOS_BRAKELIGHT_LEFT,
    CARFXPOS_BRAKELIGHT_RIGHT,
    CARFXPOS_SIDE_MIRROR_LEFT,
    CARFXPOS_SIDE_MIRROR_RIGHT,
    CARFXPOS_LICENSE_PLATE_FRONT,
    CARFXPOS_LICENSE_PLATE_REAR,
    NUM_CARFXPOS,
};

enum eCullableCarParts {
    CULLABLE_CAR_PART_TIRE_FL,
    CULLABLE_CAR_PART_TIRE_FR,
    CULLABLE_CAR_PART_TIRE_RR,
    CULLABLE_CAR_PART_TIRE_RL,
    CULLABLE_CAR_PART_BRAKE_FL,
    CULLABLE_CAR_PART_BRAKE_FR,
    CULLABLE_CAR_PART_BRAKE_RR,
    CULLABLE_CAR_PART_BRAKE_RL,
    CULLABLE_CAR_PART_SIDE_FRONT,
    CULLABLE_CAR_PART_SIDE_REAR,
    CULLABLE_CAR_PART_UNDERNEATH,
    NUM_CULLABLE_CAR_PARTS,
};
enum eCullingPolarity {
    CULLING_POLARITY_ANY_VISIBLE,
    CULLING_POLARITY_ALL_MUST_BE_VISIBLE,
};

struct CarFXPosInfo {
    // total size: 0x14
    unsigned int position_marker_hashes[4]; // offset 0x0, size 0x10
    unsigned char marker_count; // offset 0x10, size 0x1
};

class CarPartCullingPlaneInfo {
public:
    CarPartCullingPlaneInfo() {

    }

    // total size: 0x4C
    eCullableCarParts Type; // offset 0x0, size 0x4
    char *Name; // offset 0x4, size 0x4
    eCullingPolarity Polarity; // offset 0x8, size 0x4
    int NumPlanes; // offset 0xC, size 0x4
    bVector3 Normal[3]; // offset 0x10, size 0x30
    float NormalDistance[3]; // offset 0x40, size 0xC
};

class CarPartInfo {
public:
    CarPartInfo() {

    }

    // total size: 0x1C
    struct bVector3 Position; // offset 0x0, size 0x10
    int NumCulledNotVisible; // offset 0x10, size 0x4
    int NumCulledVisible; // offset 0x14, size 0x4
    bool IsVisible; // offset 0x18, size 0x1
};

class CarPartCuller {
public:
    void InitPart(eCullableCarParts type, const bVector3 *position);
    void RenderPart(eCullableCarParts type, eView *view, const bMatrix4 *local_world, unsigned short stang);
    void CullParts(bVector3 *camera_eye, unsigned short stang);

    CarPartCuller() {

    }

    // unsolved
    bool IsPartVisible(eCullableCarParts types) {
        return true;
    }

private:
    // total size: 0x134
    struct CarPartInfo CarPartInfoTable[11]; // offset 0x0, size 0x134
};

bool GetNumCarEffectMarkerHashes(CarEffectPosition fx_pos, int &count_out);
const unsigned int *GetCarEffectMarkerHashes(CarEffectPosition fx_pos);
void InitCarEffects();
void CloseCarEffects();

#endif
