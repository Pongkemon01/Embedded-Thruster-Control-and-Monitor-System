#ifndef LIBETCAM_H
#define LIBETCAM_H

#include <array>
#include <cstdint>

namespace libetcam
{
    const uint8_t ku_THRUSTER_NUMBER =          8U;
    const uint8_t ku_THROTTLE_COMMAND_SIZE =    16U;
    const uint8_t ku_THROTTLE_PACKET_SIZE =     ku_THROTTLE_COMMAND_SIZE + 1U;
    const uint8_t ku_TELEMETRY_SIZE =           9U;
    const uint8_t ku_THRUSTER_STATE_SIZE =      ku_THRUSTER_NUMBER * ku_TELEMETRY_SIZE;

    struct TelemetryStruct;

    class TelemetrySync;

    std::array< uint8_t, ku_THROTTLE_PACKET_SIZE > au_throttle_pack( const std::array< uint16_t, ku_THRUSTER_NUMBER >kaus_throttle );
    std::array< struct TelemetryStruct, ku_THRUSTER_NUMBER > ax_telemetry_parser( const std::array< uint8_t, ku_THRUSTER_STATE_SIZE >kau_telemetry );
}

#endif
