#pragma once

#include "MyGE/Layer.h"

#include "MyGE/Events/ApplicationEvent.h"
#include "MyGE/Events/KeyEvent.h"
#include "MyGE/Events/MouseEvent.h"


namespace MyGE {

    class MYGE_API ImGuiLayer : public Layer
    {
        // Methods
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnImGuiRender() override;

            void Begin();
            void End();
    };
}