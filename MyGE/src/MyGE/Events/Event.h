#pragma once

#include "MyGE/Core.h"


namespace MyGE {


    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BITT(0),
        EventCategoryInput          = BITT(1),
        EventCategoryKeyboard       = BITT(2),
        EventCategoryMouse          = BITT(3),
        EventCategoryMouseButton    = BITT(4)
    };


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlag() const override { return category; }

    class MYGE_API Event
    {
            friend class EventDispatcher;

        // Methods
        public:
            virtual EventType GetEventType() const  = 0;
            virtual const char* GetName() const     = 0;
            virtual int GetCategoryFlag() const     = 0;
            virtual std::string ToString() const { return GetName(); }

            inline bool IsInCategory(EventCategory Category)
            {
                return GetCategoryFlag() & Category;
            }

        // Varaiables
        protected:
            bool m_Handled = false;
    };

    class EventDispatcher
    {
            template<typename T>
            using EventFn = std::function<bool(T&)>;

        // Methods
        public:
            EventDispatcher(Event& Event)
                : m_Event(Event) {}

            template<typename T>
            bool Dispatch(EventFn<T> Func)
            {
                if (m_Event.GetEventType() = T::GetStaticType())
                {
                    m_Event.m_Handled = Func(*(T*)&m_Event);
                    return true;
                }
                return false;
            }

        // Variables
        private:
            Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& E)
    {
        return os << E.ToString();
    }
}