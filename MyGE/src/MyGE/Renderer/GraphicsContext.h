#pragma once


namespace MyGE {

    class GraphicsContext
    {
        // Methods
        public:
            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}