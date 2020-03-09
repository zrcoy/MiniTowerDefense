#ifndef __PlayerController_H__
#define __PlayerController_H__

class Event;

class PlayerController
{
protected:
    bool m_MoveUp;
    bool m_MoveDown;
    bool m_MoveLeft;
    bool m_MoveRight;
    bool m_MousePressed;
    vec2 m_MousePos;
    bool m_Num1Pressed;
    bool m_Num2Pressed;
    bool m_Num3Pressed;
    bool m_Num4Pressed;
    bool m_SaveJSON;

public:
    void OnEvent(Event* pEvent);

    bool IsMoveUpHeld() { return m_MoveUp; }
    bool IsMoveDownHeld() { return m_MoveDown; }
    bool IsMoveLeftHeld() { return m_MoveLeft; }
    bool IsMoveRightHeld() { return m_MoveRight; }
    bool IsMousePressed() { return m_MousePressed; }
    vec2 GetMousePos();
    bool IsNum1Pressed() { return m_Num1Pressed; }
    bool IsNum2Pressed() { return m_Num2Pressed; }
    bool IsNum3Pressed() { return m_Num3Pressed; }
    bool IsNum4Pressed() { return m_Num4Pressed; }
    bool IsSaveJSONPressed() { return m_SaveJSON; }
};


#endif //__PlayerController_H__
