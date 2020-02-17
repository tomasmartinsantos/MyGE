#pragma once
#include "MyGE/Renderer/GraphicsContext.h"

struct GLFWwindow;


namespace MyGE {

    class OpenGLContext : public GraphicsContext
    {
        // Methods
        public:
            OpenGLContext(GLFWwindow* WindowHandle);

            virtual void Init() override;
            virtual void SwapBuffers() override;

        // Variables
        private:
            GLFWwindow* m_WindowHandle;
    };
}