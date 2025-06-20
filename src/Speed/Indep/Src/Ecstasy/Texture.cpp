#include "./Texture.hpp"
#include "./eStreamingPack.hpp"
#include "Speed/GameCube/Src/Ecstasy/TextureInfoPlat.hpp"
#include "Speed/Indep/Src/Misc/GameFlow.hpp"
#include "Speed/Indep/Src/Misc/ResourceLoader.hpp"
#include "Speed/Indep/Src/Misc/Timer.hpp"
#include "Speed/Indep/bWare/Inc/bList.hpp"
#include "Speed/Indep/bWare/Inc/bMath.hpp"
#include "Speed/Indep/bWare/Inc/bSlotPool.hpp"
#include "version.h"

SlotPool *TexturePackSlotPool;
BOOL DuplicateTextureWarningEnabled;
bTList<TextureVRAMDataHeader> TextureVRAMDataHeaderList;
bTList<TextureAnimPack> TextureAnimPackList;

void eInitTextures(void) {
    TexturePackSlotPool = bNewSlotPool(bMax(28, 32), 128, "TexturePackSlotPool", 0);
}

void SetDuplicateTextureWarning(BOOL enabled) {
    DuplicateTextureWarningEnabled = enabled;
}

TextureVRAMDataHeader *FindVRAMData(unsigned int filename_hash) {
    for (TextureVRAMDataHeader *vram_header = TextureVRAMDataHeaderList.GetHead(); vram_header != TextureVRAMDataHeaderList.EndOfList();
         vram_header = vram_header->GetNext()) {
        if (vram_header->FilenameHash == filename_hash) {
            return vram_header;
        }
    }
    return nullptr;
}

TexturePackHeader *InternalLoadTexturePackHeaderChunks(bChunk *chunk) {}

void InternalUnloadTexturePackHeaderChunks(bChunk *chunk) {}

TextureVRAMDataHeader *InternalLoadVRAMDataChunks(bChunk *chunk) {
    bChunk *vram_header_chunk;
    bChunk *null_chunk;
    bChunk *vram_data_chunk;
    TextureVRAMDataHeader *vram_header; // r29
}

TextureInfo *eCreateTextureInfo() {
    TextureInfo *texture_info = new TextureInfo();
    TextureInfoPlatInfo *plat_info = new TextureInfoPlatInfo();
    texture_info->SetPlatInfo(plat_info);
    return texture_info;
}

void eDestroyTextureInfo(struct TextureInfo *texture_info) {
    TextureInfoPlatInfo *plat_info = texture_info->GetPlatInfo();
    if (plat_info != nullptr) {
        delete plat_info;
    }
    if (texture_info != nullptr) {
        delete texture_info;
    }
}

TextureAnimPack::TextureAnimPack(TexturePack *parent_texture_pack, TextureAnim *texture_anim_table, TextureAnimEntry *texture_anim_entry_table,
                                 int num_anims, int num_anim_entries) {
    this->ParentTexturePack = parent_texture_pack;
    this->TextureAnimTable = texture_anim_table;
    this->TextureAnimEntryTable = texture_anim_entry_table;
    this->NumTextureAnims = num_anims;
    this->NumTextureAnimEntries = num_anim_entries;

    TextureAnimEntry *anim_entry = texture_anim_entry_table;
    for (int i = 0; i < num_anims; i++) {
        TextureAnim *texture_anim = &this->TextureAnimTable[i];
        texture_anim->TextureAnimTable = anim_entry;
        anim_entry += texture_anim->NumFrames;
    }
    TextureAnimPackList.AddTail(this);
}

TextureAnimPack::~TextureAnimPack() {
    for (int i = 0; i < this->NumTextureAnims; i++) {
        TextureAnim *texture_anim = &this->TextureAnimTable[i];
        TextureAnimEntry *base_entry = texture_anim->TextureAnimTable;
        int num_frames = texture_anim->NumFrames;

        for (int j = 0; j < num_frames; j++) {
            TextureAnimEntry *frame_entry = &base_entry[j];
            if (frame_entry->pTextureInfo != nullptr) {
                frame_entry->pTextureInfo->ReleaseAnimData(frame_entry->pPlatAnimData);
            }
        }
    }
    this->Remove();
}

