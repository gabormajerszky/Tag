#pragma once

#include "ClientPacket.h"
#include "Address.h"

struct AddressedPacket {
    ClientPacket packet;
    Address address;
};
