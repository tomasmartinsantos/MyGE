#pragma once

#include "Event.h"


namespace MyGE {

    class MYGE_API KeyEvent : public Event
    {
        // Methods
        public:
            inline int GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        protected:
            KeyEvent(int KeyCode)
                : m_KeyCode(KeyCode) {}

        // Variables
        protected:
            int m_KeyCode;
    };

    class MYGE_API KeyPressedEvent : public KeyEvent
    {
        // Methods
        public:
            KeyPressedEvent(int KeyCode, int RepeatCount)
                : KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

            inline int GetRepeatCount() const { return m_RepeatCount; }

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << ") repeats";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed)

        // Variables
        private:
            int m_RepeatCount;
    };

    class MYGE_API KeyReleasedEvent : public KeyEvent
    {
        // Methods
        public:
            KeyReleasedEvent(int KeyCode)
                : KeyEvent(KeyCode) {}

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_KeyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyReleased)
    };

    class MYGE_API KeyTypedEvent : public KeyEvent
    {
        // Methods
        public:
            KeyTypedEvent(int KeyCode)
                : KeyEvent(KeyCode) {}

            virtual std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyTypedEvent: " << m_KeyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyTyped)
    };
}