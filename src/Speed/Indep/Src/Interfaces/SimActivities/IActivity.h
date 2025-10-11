#ifndef INTTERFACES_SIMACTIVITIES_IACTIVITY_H
#define INTTERFACES_SIMACTIVITIES_IACTIVITY_H

#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

#include "types.h"

#include "Speed/Indep/Libs/Support/Utility/UCOM.h"
#include "Speed/Indep/Libs/Support/Utility/UCollections.h"
#include "Speed/Indep/Src/Sim/SimTypes.h"

struct HACTIVITY__ {
    // total size: 0x4
    int unused; // offset 0x0, size 0x4
};

typedef HACTIVITY__ *HACTIVITY;

namespace Sim {

class IActivity : public UTL::COM::IUnknown,
                  public UTL::COM::Factory<Param, IActivity, UCrc32>,
                  public UTL::Collections::Instanceable<HACTIVITY, IActivity, 40> {
  public:
    static HINTERFACE _IHandle() {
        return (HINTERFACE)_IHandle;
    }

    IActivity(UTL::COM::Object *owner) : UTL::COM::IUnknown(owner, _IHandle()) {}

    virtual ~IActivity() {}
};

}; // namespace Sim

#endif
