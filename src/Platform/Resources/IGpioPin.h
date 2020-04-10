#ifndef IGPIOPIN_H_INCLUDED
#define IGPIOPIN_H_INCLUDED

namespace BaseJumper
{
	class IGpioPin
	{
	  public:
		enum Direction {
			Direction_Input,
			Direction_Output
		};
	
	  private:
	    IGpioPin(const IGpioPin&) = delete;
	    void operator =(const IGpioPin&) = delete;
	
	  protected:
	    IGpioPin() {}
	
	  public:
		virtual void set_direction(Direction dir) = 0;
		virtual void set_level(bool val) = 0;
		virtual bool get_level() = 0;
	};
}

#endif
