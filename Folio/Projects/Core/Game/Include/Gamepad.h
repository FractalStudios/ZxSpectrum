#pragma once

// Windows includes.
#include    <Windows.h>
#include    <XInput.h>
#pragma comment(lib, "XInput.lib") 

// STL includes.
#include    <map>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

class Gamepad
{
public:
    Gamepad (FolioHandle    targetWndHandle = 0,
             float          deadZoneX = 0.05f,
             float          deadZoneY = 0.02f);
    ~Gamepad ();

    // Controller id enumeration.
    enum CONTROLLER_ID
    {
        CONTROLLER_ID_UNDEFINED = -1,
        CONTROLLER_ID_1,
        CONTROLLER_ID_2,
        CONTROLLER_ID_3,
        CONTROLLER_ID_4,
    }; // Endenum.

    bool    CheckController (CONTROLLER_ID controllerId);

    // Button enumeration.
    enum BUTTON
    {
        BUTTON_UNDEFINED        = -1,
        BUTTON_DPAD_UP          = XINPUT_GAMEPAD_DPAD_UP,
        BUTTON_DPAD_DOWN        = XINPUT_GAMEPAD_DPAD_DOWN,
        BUTTON_DPAD_LEFT        = XINPUT_GAMEPAD_DPAD_LEFT,
        BUTTON_DPAD_RIGHT       = XINPUT_GAMEPAD_DPAD_RIGHT,
        BUTTON_START            = XINPUT_GAMEPAD_START,
        BUTTON_BACK             = XINPUT_GAMEPAD_BACK,
        BUTTON_LEFT_THUMB       = XINPUT_GAMEPAD_LEFT_THUMB,
        BUTTON_RIGHT_THUMB      = XINPUT_GAMEPAD_RIGHT_THUMB,
        BUTTON_LEFT_SHOULDER    = XINPUT_GAMEPAD_LEFT_SHOULDER,
        BUTTON_RIGHT_SHOULDER   = XINPUT_GAMEPAD_RIGHT_SHOULDER,
        BUTTON_A                = XINPUT_GAMEPAD_A,
        BUTTON_B                = XINPUT_GAMEPAD_B,
        BUTTON_X                = XINPUT_GAMEPAD_X,
        BUTTON_Y                = XINPUT_GAMEPAD_Y,
    }; // Endenum.

    CONTROLLER_ID   GetFirstConnectedController () const;
    bool            IsControllerConnected (CONTROLLER_ID controllerId) const;

    bool    IsButtonDown (CONTROLLER_ID controllerId, 
                          BUTTON        button) const;

    bool    IsDPadUpButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsDPadDownButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsDPadLeftButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsDPadRightButtonDown (CONTROLLER_ID controllerId) const;

    bool    IsStartButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsBackButtonDown (CONTROLLER_ID controllerId) const;

    bool    IsLeftThumbButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsRightThumbButtonDown (CONTROLLER_ID controllerId) const;
    
    bool    IsLeftShoulderButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsRightShoulderButtonDown (CONTROLLER_ID controllerId) const;

    bool    IsAButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsBButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsXButtonDown (CONTROLLER_ID controllerId) const;
    bool    IsYButtonDown (CONTROLLER_ID controllerId) const;

    UInt8   GetLeftTriggerPressure (CONTROLLER_ID controllerId) const;
    UInt8   GetRightTriggerPressure (CONTROLLER_ID controllerId) const;

    float   GetLeftAnalogStickXPosition (CONTROLLER_ID controllerId) const;
    float   GetLeftAnalogStickYPosition (CONTROLLER_ID controllerId) const;

    float   GetRightAnalogStickXPosition (CONTROLLER_ID controllerId) const;
    float   GetRightAnalogStickYPosition (CONTROLLER_ID controllerId) const;

    // The default key auto-repeat rate.
    static  const   UInt32  DEFAULT_KEY_AUTO_REPEAT_RATE = 150;

    FolioStatus AddKeyMapping (CONTROLLER_ID    controllerId,
                               BUTTON           button, 
                               UInt32           virtualKey,
                               UInt32           keyAutoRepeatRate = DEFAULT_KEY_AUTO_REPEAT_RATE);
    FolioStatus RemoveKeyMappingByButton (CONTROLLER_ID controllerId,
                                          BUTTON        button);
    FolioStatus RemoveKeyMappingByKey (CONTROLLER_ID    controllerId,
                                       UInt32           virtualKey);
    void    ClearKeyMappings (CONTROLLER_ID controllerId);

    void    EnableKeyMappingEvents (FolioHandle targetWndHandle);
    void    DisableKeyMappingEvents ();
    bool    IsKeyMappingEventsEnabled (CONTROLLER_ID controllerId) const;

private:
    FolioHandle m_targetWndHandle;  // Target window for mapped keys.
    
    float   m_deadZoneX;    // Analog stick X dead zone.
    float   m_deadZoneY;    // Analog stick Y dead zone.

    // Controller state map.
    typedef std::map<CONTROLLER_ID, XINPUT_STATE>   ControllerStateMap;

    ControllerStateMap    m_controllerStates; // Controller state map.

    // Simulated key.
    struct SimulatedKey
    {
        SimulatedKey ()
        :   m_button(BUTTON_UNDEFINED),   
            m_virtualKey(0),
            m_keyAutoRepeatRate(DEFAULT_KEY_AUTO_REPEAT_RATE),
            m_lastKeyPressTickCount(0)
        {} // Endproc.

        SimulatedKey (BUTTON   button,   
                      UInt32   virtualKey,
                      UInt32   keyAutoRepeatRate)
        :   m_button(button),   
            m_virtualKey(virtualKey),
            m_keyAutoRepeatRate(keyAutoRepeatRate),
            m_lastKeyPressTickCount(0)
        {} // Endproc.

        ~SimulatedKey()
        {} // Endproc.
        
        BUTTON  m_button;                   // The controller button.
        UInt32  m_virtualKey;               // The virtual key.
        UInt32  m_keyAutoRepeatRate;        // The auto-repeat rate (in milliseconds) of a simulated key press.
        UInt32  m_lastKeyPressTickCount;    // The tick count when the simulated key was last pressed. 
    }; // Endstruct.

    // Simulated key map.
    typedef std::multimap<CONTROLLER_ID, SimulatedKey>  ControllerSimulatedKeyMap;

    ControllerSimulatedKeyMap   m_controllerSimulatedKeys; // Controller simulated keys.

    void    DispatchKeyMappings (CONTROLLER_ID          controllerId,
                                 const XINPUT_STATE&    currentControllerState,
                                 const XINPUT_STATE&    previousControllerState);

    bool    IsButtonDown (BUTTON                button,
                          const XINPUT_STATE&   controllerState) const;

    void    UpdateControllerState (CONTROLLER_ID        controllerId,
                                   const XINPUT_STATE&  controllerState);
    void    RemoveControllerState (CONTROLLER_ID controllerId);

    bool    FindController (CONTROLLER_ID   controllerId,
                            XINPUT_STATE*   controllerState = 0) const;

    ControllerSimulatedKeyMap::iterator FindKeyMappingByButton (CONTROLLER_ID   controllerId,
                                                                BUTTON          button);
    ControllerSimulatedKeyMap::iterator FindKeyMappingByKey (CONTROLLER_ID  controllerId,
                                                             UInt32         virtualKey);

    FolioStatus QueryControllerState (CONTROLLER_ID controllerId,
                                      XINPUT_STATE& controllerState) const;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
