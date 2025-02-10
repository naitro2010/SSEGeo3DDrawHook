#pragma once

namespace plugin {
    class Hooks {
        private:
            static void Draw(uint64_t arg1,uint32_t arg2,uint8_t arg3)
            static inline REL::Relocation<decltype(Draw)> origDraw;

        public:
            static void installDrawHook();
    };

}  // namespace plugin