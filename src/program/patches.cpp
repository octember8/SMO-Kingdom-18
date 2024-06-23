#include "patches.hpp"

namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

void worldSelectPatches() {
    //allocate actor arrays and create actor objs
    patch::CodePatcher p(0x50065C);
    p.WriteInst(inst::Movz(reg::W0, 0x90));
    p.Seek(0x500844);
    p.WriteInst(inst::CmpImmediate(reg::X26, 0x12));
    p.Seek(0x5008D0);
    p.WriteInst(inst::Movz(reg::W0, 0x90));
    p.Seek(0x50096C);
    p.WriteInst(inst::CmpImmediate(reg::X26, 0x12));
    //route size bitmask
    p.Seek(0x5008F4);
    p.WriteInst(inst::Movz(reg::W24, 0x2AC2B));

    //initialize layout actors
    p.Seek(0x5009FC);
    p.WriteInst(inst::Movz(reg::W21, 0x90));
    p.Seek(0x500B18);
    p.WriteInst(inst::CmpImmediate(reg::X21, 0x12));

    //fix index cycles
    p.Seek(0x5006BC);
    p.WriteInst(inst::AddImmediate(reg::W0, reg::W27, 0x13));
    p.Seek(0x5006C0);
    p.WriteInst(inst::Movz(reg::W1, 0x12));
    //allocate array
    p.Seek(0x500B20);
    p.WriteInst(inst::Movz(reg::W0, 0x48));

    //load actors
    p.Seek(0x500D98);
    p.WriteInst(inst::CmpImmediate(reg::X20, 0x90));
    p.Seek(0x500DE0);
    p.WriteInst(inst::CmpImmediate(reg::X20, 0x90));

    //limit num worlds
    p.Seek(0x501244);
    p.WriteInst(inst::CmpImmediate(reg::W0, 0x12));
    p.Seek(0x501248);
    p.WriteInst(inst::Movz(reg::W26, 0x12));

    //check all kingdoms unlocked
    p.Seek(0x5012DC);
    p.WriteInst(inst::CmpImmediate(reg::W8, 0x12));
    p.Seek(0x501320);
    p.WriteInst(inst::CmpImmediate(reg::W8, 0x12));

    //show/hide all actors
    p.Seek(0x5015FC);
    p.WriteInst(inst::CmpImmediate(reg::X20, 0x12));

    //kill
    p.Seek(0x5022B0);
    p.WriteInst(inst::CmpImmediate(reg::X20, 0x90));

}

void worldMoviePatch() {
    //allocate movie preview array and create textures
    patch::CodePatcher p(0x508D30);
    p.WriteInst(inst::Movz(reg::W0, 0x120));
    p.Seek(0x508DA8);
    p.WriteInst(inst::CmpImmediate(reg::X24, 0x12));   
}

void runCodePatches() {
    worldSelectPatches();
    worldMoviePatch();
}