#pragma once

#include "Event.h"


namespace MyGE {

    class MYGE_API MouseMovedEvent : public Event
    {
        // Methods
        public:
            MouseMovedEvent(float X, float Y)
                : m_MouseX(X), m_MouseY(Y) {}

            inline float GetX() const { return m_MouseX; }
            inline float GetY() const { return m_MouseY; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        // Variables
        private:
            float m_MouseX, m_MouseY;
    };

    class MYGE_API MouseScrolledEvent : public Event
    {
        // Methods
        public:
            MouseScrolledEvent(float XOffset, float YOffset)
                : m_XOffset(XOffset), m_YOffset(YOffset) {}

            inline float GetXOffset() const { return m_XOffset; }
            inline float GetYOffset() const { return m_YOffset; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        // Variables
        private:
            float m_XOffset, m_YOffset;
    };

    class MYGE_API MouseButtonEvent : public Event
    {
        // Methods
        public:
            inline int GetMouseButton() const { return m_Button; }

            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        protected:
            MouseButtonEvent(int Button)
                : m_Button(Button) {}

        // Variables
        protected:
            int m_Button;
    };

    class MYGE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
        // Methods
        public:
            MouseButtonPressedEvent(int Button)
                : MouseButtonEvent(Button) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MYGE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
        // Methods
        public:
            MouseButtonReleasedEvent(int Button)
                : MouseButtonEvent(Button) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_Button;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}