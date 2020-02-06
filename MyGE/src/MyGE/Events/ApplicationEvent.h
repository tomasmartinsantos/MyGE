#pragma once

#include "Event.h"


namespace MyGE {

    class MYGE_API WindowResizeEvent : public Event
    {
        // Methods
        public:
            WindowResizeEvent(unsigned int Width, unsigned int Height)
                : m_Width(Width), m_Height(Height) {}

            inline unsigned int GetWidth() const { return m_Width; }
            inline unsigned int GetHeight() const { return m_Height; }

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
                return ss.str();
            }

            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)

        // Variables
        private:
            unsigned int m_Width, m_Height;
    };

    class MYGE_API WindowCloseEvent : public Event
    {
        // Methods
        public:
            WindowCloseEvent() {}

            EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MYGE_API AppTickEvent : public Event
    {
        // Methods
        public:
            AppTickEvent() {}

            EVENT_CLASS_TYPE(AppTick)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MYGE_API AppUpdateEvent : public Event
    {
        // Methods
        public:
            AppUpdateEvent() {}

            EVENT_CLASS_TYPE(AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MYGE_API AppRenderEvent : public Event
    {
        // Methods
        public:
            AppRenderEvent() {}

            EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}