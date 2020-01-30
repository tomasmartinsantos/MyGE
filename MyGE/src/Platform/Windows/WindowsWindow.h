#pragma once

#include "MyGE/Window.h"

#include "GLFW/glfw3.h"


namespace MyGE {

    class WindowsWindow : public Window
    {
        // Methods
        public:
            WindowsWindow(const WindowProps& Props);
            virtual ~WindowsWindow();

            void OnUpdate() override;

            inline unsigned int GetWidth() const override { return m_Data.Width; }
            inline unsigned int GetHeight() const override { return m_Data.Height; }

            // Window Attributes
            inline void SetEventCallback(const EventCallbackFn& Callback) override { m_Data.EventCallback = Callback; }
            void SetVSync(bool Enabled) override;
            bool IsVSync() const override;
        private:
            virtual void Init(const WindowProps& Props);
            virtual void Shutdown();

        // Variables
        private:
            GLFWwindow* m_Window;

            struct WindowData
            {
                std::string Title;
                unsigned int Width;
                unsigned int Height;
                bool VSync;
                EventCallbackFn EventCallback;
            };

            WindowData m_Data;
    };
}