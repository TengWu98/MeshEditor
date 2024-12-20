﻿#pragma once

#include "pch.h"

LINK_EDITOR_NAMESPACE_BEGIN

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4)
};

#define EVENT_CLASS_TYPE(Type) static EventType GetStaticType() {return EventType::Type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #Type; }

#define EVENT_CLASS_CATEGORY(Category) virtual int GetCategoryFlags() const override { return Category; }


class Event
{
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    bool IsInCategory(EventCategory Category)
    {
        return GetCategoryFlags() & Category;
    }
};

class EventDispatcher
{
public:
    EventDispatcher(Event& InEvent)
        : Event(InEvent)
    {
    }
		
    // F will be deduced by the compiler
    template<typename T, typename F>
    bool Dispatch(const F& Func)
    {
        if (Event.GetEventType() == T::GetStaticType())
        {
            Event.Handled |= Func(static_cast<T&>(Event));
            return true;
        }
        return false;
    }
private:
    Event& Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& InEvent)
{
    return os << InEvent.ToString();
}

LINK_EDITOR_NAMESPACE_END