#pragma once
#include "MyGe/Core.h"

namespace MyGE {

    class MYGE_API Input
    {
        // Methods
        public:
            inline static bool IsKeyPressed(int Keycode) { return s_Instance->IsKeyPressedImpl(Keycode); }
            inline static bool IsMouseButtonPressed(int Button) { return s_Instance->IsMouseButtonPressedImpl(Button); }
            inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
            inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
            inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
        protected:
            virtual bool IsKeyPressedImpl(int Keycode) = 0;
            virtual bool IsMouseButtonPressedImpl(int Button) = 0;
            virtual std::pair<float, float> GetMousePositionImpl() = 0;
            virtual float GetMouseXImpl() = 0;
            virtual float GetMouseYImpl() = 0;
        // Variables
        private:
            static Input* s_Instance;
    };
}