void TextureAnimPack::InitAnims() {
    TextureAnim *texture_anim = this->TextureAnimTable;
    TextureAnimEntry *anim_entry;
    int num_anims = this->NumTextureAnims;

    for (int i = 0; i < num_anims; i++) {
        TextureAnimEntry *base_entry = texture_anim->TextureAnimTable;
        int num_frames = texture_anim->NumFrames;
        BOOL valid = true;
        for (int j = 0; j < num_frames; j++) {
            TextureAnimEntry *frame_entry = &base_entry[j];
            TextureInfo *texture_info = this->ParentTexturePack->GetLoadedTexture(frame_entry->NameHash);
            if (texture_info != nullptr) {
                frame_entry->pTextureInfo = texture_info;
                frame_entry->pPlatAnimData = texture_info->CreateAnimData();
            } else {
                frame_entry->pTextureInfo = nullptr;
                frame_entry->pPlatAnimData = nullptr;
                valid = false;
            }
        }
        texture_anim->Valid = valid;
        texture_anim->CurrentFrame = 0;
        texture_anim++;
    }
}

// UNSOLVED
void UpdateTextureAnimations() {
    // ProfileNode profile_node;

    if ((TheGameFlowManager.CurrentGameFlowState != GAMEFLOW_STATE_IN_FRONTEND) && (WorldTimeElapsed == 0.0f)) {
        return;
    }

    float world_time = WorldTimeFrames * (1.0f / REFRESH_RATE); // f29
    float real_time = RealTimeFrames * (1.0f / REFRESH_RATE);   // f30
    int tweak_fps;

    for (TextureAnimPack *anim_pack /* r26 */ = TextureAnimPackList.GetHead(); anim_pack != TextureAnimPackList.EndOfList();
         anim_pack = anim_pack->GetNext()) {
        TextureAnim *texture_anim = anim_pack->TextureAnimTable; // r8
        int num_anims = anim_pack->NumTextureAnims;              // r23

        for (int i /* r9 */ = 0; i < num_anims; i++) {
            float current_time;                       // f13
            int num_frames = texture_anim->NumFrames; // r30
            int fps = texture_anim->FramesPerSecond;  // r0
            int current_frame;                        // r28

            if (!texture_anim->Valid) {
                continue;
            }
            TextureAnimEntry *base_entry = texture_anim->TextureAnimTable; // r27
            TextureAnimEntry *current_entry = &base_entry[i];              // r31
            current_time = texture_anim->TimeBase == 1 ? real_time : world_time;
            current_frame = fps * current_time;
            current_frame -= (current_frame / num_frames) * num_frames;

            if (current_frame == texture_anim->CurrentFrame) {
                continue;
            }
            texture_anim->CurrentFrame = current_frame;
            for (int j /* r29 */ = 0; j < num_frames; j++) {
                void *new_anim_data = current_entry[j].pPlatAnimData;
                TextureInfo *texture_info = current_entry[j].pTextureInfo;
                texture_info->SetAnimData(new_anim_data);
            }
        }
    }

    // TODO ProfileNode and IsInFrontEnd stuff
}

