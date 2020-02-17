#pragma once

#include "MyGE/Window.h"
#include "MyGE/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace MyGE {

    class WindowsWindow : public Window
    {
        // Methods
        public:
            WindowsWindow(const WindowProps& Props);
            virtual ~WindowsWindow();

            virtual void OnUpdate() override;

            inline virtual unsigned int GetWidth() const override { return m_Data.Width; }
            inline virtual unsigned int GetHeight() const override { return m_Data.Height; }

            // Window Attributes
            inline virtual void SetEventCallback(const EventCallbackFn& Callback) override { m_Data.EventCallback = Callback; }
            virtual void SetVSync(bool Enabled) override;
            virtual bool IsVSync() const override;

            inline virtual void* GetNativeWindow() const override { return m_Window; }
        private:
            virtual void Init(const WindowProps& Props);
            virtual void Shutdown();

        // Variables
        private:
            GLFWwindow* m_Window;
            GraphicsContext* m_Context;

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