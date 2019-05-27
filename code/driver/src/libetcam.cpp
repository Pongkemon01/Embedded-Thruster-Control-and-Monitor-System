#include "libetcam.hpp"

#include <cstring>

namespace libetcam
{
    static const uint8_t ku_COMMAND_THROTTLE = 0xA1U;

    TelemetrySync::TelemetrySync( void )
    {
        this->u_sync_count_ = 0U;
    }
            
    bool TelemetrySync::b_telemetry_sync( const uint8_t ku_recieve_byte )
    {
        bool is_sync = false;
        
        if( ku_recieve_byte == ku_SYNC_BYTE_ )
        {
            ( this->u_sync_count_ )++;
            
            if( this->u_sync_count_ >= ku_SYNC_LENGTH_ )
            {
                is_sync = true;

                this->u_sync_count_ = 0U;
            }
        }
        else
        {
            this->u_sync_count_ = 0U;
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

    std::array< struct TelemetryStruct, ku_THRUSTER_NUMBER > ax_telemetry_parser( const std::array< uint8_t, ku_TELEMETRY_SIZE >&kau_telemetry )
    {
        std::array< struct TelemetryStruct, ku_THRUSTER_NUMBER > ax_telemetry_parsed;
        
        for( uint8_t i = 0U ; i < ku_THRUSTER_NUMBER ; i++ )
        {
            uint16_t us_copy_float_section;

            ax_telemetry_parsed[i].u_temperature = kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 0U];

            us_copy_float_section = ( kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 1U] << 8U );
            us_copy_float_section |= kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 2U];
            ax_telemetry_parsed[i].f_voltage = ( float )( us_copy_float_section ) / ( float )( 100U );

            us_copy_float_section = ( kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 3U] << 8U );
            us_copy_float_section |= kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 4U];
            ax_telemetry_parsed[i].f_current = ( float )( us_copy_float_section ) / ( float )( 100U );

            std::memcpy( ( void * )( &( ax_telemetry_parsed[i].us_power_consumtion ) ), ( void * )( &( kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 5U] ) ), 2U );

            std::memcpy( ( void * )( &( ax_telemetry_parsed[i].us_erpm ) ), ( void * )( &( kau_telemetry[( i * ku_KISS_TELEMETRY_REDUCED_SIZE ) + 7U] ) ), 2U );
        }

        return ax_telemetry_parsed;
    }
}
