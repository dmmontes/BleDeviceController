
#ifndef BLE_CONTROLLER_FACTORY
#define BLE_CONTROLLER_FACTORY

#include "IBleController.h"

namespace Ble
{
    /**
     * @brief Factory of BleController.
     */
    class BleControllerFactory
    {
    public:
        /**
         * @brief Type of ble controller 
         */
        enum class BleType : uint8_t
        {
            MOUSE,  ///< Mouse Ble Controller
            GAMEPAD ///< Gamepad Ble Controller
        };

        /**
         * @brief Create a Ble Controller object 
         * 
         * @param type Type of the Ble Controller
         * @return IBleController* Pointer to Ble Controller created
         */
        IBleController *createBleController(BleType type, String name, bool useSecurity);

        /**
         * @brief Delete a Ble Controller object
         * 
         * @param bleController Pointer to Ble Controller Object
         */
        void deleteBleController(IBleController *bleController);

    private:
        IBleController *bleController_{nullptr}; ///< Pointer to BleController
    };

} // namespace Ble

#endif //BLE_CONTROLLER_FACTORY
