#ifndef __GPIOADAPTOR_H__
#define __GPIOADAPTOR_H__

#include "Platform/PlatformCommon.h"
#include "Platform/Resources/IGpioPin.h"

namespace BaseJumper
{
  class GpioAdaptor : public IGpioPin
  {
  private:
    const uint8_t pin_num;

  public:
    GpioAdaptor(const uint8_t pin_num);
    void set_direction(IGpioPin::Direction direction) override final;
    void set_level(bool val) override final;
    bool get_level() override final;
  };
}
#endif //__GPIOADAPTOR_H__
