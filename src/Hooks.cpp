#include "Hooks.h"
namespace plugin {
    void Hooks::Draw(uint64_t arg1,uint32_t arg2,uint8_t arg3) {
        origDraw(arg1,arg2,arg3);
        origDraw(arg1,arg2,arg3);
    }

    void Hooks::installDrawHook() {
        
        
        std::uintptr_t hook = REL::Offset(0x64447d).address();
        auto& trampoline = SKSE::GetTrampoline();
        trampoline.create(64);
        origDraw = trampoline.write_call<5>(hook, Draw);
        logger::info("Draw hook installed at address 0x{:X}",REL::Offset(0x64447d).address());
    }
}  // namespace plugin
