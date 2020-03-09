#include "GamePCH.h"

#include "GameObjects/PlayerController.h"

//void PlayerController::ClearSingleFrameBooleans()
//{
//    m_MouseWasPressedThisFrame = false;
//}

void PlayerController::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_NewFrame)
    {
        m_MousePressed = false;
        return;
    }

    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = (InputEvent*)pEvent;




        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (keyID == VK_UP || keyID == 'W') { m_MoveUp = true; }
                if (keyID == VK_DOWN || keyID == 'S') { m_MoveDown = true; }
                if (keyID == VK_LEFT || keyID == 'A') { m_MoveLeft = true; }
                if (keyID == VK_RIGHT || keyID == 'D') { m_MoveRight = true; }
                if (keyID == VK_NUMPAD1 || keyID == '1') { m_Num1Pressed = true; }
                if (keyID == VK_NUMPAD2 || keyID == '2') { m_Num2Pressed = true; }
                if (keyID == VK_NUMPAD3 || keyID == '3') { m_Num3Pressed = true; }
                if (keyID == VK_NUMPAD4 || keyID == '4') { m_Num4Pressed = true; }
                if (keyID == 'P') { m_SaveJSON = true; }
            }

            if (pInput->GetInputState() == InputState_Released)
            {
                if (keyID == VK_UP || keyID == 'W') { m_MoveUp = false; }
                if (keyID == VK_DOWN || keyID == 'S') { m_MoveDown = false; }
                if (keyID == VK_LEFT || keyID == 'A') { m_MoveLeft = false; }
                if (keyID == VK_RIGHT || keyID == 'D') { m_MoveRight = false; }
                if (keyID == VK_NUMPAD1 || keyID == '1') { m_Num1Pressed = false; }
                if (keyID == VK_NUMPAD2 || keyID == '2') { m_Num2Pressed = false; }
                if (keyID == VK_NUMPAD3 || keyID == '3') { m_Num3Pressed = false; }
                if (keyID == VK_NUMPAD4 || keyID == '4') { m_Num4Pressed = false; }
                if (keyID == 'P') { m_SaveJSON = false; }
            }
        }

        else if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            //Get mouse coord in windows defined way
            m_MousePos = pInput->GetPosition();
            if (pInput->GetInputState() == InputState_Pressed)
            {
                //m_MouseWasPressedThisFrame = true;
                m_MousePressed = true;
            }
            if (pInput->GetInputState() == InputState_Released)
            {
                m_MousePressed = false;
            }

        }

#endif
    }
}

vec2 PlayerController::GetMousePos()
{
    return m_MousePos;
    int bp = 0;
}
