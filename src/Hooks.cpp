#include "Hooks.h"
namespace plugin {
    uint64_t (*orig_realdrawfn)(uint64_t t, float time) = nullptr;
    uint64_t RealDrawFunction(uint64_t t, float time)
    {
        float* seconds_since_last_frame_world = (float*)REL::Offset(0x31cc288).address();
        float* seconds_since_last_frame_real = (float*)REL::Offset(0x31cc28c).address();
        //auto before_draw = (void (*)(void))(REL::Offset(0x8f4270).address());
        auto after_draw = (void (*)(void))(REL::Offset(0x5fc210).address());
        
        /*
        REL::safe_write(REL::Offset(0x6460c5).address(), (uint8_t*)"\x90\x90",2);
        REL::safe_write(REL::Offset(0x646120).address(), (uint8_t*)"\x90\x90", 2);
        
        REL::safe_write(REL::Offset(0x6461e8).address(), (uint8_t*)"\x90\x90", 2);
        */
        //*seconds_since_last_frame_world /= 2.0;
        //*seconds_since_last_frame_real /= 2.0;
        orig_realdrawfn(t, time);
        uint8_t original_646393[6];
        memcpy(original_646393, (void*)REL::Offset(0x646393).address(), 6);
        REL::safe_write(REL::Offset(0x646393).address(), (uint8_t*)"\x48\xe9", 2);
        REL::safe_write(REL::Offset(0x6460d5).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x646153).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x64617e).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x64632e).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x646628).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x646766).address(), (uint8_t*)"\x90\x90", 2);
        REL::safe_write(REL::Offset(0x64676f).address(), (uint8_t*)"\xeb", 1);
        orig_realdrawfn(t, time);
        REL::safe_write(REL::Offset(0x646393).address(), (uint8_t*)original_646393, 6);
        REL::safe_write(REL::Offset(0x6460d5).address(), (uint8_t*)"\x75", 1);
        REL::safe_write(REL::Offset(0x646153).address(), (uint8_t*)"\x75", 1);
        REL::safe_write(REL::Offset(0x64632e).address(), (uint8_t*)"\x75", 1);
        REL::safe_write(REL::Offset(0x646628).address(), (uint8_t*)"\x75", 1);
        //REL::safe_write(REL::Offset(0x646120).address(), (uint8_t*)"\x74", 1);
        REL::safe_write(REL::Offset(0x64617e).address(), (uint8_t*)"\x74", 1);
        REL::safe_write(REL::Offset(0x646766).address(), (uint8_t*)"\x74\x09", 2);
        REL::safe_write(REL::Offset(0x64676f).address(), (uint8_t*)"\x74\x32", 2);
        /*
        
        REL::safe_write(REL::Offset(0x64617e).address(), (uint8_t*)"\xeb", 1);
        REL::safe_write(REL::Offset(0x646120).address(), (uint8_t*)"\xeb", 1);
        
        orig_realdrawfn(t, time);
        REL::safe_write(REL::Offset(0x64617e).address(), (uint8_t*)"\x74", 1);
        REL::safe_write(REL::Offset(0x646120).address(), (uint8_t*)"\x74", 1);
        
        
        REL::safe_write(REL::Offset(0x64617e).address(), (uint8_t*)"\x74\x30", 2);
        REL::safe_write(REL::Offset(0x6461e8).address(), (uint8_t*)"\x74\x18", 2);
        REL::safe_write(REL::Offset(0x6460c5).address(), (uint8_t*)"\x74\x07", 2);
        
        REL::safe_write(REL::Offset(0x646393).address(), (uint8_t*)original_646393, 6);
        */
        //before_draw();
        
        return 0;
    }
    void Hooks::installDrawHook() {
        
        orig_realdrawfn = (uint64_t(*)(uint64_t, float))REL::Offset(0x645ea0).address();
        DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)orig_realdrawfn,RealDrawFunction);
		DetourTransactionCommit();
    }
}  // namespace plugin
