#include "./Platform/Shared/Core/AssertionManager.h"
#include "./Platform/Shared/Core/AssertionPersistanceRam.h"
#include "./Platform/Platform.h"
#include "./Platform/Shared/Data/OStream.h"
#include "SpiAdaptor.h"
#include "GpioAdaptor.h"
#include "ClassId.h"

/** Arduino Classifications **/
// Boards are grouped by the jumper they use
#if defined(USE_ARDUINO_MKR_PIN_LAYOUT)
    #define JUMPER_MKR
#elif defined(ARDUINO_AVR_UNO)
    #define JUMPER_UNO
#else
    #error "Unsupported Board."    
#endif


namespace BaseJumper
{
    /** Assertions **/
 
    constexpr size_t max_assertions = 5;
    static AssertionPersistanceRam<max_assertions> persistance;
    static AssertionManager<Num_ClassIds,max_assertions> manager(persistance);
    IAssertionManager& assertion_manager = manager;

    /** Pin mappings **/

    #if defined(JUMPER_MKR)
    static constexpr uint8_t ss_pin_num = 7;
    static constexpr uint8_t busy_pin_num = 6;
    #elif defined(JUMPER_UNO)
    static constexpr uint8_t ss_pin_num = 10;
    static constexpr uint8_t busy_pin_num = 9;
    #endif    

    /** Resources **/

    static SpiAdaptor spi_adaptor;
    static GpioAdaptor ss_pin_adaptor(ss_pin_num);
    static GpioAdaptor busy_pin_adaptor(busy_pin_num);

    /** Resource Mappings **/

    ISpi& ctl_client_spi = spi_adaptor;
    IGpioPin& ctl_client_ss_pin = ss_pin_adaptor;
    IGpioPin& ctl_client_busy_pin = busy_pin_adaptor;
    
    OStream& cout = null_stream;

    /** Functions **/

    void platform_init()
    {
    }
}