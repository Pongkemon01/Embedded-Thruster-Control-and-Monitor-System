#include "libetcam.hpp"

#include <cstring>

namespace libetcam
{
    static const uint8_t ku_COMMAND_THROTTLE = 0xA1U;

    TelemetrySync::TelemetrySync( void )
    {
        this->u_sync_count = 0U;
    }
            
    bool TelemetrySync::b_telemetry_sync( const uint8_t ku_recieve_byte )
    {
        bool is_sync = false;
        
        if( ku_recieve_byte == ku_SYNC_BYTE )
        {
            ( this->u_sync_count )++;
            
            if( this->u_sync_count >= 8U )
            {
                is_sync = true;

                this->u_sync_count = 0U;
            }
        }
        else
        {
            this->u_sync_count = 0U;
        }

        return is_sync;
    }

    std::array< uint8_t, ku_THROTTLE_PACKET_SIZE > au_throttle_pack( const std::array< uint16_t, ku_THRUSTER_NUMBER >&kaus_throttle )
    {
        std::array< uint8_t, ku_THROTTLE_PACKET_SIZE > au_throttle_packet;

        au_throttle_packet[0U] = ku_COMMAND_THROTTLE;

        std::memcpy( ( void * )( au_throttle_packet.begin() + 1U ), ( void * )kaus_throttle.begin(), ku_THROTTLE_COMMAND_SIZE );
        
        return au_throttle_packet;
    }

    std::array< struct TelemetryStruct, ku_THRUSTER_NUMBER > ax_telemetry_parser( const std::array< uint8_t, ku_THRUSTER_STATE_SIZE >&kau_telemetry )
    {
        std::array< struct TelemetryStruct, ku_THRUSTER_NUMBER > ax_thruster_state;
        
        for( uint8_t i = 0U ; i < ku_THRUSTER_NUMBER ; i++ )
        {
            uint16_t us_copy_float_section;

            ax_thruster_state[i].u_temperature = kau_telemetry[( i * ku_TELEMETRY_SIZE ) + 0U];

            std::memcpy( ( void * )( &us_copy_float_section ), ( void * )( &( kau_telemetry[( i * ku_TELEMETRY_SIZE ) + 1U] ) ), 2U );
            ax_thruster_state[i].f_voltage = ( float )( us_copy_float_section * 100U );

            std::memcpy( ( void * )( &us_copy_float_section ), ( void * )( &( kau_telemetry[( i * ku_TELEMETRY_SIZE ) + 3U] ) ), 2U );
            ax_thruster_state[i].f_current = ( float )( us_copy_float_section * 100U );

            std::memcpy( ( void * )( &( ax_thruster_state[i].us_power_consumtion ) ), ( void * )( &( kau_telemetry[( i * ku_TELEMETRY_SIZE ) + 5U] ) ), 2U );

            std::memcpy( ( void * )( &( ax_thruster_state[i].us_erpm ) ), ( void * )( &( kau_telemetry[( i * ku_TELEMETRY_SIZE ) + 7U] ) ), 2U );
        }

        return ax_thruster_state;
    }
}
