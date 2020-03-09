#ifndef __Event_H__
#define __Event_H__

enum EventTypes
{
    EventType_Input,
    EventType_NewFrame
    
};

class Event
{
protected:

public:
    Event() {}
    virtual ~Event() {}

    virtual EventTypes GetEventType() = 0;
};

class NewFrameEvent:public Event
{
protected:

public:
    NewFrameEvent() {}
    virtual ~NewFrameEvent() {}

    virtual EventTypes GetEventType() { return EventType_NewFrame; }
};

#endif //__Event_H__
