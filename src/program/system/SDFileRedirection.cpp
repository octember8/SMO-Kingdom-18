#include "system/SDFileRedirection.h"

#include <lib.hpp>

#include <filedevice/nin/seadNinSDFileDeviceNin.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <nn/fs.h>
#include <resource/seadArchiveRes.h>

#include "al/Library/File/FileLoader.h"

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) {
    static void Callback(sead::FileDeviceMgr* thisPtr) {
        Orig(thisPtr);

        thisPtr->mMountedSd = nn::fs::MountSdCardForDebug("sd");
        sead::NinSDFileDevice* sdFileDevice = new sead::NinSDFileDevice();
        thisPtr->mount(sdFileDevice);
    }
};

HOOK_DEFINE_TRAMPOLINE(RedirectFileDevice) {
    static sead::FileDevice* Callback(sead::FileDeviceMgr* thisPtr, sead::SafeString& path,
                                      sead::BufferedSafeString* pathNoDrive) {
        sead::FixedSafeString<32> driveName;
        sead::FileDevice* device;

        // Logger::log("Loading path=%s, pathNoDrive=%s\n", path.cstr(), pathNoDrive ? pathNoDrive->cstr() : "null");

        if (!sead::Path::getDriveName(&driveName, path)) {
            device = thisPtr->findDevice("sd");

            if (!device || !device->isExistFile(path)) {
                device = thisPtr->getDefaultFileDevice();
            } else {
                // Logger::log("Found Replacement File on SD! Path: %s\n", path.cstr());
            }
        } else
            device = thisPtr->findDevice(driveName);

        if (!device)
            return nullptr;

        if (pathNoDrive != nullptr)
            sead::Path::getPathExceptDrive(pathNoDrive, path);

        return device;
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderLoadArc) {
    static sead::ArchiveRes* Callback(al::FileLoader* thisPtr, sead::SafeString& path, const char* ext,
                                      sead::FileDevice* device) {
        // Logger::log("Path: %s\n", path.cstr());

        sead::FileDevice* sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");
        if (sdFileDevice && sdFileDevice->isExistFile(path)) {
            // Logger::log("Found Replacement File on SD! Path: %s\n", path.cstr());
            device = sdFileDevice;
        }

        return Orig(thisPtr, path, ext, device);
    }
};

HOOK_DEFINE_TRAMPOLINE(FileLoaderIsExistFile) {
    static bool Callback(al::FileLoader* thisPtr, sead::SafeString& path, sead::FileDevice* device) {

        sead::FileDevice* sdFileDevice = sead::FileDeviceMgr::instance()->findDevice("sd");
        if (sdFileDevice && sdFileDevice->isExistFile(path)) {
            // Logger::log("Found Replacement File on SD! Path: %s\n", path.cstr());
            device = sdFileDevice;
        }

        return Orig(thisPtr, path, device);
    }
};

void installSDFileRedirection() {
    RedirectFileDevice::InstallAtOffset(0x76CFE0);
    FileLoaderLoadArc::InstallAtOffset(0xA5EF64);
    CreateFileDeviceMgr::InstallAtOffset(0x76C8D4);
    FileLoaderIsExistFile::InstallAtOffset(0xA5ED28);
}
