#include "../../Shared/ClientServer/SpiClientServer.h"

namespace BaseJumper
{
	uint8_t SpiClientServer::header_ack[Header::encoded_len] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
}
