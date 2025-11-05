#include "./CarRender.hpp"
#include "Speed/Indep/Src/Ecstasy/eMath.hpp"
#include "Speed/Indep/Src/Misc/GameFlow.hpp"
#include "Speed/Indep/Src/Misc/Profiler.hpp"
#include "Speed/Indep/bWare/Inc/bMath.hpp"
#include "dolphin/mtx/GeoTypes.h"

static const CarFXPosInfo FXMarkerNameHashMappings[28] = {
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0, 0, 0, 0 },
        255,
    },
    {
        { 0xA5B28001, 0xBCF8A18B, 0xBD7CF15E, 0 },
        3,
    },
};

bool GetNumCarEffectMarkerHashes(CarEffectPosition fx_pos, int &count_out) {
    bool position_marker_based_fxpos = false;

    count_out = int(position_marker_based_fxpos);
    if (FXMarkerNameHashMappings[fx_pos].marker_count != 0xFF) {
        count_out = FXMarkerNameHashMappings[fx_pos].marker_count;
        position_marker_based_fxpos = true;
    }

    return position_marker_based_fxpos;
}

const unsigned int *GetCarEffectMarkerHashes(CarEffectPosition fx_pos) {
    return FXMarkerNameHashMappings[fx_pos].position_marker_hashes;
}

CarPartCullingPlaneInfo CarPartCullingPlaneInfoTable[11];

void CarPartCuller::InitPart(eCullableCarParts type, const bVector3 *position) {
    CarPartCullingPlaneInfo *plane_info = &CarPartCullingPlaneInfoTable[type];
    CarPartInfo *part_info = &this->CarPartInfoTable[type];

    for (int n = 0; n < plane_info->NumPlanes; n++) {
        if (bAbs(1.0f - bLength(plane_info->Normal[n])) > 0.01f) {
            bNormalize(&plane_info->Normal[n], &plane_info->Normal[n]);
        }
    }

    part_info->Position = *position;
}

void CarPartCuller::CullParts(bVector3 *camera_eye, unsigned short stang) {
    ProfileNode profile_node;
    bVector3 Modcamera_eye = *camera_eye;
    bVector3 *unModcamera_eyeP;
    bMatrix4 turnMat;

    if (stang != 0) {
        PSMTX44Identity(*reinterpret_cast<Mtx44 *>(&turnMat));
        eRotateZ(&turnMat, &turnMat, -stang);
        eMulVector(&Modcamera_eye, &turnMat, camera_eye);
    }

    for (eCullableCarParts type = CULLABLE_CAR_PART_TIRE_FL; type < NUM_CULLABLE_CAR_PARTS;) {
        bool visible = true;
        CarPartCullingPlaneInfo *plane_info = &CarPartCullingPlaneInfoTable[type];
        CarPartInfo *part_info = &this->CarPartInfoTable[type];
        float omodifier = plane_info->NormalDistance[0];
        float modifier;

        if (IsGameFlowInFrontEnd()) {
            // decide whether to use camera_eye or Modcamera_eye
            if (type <= 1) {
                if (stang > 0x8000) {
                    
                }
            }
        }
        
    }
}
