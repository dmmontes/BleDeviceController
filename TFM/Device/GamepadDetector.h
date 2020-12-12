#ifndef GAMEPAD_DETECTOR
#define GAMEPAD_DETECTOR

#include "GamepadAction.h"

namespace Detector
{
    /**
     * @brief Common class for gamepad detectors 
     */
    class GamepadDetector
    {
    protected:
        /**
         * @brief Check if key has changed its state
         * 
         * @param keyPressed indicates if key is pressed
         * @param key Key that represents the action
         * @param action Action to be performed
         * @return true if key has changed its state, false otherwise
         */
        bool checkKey(bool keyPressed, GamepadAction::Key key, IAction *action);

    private:
        static uint8_t ID;               ///< Generator of ids for each detector
        const uint8_t detectorId_{++ID}; ///< Id of the gamepad detector
    };
} // namespace Detector

#endif //GAMEPAD_DETECTOR