void TextureLoadedStreamingEntryCallback(struct bChunk *chunk /* r29 */, struct eStreamingEntry *streaming_entry /* r4 */,
                                         struct eStreamingPack *streaming_pack /* r5 */) {
    // struct ProfileNode profile_node;
    TexturePackHeader *texture_pack_header; // r9
    TexturePack *texture_pack;              // r28
    unsigned char *pdata;
    TextureInfoPlatInfo *plat_info; // r30
    TextureInfo *texture_info;      // r31
    int data_start;                 // r5
    int data_end;                   // r6
    int data_size;

    // inline struct ProfileNode * ProfileNode::ProfileNode(struct ProfileNode * const this, const char * section_name, int categories, struct
    // ProfileNode * const this, const char * section_name, int categories) {} Range: 0x800FCF3C -> 0x800FCF3C
    // inline void TextureInfo::EndianSwap(struct TextureInfo *const this, struct TextureInfo *const this /* r31 */) {
    //     // Inlines
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(unsigned int *value, unsigned int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(unsigned int *value, unsigned int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(unsigned int *value, unsigned int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(int *value, int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(int *value, int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(int *value, int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(int *value, int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(int *value, int *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    //     // Range: 0x800FCF3C -> 0x800FCF3C
    //     inline void bPlatEndianSwap(short *value, short *value) {}
    // }
}

void eLoadStreamingTexture(unsigned int *name_hash_table, int num_hashes, void (*callback)(void *), void *param0, int memory_pool_num) {
    StreamingTexturePackLoader.LoadStreamingEntry(name_hash_table, num_hashes, callback, param0, memory_pool_num);
}

void eUnloadStreamingTexture(unsigned int *name_hash_table, int num_hashes) {
    StreamingTexturePackLoader.UnloadStreamingEntry(name_hash_table, num_hashes);
}

void eWaitForStreamingTexturePackLoading(const char *filename) {
    StreamingTexturePackLoader.WaitForLoadingToFinish(filename);
}

void eUnloadAllStreamingTextures(const char *filename) {
    StreamingTexturePackLoader.UnloadAllStreamingEntries(filename);
}

int eIsStreamingTexturePackLoaded(const char *filename) {
    return StreamingTexturePackLoader.GetLoadedStreamingPack(filename) != nullptr;
}

int eLoadStreamingTexturePack(const char *filename, void (*callback_function)(void *), void *callback_param, int memory_pool_num) {
    eStreamingPack *streaming_pack;

    streaming_pack = StreamingTexturePackLoader.CreateStreamingPack(filename, callback_function, callback_param, memory_pool_num);
    return streaming_pack != nullptr;
}

void TextureLoadingStreamingPackPhase1(eStreamingPackHeaderLoadingInfoPhase1 *loading_info /* r27 */) {
    bChunk *list_chunk;     // r28
    bChunk *null_chunk;     // r30
    bChunk *header_chunk;   // r29
    int header_chunks_size; // r9

    list_chunk = loading_info->TempHeaderChunks;
    EndianSwapChunkHeader(list_chunk);
    header_chunk = list_chunk->GetFirstChunk();
    EndianSwapChunkHeader(header_chunk);
    null_chunk = header_chunk->GetNext();
    EndianSwapChunkHeader(null_chunk);
    // TODO wrong
    header_chunks_size = header_chunk[1].GetSize();
    loading_info->NextLoadAmount = header_chunks_size + 16;
    loading_info->NextLoadPosition = (size_t)null_chunk - (size_t)list_chunk;
}

void TextureLoadingStreamingPackPhase2(eStreamingPackHeaderLoadingInfoPhase2 *loading_info) {
    bChunk *header_chunks = loading_info->HeaderChunks;
    if (loading_info->HeaderChunksMemCopied == 0) {
        EndianSwapChunkHeader(header_chunks);
    }
    EndianSwapChunkHeadersRecursive(header_chunks->GetFirstChunk(), header_chunks->GetLastChunk());

    TexturePackHeader *texture_pack_header = InternalLoadTexturePackHeaderChunks(header_chunks);
    loading_info->StreamingEntryTable = texture_pack_header->TextureStreamEntryTable;
    loading_info->StreamingEntryNumEntries = texture_pack_header->pTexturePack->GetNumTextures();
    loading_info->pTexturePackHeader = texture_pack_header;
}

void eUnloadStreamingTexturePack(const char *filename) {
    StreamingTexturePackLoader.DeleteStreamingPack(filename);
}

void TextureUnloadingStreamingPack(eStreamingPack *streaming_pack) {
    InternalUnloadTexturePackHeaderChunks(streaming_pack->HeaderChunks);
}

void MaybePrintUnusedTextures() {}
