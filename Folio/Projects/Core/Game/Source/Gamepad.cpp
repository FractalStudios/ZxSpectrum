// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    <Util.h>
#include    "Gamepad.h"

namespace Folio
{

namespace Core
{

namespace Game
{

Gamepad::Gamepad (FolioHandle   targetWndHandle,
                  float         deadZoneX,
                  float         deadZoneY)
:   m_targetWndHandle(targetWndHandle),
    m_deadZoneX(deadZoneX),
    m_deadZoneY(deadZoneY)
{
} // Endproc.


Gamepad::~Gamepad ()
{
} // Endproc.


bool    Gamepad::CheckController (CONTROLLER_ID controllerId)
{
    // Query the controller's state.

    XINPUT_STATE    currentControllerState = {0};  // Initialise!

    bool    controllerConnected = (QueryControllerState (controllerId, currentControllerState) == ERR_SUCCESS);

    // Is the controller connected?

    if (controllerConnected)
    {
        // Yes. Are key mapping events enabled for this controller?

        if (IsKeyMappingEventsEnabled (controllerId))
        {
            // Yes. Find the controller (and get its previous state).

            XINPUT_STATE    previousControllerState = {0};  // Initialise!

            if (FindController (controllerId, &(previousControllerState)))
            {
                // Dispatch.

                DispatchKeyMappings (controllerId, currentControllerState, previousControllerState);
            } // Endif.

        } // Endif.

        // Update the controller's state.

        UpdateControllerState (controllerId, currentControllerState);
    } // Endif.

    else
    {
        // No. Remove the controller's state.
        
        RemoveControllerState (controllerId);
    } // Endelse.

    return (controllerConnected);
} // Endproc.


Gamepad::CONTROLLER_ID  Gamepad::GetFirstConnectedController () const
{
    CONTROLLER_ID   controllerId = CONTROLLER_ID_UNDEFINED;

    // Find the first connected controller.

    for (UInt32 controller = CONTROLLER_ID_1; controller <= CONTROLLER_ID_4; ++controller)
    {
        // Query the controller's state.

        XINPUT_STATE    currentControllerState = {0};  // Initialise!

        if (QueryControllerState (static_cast<CONTROLLER_ID> (controller), currentControllerState) == ERR_SUCCESS)
        {
            // Note the conroller's identifier.

            controllerId = static_cast<CONTROLLER_ID> (controller);

            break;
        } // Endif.

    } // Endfor.

    return (controllerId);
} // Endproc.


bool    Gamepad::IsControllerConnected (CONTROLLER_ID controllerId) const
{
    // Find the controller.
    
    return (FindController (controllerId));
} // Endproc.


bool    Gamepad::IsButtonDown (CONTROLLER_ID controllerId, 
                               BUTTON        button) const
{
    bool    isButtonDown = false;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        // Is the controller's button down?

        isButtonDown = IsButtonDown (button, controllerState);
    } // Endif.

    return (isButtonDown);
} // Endproc.


bool    Gamepad::IsDPadUpButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_DPAD_UP)); 
} // Endproc.


bool    Gamepad::IsDPadDownButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_DPAD_DOWN)); 
} // Endproc.


bool    Gamepad::IsDPadLeftButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_DPAD_LEFT)); 
} // Endproc.


bool    Gamepad::IsDPadRightButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_DPAD_RIGHT)); 
} // Endproc.


bool    Gamepad::IsStartButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_START)); 
} // Endproc.


bool    Gamepad::IsBackButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_BACK)); 
} // Endproc.


bool    Gamepad::IsLeftThumbButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_LEFT_THUMB)); 
} // Endproc.


bool    Gamepad::IsRightThumbButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_RIGHT_THUMB)); 
} // Endproc.


bool    Gamepad::IsLeftShoulderButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_LEFT_SHOULDER)); 
} // Endproc.


bool    Gamepad::IsRightShoulderButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_RIGHT_SHOULDER)); 
} // Endproc.


bool    Gamepad::IsAButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_A)); 
} // Endproc.


bool    Gamepad::IsBButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_B)); 
} // Endproc.


