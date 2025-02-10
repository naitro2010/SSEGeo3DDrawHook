#pragma once
#include <stdint.h>
namespace plugin {
    class Hooks {
        private:
            static void Draw(uint64_t arg1);
            static inline REL::Relocation<decltype(Draw)> origDraw;

        public:
            static void installDrawHook();
    };

}  // namespace plugin