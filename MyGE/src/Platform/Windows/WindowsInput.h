#pragma once
#include "MyGE/Input.h"


namespace MyGE {

    class MYGE_API WindowsInput : public Input
    {
        // Methods
        protected:
            virtual bool IsKeyPressedImpl(int Keycode) override;
            virtual bool IsMouseButtonPressedImpl(int Button) override;
            virtual std::pair<float, float> GetMousePositionImpl() override;
            virtual float GetMouseXImpl() override;
            virtual float GetMouseYImpl() override;
    };
}