bool    Gamepad::IsXButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_X)); 
} // Endproc.


bool    Gamepad::IsYButtonDown (CONTROLLER_ID controllerId) const
{
    return (IsButtonDown (controllerId, BUTTON_Y)); 
} // Endproc.


UInt8   Gamepad::GetLeftTriggerPressure (CONTROLLER_ID controllerId) const
{
    UInt8   leftTriggerPressure = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        leftTriggerPressure = controllerState.Gamepad.bLeftTrigger;
    } // Endif.

    return (leftTriggerPressure);
} // Endproc.


UInt8   Gamepad::GetRightTriggerPressure (CONTROLLER_ID controllerId) const
{
    UInt8   rightTriggerPressure = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        rightTriggerPressure = controllerState.Gamepad.bRightTrigger;
    } // Endif.

    return (rightTriggerPressure);
} // Endproc.


float   Gamepad::GetLeftAnalogStickXPosition (CONTROLLER_ID controllerId) const
{
    float   leftAnalogStickXPosition = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        leftAnalogStickXPosition = controllerState.Gamepad.sThumbLX;

        leftAnalogStickXPosition = (std::abs (leftAnalogStickXPosition) < m_deadZoneX 
                                   ? 0 
                                   : (std::abs (leftAnalogStickXPosition) - m_deadZoneX) * (leftAnalogStickXPosition / std::abs (leftAnalogStickXPosition)));
 
        if (m_deadZoneX > 0) 
        {
            leftAnalogStickXPosition /= 1 - m_deadZoneX;
        } // Endif.

    } // Endif.

    return (leftAnalogStickXPosition);
} // Endproc.


float   Gamepad::GetLeftAnalogStickYPosition (CONTROLLER_ID controllerId) const
{
    float   leftAnalogStickYPosition = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        leftAnalogStickYPosition = controllerState.Gamepad.sThumbLY;

        leftAnalogStickYPosition = (std::abs (leftAnalogStickYPosition) < m_deadZoneY 
                                   ? 0 
                                   : (std::abs (leftAnalogStickYPosition) - m_deadZoneY) * (leftAnalogStickYPosition / std::abs (leftAnalogStickYPosition)));
 
        if (m_deadZoneY > 0) 
        {
            leftAnalogStickYPosition /= 1 - m_deadZoneY;
        } // Endif.

    } // Endif.

    return (leftAnalogStickYPosition);
} // Endproc.


float   Gamepad::GetRightAnalogStickXPosition (CONTROLLER_ID controllerId) const
{
    float   rightAnalogStickXPosition = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        rightAnalogStickXPosition = controllerState.Gamepad.sThumbRX;

        rightAnalogStickXPosition = (std::abs (rightAnalogStickXPosition) < m_deadZoneX 
                                    ? 0 
                                    : (std::abs (rightAnalogStickXPosition) - m_deadZoneX) * (rightAnalogStickXPosition / std::abs (rightAnalogStickXPosition)));
 
        if (m_deadZoneX > 0) 
        {
            rightAnalogStickXPosition /= 1 - m_deadZoneX;
        } // Endif.

    } // Endif.

    return (rightAnalogStickXPosition);
} // Endproc.


float   Gamepad::GetRightAnalogStickYPosition (CONTROLLER_ID controllerId) const
{
    float   rightAnalogStickYPosition = 0;   // Initialise!

    // Find the controller (and get its state).

    XINPUT_STATE    controllerState = {0};  // Initialise!

    if (FindController (controllerId, &(controllerState)))
    {
        rightAnalogStickYPosition = controllerState.Gamepad.sThumbRY;

        rightAnalogStickYPosition = (std::abs (rightAnalogStickYPosition) < m_deadZoneY 
                                    ? 0 
                                    : (std::abs (rightAnalogStickYPosition) - m_deadZoneY) * (rightAnalogStickYPosition / std::abs (rightAnalogStickYPosition)));
 
        if (m_deadZoneY > 0) 
        {
            rightAnalogStickYPosition /= 1 - m_deadZoneY;
        } // Endif.

    } // Endif.

    return (rightAnalogStickYPosition);
} // Endproc.


