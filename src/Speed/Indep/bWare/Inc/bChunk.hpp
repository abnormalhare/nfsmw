#ifndef BWARE_BCHUNK_H
#define BWARE_BCHUNK_H

#ifdef EA_PRAGMA_ONCE_SUPPORTED
#pragma once
#endif

#include "types.h"

class bChunk {
    // total size: 0x8
    unsigned int ID; // offset 0x0, size 0x4
    int Size;        // offset 0x4, size 0x4

  public:
    bChunk() {}

    bChunk(unsigned int id, int size) {
        this->ID = id;
        this->Size = size;
    }

    unsigned int GetID() {
        return this->ID;
    }

    BOOL GetSize() {
        return this->Size;
    }

    BOOL IsNestedChunk() {
        return this->GetID() < 0;
    }

    int IsDataChunk() {}

    int CountChildren() {
        /* anonymous block */ {
            int ret;
            /* anonymous block */ { struct bChunk *c; }
        }
    }

    char *GetData() {
        return reinterpret_cast<char *>(&this[1]);
    }

    char *GetAlignedData(int alignment_size) {
        return reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(this->GetData() + alignment_size - 1) & ~(alignment_size - 1));
    }

    int GetAlignedSize(int alignment_size) {
        return this->Size - (this->GetAlignedData(alignment_size) - this->GetData());
    }

    void VerifyAlignment(int alignment_size) {
        unsigned int *pdata;
    }

    bChunk *GetFirstChunk() {
        return &this[1];
    }

    bChunk *GetLastChunk() {
        return (bChunk *)((char *)this + this->Size) + 1;
    }

    bChunk *GetNext() {
        return this->GetLastChunk();
    }

    bChunk *GetLastChunk(struct bChunk *first_chunk, int sizeof_binary) {}
};

typedef int (*bChunkLoaderFunction)(struct bChunk *);

class bChunkLoader {
    // total size: 0x10
    struct bChunkLoader *Next;             // offset 0x0, size 0x4
    unsigned int ID;                       // offset 0x4, size 0x4
    bChunkLoaderFunction LoaderFunction;   // offset 0x8, size 0x4
    bChunkLoaderFunction UnloaderFunction; // offset 0xC, size 0x4

  public:
    bChunkLoaderFunction GetLoaderFunction() {
        return this->LoaderFunction;
    }

    bChunkLoaderFunction GetUnloaderFunction() {
        return this->UnloaderFunction;
    }

    unsigned int GetHash(unsigned int id) {}
};

class bChunkCarpHeader {
    // total size: 0x10
    int mCrpSize;                          // offset 0x0, size 0x4
    int mSectionNumber;                    // offset 0x4, size 0x4
    int mFlags;                            // offset 0x8, size 0x4
    struct bChunkCarpHeader *mLastAddress; // offset 0xC, size 0x4

  public:
    bChunkCarpHeader() {}

    ~bChunkCarpHeader() {}

    int GetCarpSize() {
        return mCrpSize;
    }

    int GetSectionNumber() {
        return mSectionNumber;
    }

    int GetFlags() {
        return mFlags;
    }

    bool IsResolved() {}

    void SetResolved() {}

    void SetNotResolved() {}

    bChunkCarpHeader *GetLastAddress() {
        return this->mLastAddress;
    }

    void SetLastAddress(bChunkCarpHeader *address) {
        this->mLastAddress = address;
    }
};

#endif
