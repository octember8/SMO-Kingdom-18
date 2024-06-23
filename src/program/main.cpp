#include "lib.hpp"
#include "patches.hpp"
#include "logger/Logger.hpp"
#include "fs.h"
#include "helpers/InputHelper.h"
#include "helpers/PlayerHelper.h"
#include "ExceptionHandler.h"

#include <basis/seadRawPrint.h>
#include <prim/seadSafeString.h>
#include <resource/seadResourceMgr.h>
#include <filedevice/nin/seadNinSDFileDeviceNin.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <resource/seadArchiveRes.h>
#include <heap/seadHeapMgr.h>
#include <devenv/seadDebugFontMgrNvn.h>
#include <gfx/seadTextWriter.h>
#include <gfx/seadViewport.h>

#include <al/Library/File/FileLoader.h>
#include <al/Library/File/FileUtil.h>

#include <game/StageScene/StageScene.h>
#include <game/System/GameSystem.h>
#include <game/System/Application.h>
#include <game/HakoniwaSequence/HakoniwaSequence.h>
#include <game/GameData/GameDataFunction.h>

#include "rs/util.hpp"

HOOK_DEFINE_INLINE(WorldMovieResource) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x110) {
            *(char**)(ctx->X[0]+ctx->X[23]) = "content:/MovieData/World18.mp4";
        } else {
            *(char**)(ctx->X[0]+ctx->X[23]) =  (char*)ctx->X[8];
        }
    }
};

HOOK_DEFINE_INLINE(WorldMovieFirstTimeResource) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x110) {
            ctx->X[2] = (long)"PuzzlePicImage";
        } else {
            ctx->X[2] = (long)*(char**)(ctx->X[8]+8);
        }
    }
};

HOOK_DEFINE_INLINE(WorldMapRouteShuffle) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        if (ctx->X[23] == 0x11) {
            ctx->W[9] = 0x11;
        } else {
            if (ctx->X[23] == 0x12) {
                ctx->W[9] = 0;
            } else {
                ctx->W[9] = ctx->W[23] - ctx->W[9];
            }
        }
    }
};

bool checkEnableUnlockWorldSpecial3(al::LiveActor const* actor) {
        bool foundShine[4];
        GameDataHolderAccessor gdha = GameDataHolderAccessor(actor);
        GameDataFile const* gdf = gdha.mData->mGameDataFile;

        unsigned long unlockFlag = gdf->isUnlockedWorld(0x10);
        if ((unlockFlag & 1) != 0) {
            unlockFlag = gdf->isUnlockedWorld(0x11);
            if ((unlockFlag & 1) == 0) {
                foundShine[0] = false;
                int unlockShineNum = gdf->findUnlockShineNumCurrentWorld(foundShine);
                if (!foundShine[0]) {
                    return false;
                }
                int totalShines = gdf->getTotalPayShineNum();
                return unlockShineNum <= totalShines;
            }
        }
        return false;
}

HOOK_DEFINE_TRAMPOLINE(CheckEnableUnlockWorldSpecial2and3) {
    static bool Callback(al::LiveActor const* actor) {
        return checkEnableUnlockWorldSpecial3(actor) || Orig(actor);
    }
};

HOOK_DEFINE_TRAMPOLINE(MoonRockCheck) {
    static int Callback(GameDataFile* gdf, int index) {
        if (index == 0x11) {
            return 0;
        }
        return Orig(gdf, index);
    }
};

extern "C" void exl_main(void *x0, void *x1) {
    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    nn::os::SetUserExceptionHandler(exception_handler, nullptr, 0, nullptr);
    installExceptionStub();

    //Logger::instance().init(LOGGER_IP, 3080);

    runCodePatches();

    WorldMovieResource::InstallAtOffset(0x508D70);
    WorldMovieFirstTimeResource::InstallAtOffset(0x508D80);
    WorldMapRouteShuffle::InstallAtOffset(0x50168C);
    CheckEnableUnlockWorldSpecial2and3::InstallAtOffset(0x52a794);
    MoonRockCheck::InstallAtOffset(0x526a24);

}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}