#include "Hooks.h"
namespace plugin {
    void Hooks::Draw(uint64_t arg1) {
        origDraw(arg1);
    }

    void Hooks::installDrawHook() {
        
        
        std::uintptr_t hook = REL::Offset(0x646937).address();
        auto& trampoline = SKSE::GetTrampoline();
        trampoline.create(64);
        origDraw = trampoline.write_call<5>(hook, Draw);
        logger::info("Draw hook installed at address 0x{:X}",REL::Offset(0x646937).address());
    }
}  // namespace plugin
