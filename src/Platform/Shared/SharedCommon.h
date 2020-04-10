#ifndef SHAREDCOMMON_H_
#define SHAREDCOMMON_H_

#include <stddef.h>
#include <stdint.h>
#include "../Shared/Data/FuncPtr.h" //TODO: move to BaseCommon
#include "../Shared/Data/OStream.h"

#define ARG_OUT		// denotes function parameters that are outputs

#define ARG_INOUT	// denotes function parameters that are both input and outputs

#define REG_WRITE_BITS(REG, MASK, POS, VAL) (((REG) = (REG) & (~(MASK))) | ((VAL) << (POS)))

#define REG_WRITE_BIT(REG, POS, VAL) ((REG) = ((REG) & (~((1 << (POS))))) | ((VAL) << (POS)))

#define REG_READ_BIT(REG, POS) (((REG) & (1 << (POS))) >> (POS))

#define REG_READ_BITS(REG, MASK, POS) (((REG) & (MASK)) >> (POS))

#define ELAPSED(START,END,TOP) ((START) <= (END) ? (END) - (START) : ((TOP) - (START)) + (END))

#define CIRCULAR_ADD(START,PLUS,TOP) (((START) + (PLUS)) % (TOP))

#define CIRCULAR_DIFF(START,END,TOP) ((START) <= (END) ? (END) - (START) : (TOP) - (START) + (END))

#define CIRCULAR_FWD(X,Y,N) (((X) + (Y)) % (N))

#define CIRCULAR_BWD(X,Y,N) ((Y) <= (X) ? ((X) - (Y)) : ((N) - (Y) + (X)))

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

namespace BaseJumper
{
	extern OStream& cout;
}

#endif /* SHAREDCOMMON_H_ */
