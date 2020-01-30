#pragma once

#include "mgpch.h"

#include "MyGE/Core.h"
#include "MyGE/Events/Event.h"


namespace MyGE {

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& _Title = "My Game Engine", unsigned int _Width = 1280, unsigned int _Height = 720)
            : Title(_Title), Width(_Width), Height(_Height)
        {
        }
    };

    // Interface representng a desktop system based Window
    class MYGE_API Window
    {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void OnUpdate() = 0;

            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;

            // Window Attributes
            virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
            virtual void SetVSync(bool Enabled) = 0;
            virtual bool IsVSync() const = 0;

            static Window* Create(const WindowProps& Props = WindowProps());
    };
}