FolioStatus Gamepad::AddKeyMapping (CONTROLLER_ID   controllerId,
                                    BUTTON          button, 
                                    UInt32          virtualKey,
                                    UInt32          keyAutoRepeatRate)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the controller's button already mapped?

    ControllerSimulatedKeyMap::iterator itr = FindKeyMappingByButton (controllerId, button);

    if (itr == m_controllerSimulatedKeys.end ())
    {
        // No. Add the controller's button to key mapping.

        m_controllerSimulatedKeys.insert (ControllerSimulatedKeyMap::value_type(controllerId, 
                                                                                SimulatedKey(button, virtualKey, keyAutoRepeatRate)));
    } // Endif.

    else
    {
        // Yes.

        status = ERR_ALREADY_EXISTS;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus Gamepad::RemoveKeyMappingByButton (CONTROLLER_ID    controllerId,
                                               BUTTON           button)
{
    // Is the controller's button mapped?

    ControllerSimulatedKeyMap::iterator itr = FindKeyMappingByButton (controllerId, button);

    if (itr != m_controllerSimulatedKeys.end ())
    {
        // Yes. Remove it.

        m_controllerSimulatedKeys.erase (itr);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus Gamepad::RemoveKeyMappingByKey (CONTROLLER_ID   controllerId,
                                            UInt32          virtualKey)
{
    // Is the virtual key mapped to the controller's button?

    ControllerSimulatedKeyMap::iterator itr = FindKeyMappingByKey (controllerId, virtualKey);

    if (itr != m_controllerSimulatedKeys.end ())
    {
        // Yes. Remove it.

        m_controllerSimulatedKeys.erase (itr);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


void    Gamepad::ClearKeyMappings (CONTROLLER_ID controllerId)
{
    m_controllerSimulatedKeys.erase (controllerId);
} // Endproc.

         
void    Gamepad::EnableKeyMappingEvents (FolioHandle targetWndHandle)
{
    m_targetWndHandle = targetWndHandle;
} // Endproc.


void    Gamepad::DisableKeyMappingEvents ()
{
    m_targetWndHandle = 0;
} // Endproc.


bool    Gamepad::IsKeyMappingEventsEnabled (CONTROLLER_ID controllerId) const
{
    // Has the target window been set?

    bool    isKeyMappingEventsEnabled = (m_targetWndHandle != 0);

    if (isKeyMappingEventsEnabled)
    {
        // Yes. Has at least one key been mapped for this controller?

        isKeyMappingEventsEnabled = 
            (m_controllerSimulatedKeys.find (controllerId) != m_controllerSimulatedKeys.end ());
    } // Endif.

    return (isKeyMappingEventsEnabled);
} // Endproc.


void    Gamepad::DispatchKeyMappings (CONTROLLER_ID         controllerId,
                                      const XINPUT_STATE&   currentControllerState,
                                      const XINPUT_STATE&   previousControllerState)
{
    // Get the current time tick count.

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
                
    for (ControllerSimulatedKeyMap::iterator itr = m_controllerSimulatedKeys.begin ();
        itr != m_controllerSimulatedKeys.end ();
        ++itr)
    {
        // Is the button mapped for this controller?

        if (itr->first == controllerId)
        {
            // Get the simulated key.

            SimulatedKey&   simulatedKey(itr->second);

            // Yes. Is the button down?

            if (IsButtonDown (itr->second.m_button, currentControllerState))
            {
                // Get the previous time tick count of the simulated key.

                UInt32  previousTickCount = simulatedKey.m_lastKeyPressTickCount;
 
                // Is this the first button press, or has the repeat interval passed?

                if (((simulatedKey.m_keyAutoRepeatRate  > 0) && ((currentTickCount - previousTickCount) >= simulatedKey.m_keyAutoRepeatRate))   ||
                    ((simulatedKey.m_keyAutoRepeatRate == 0) && !IsButtonDown (itr->second.m_button, previousControllerState))                  ||
                    !previousTickCount)
                {
                    // Note the last key press tick count.

                    simulatedKey.m_lastKeyPressTickCount = currentTickCount;

                    // Send WM_KEYDOWN event.

                    Util::Wnd::SendWndMessage (m_targetWndHandle, 
                                               WM_KEYDOWN, 
                                               simulatedKey.m_virtualKey,
                                               0x00ff0001 | (IsButtonDown (itr->second.m_button, previousControllerState) ? 1 << 30 : 0 << 30));
                } // Endif.
 
            } // Endif.

            // Check for button release events.

            else
            if ((previousControllerState.dwPacketNumber < currentControllerState.dwPacketNumber)    &&
                 simulatedKey.m_lastKeyPressTickCount)
            {
                // Reset the last key press tick count.

                simulatedKey.m_lastKeyPressTickCount = 0;

                // Send WM_KEYUP event.

                Util::Wnd::SendWndMessage (m_targetWndHandle, 
                                           WM_KEYUP, 
                                           simulatedKey.m_virtualKey,
                                           0xc0ff0001);
            } // Endelseif.

        } // Endif.
    
    } // Endfor.

} // Endproc.


bool    Gamepad::IsButtonDown (BUTTON               button,
                               const XINPUT_STATE&  controllerState) const
{
    return ((controllerState.Gamepad.wButtons & button) != 0);
} // Endproc.


void    Gamepad::UpdateControllerState (CONTROLLER_ID       controllerId,
                                        const XINPUT_STATE& controllerState)
{
    // Find the controller.

    ControllerStateMap::iterator    itr = m_controllerStates.find (controllerId);

    if (itr == m_controllerStates.end ())
    {
        // New controller. Add its state.

        m_controllerStates.insert (ControllerStateMap::value_type(controllerId, controllerState));
    } // Endif.

    else
    {
        // Existing controller. Update its state.

        itr->second = controllerState;
    } // Endelse.

} // Endproc.


void    Gamepad::RemoveControllerState (CONTROLLER_ID controllerId)
{
    // Find the controller.
    
    ControllerStateMap::iterator    itr = m_controllerStates.find (controllerId);

    if (itr != m_controllerStates.end ())
    {
        // Remove the controller.

        m_controllerStates.erase (itr);
    } // Endif.

} // Endproc.


bool    Gamepad::FindController (CONTROLLER_ID  controllerId, 
                                 XINPUT_STATE*  controllerState) const
{
    // Find the controller.

    ControllerStateMap::const_iterator  itr = m_controllerStates.find (controllerId);

    if (controllerState && (itr != m_controllerStates.end ()))
    {
        // Note the controller's state.

        *controllerState = itr->second;
    } // Endif.

    return (itr != m_controllerStates.end ());
} // Endproc.


Gamepad::ControllerSimulatedKeyMap::iterator    Gamepad::FindKeyMappingByButton (CONTROLLER_ID  controllerId,
                                                                                 BUTTON         button)
{
    return (std::find_if (m_controllerSimulatedKeys.begin (), m_controllerSimulatedKeys.end (), 
                          [controllerId, button](const std::pair<CONTROLLER_ID, SimulatedKey>& arg) 
                          {return ((arg.first           == controllerId) &&
                                   (arg.second.m_button == button));}));
} // Endproc.


Gamepad::ControllerSimulatedKeyMap::iterator    Gamepad::FindKeyMappingByKey (CONTROLLER_ID controllerId,
                                                                              UInt32        virtualKey)
{
    return (std::find_if (m_controllerSimulatedKeys.begin (), m_controllerSimulatedKeys.end (), 
                          [controllerId, virtualKey](const std::pair<CONTROLLER_ID, SimulatedKey>& arg) 
                          {return ((arg.first               == controllerId) &&
                                   (arg.second.m_virtualKey == virtualKey));}));
} // Endproc.


FolioStatus Gamepad::QueryControllerState (CONTROLLER_ID    controllerId,
                                           XINPUT_STATE&    controllerState) const
{
    FolioStatus status = ERR_SUCCESS;

    UInt32  win32Error = ::XInputGetState (controllerId, &(controllerState));
    
    if (win32Error != ERROR_SUCCESS)
    {
        status = FOLIO_MAKE_OS_ERROR(win32Error);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
