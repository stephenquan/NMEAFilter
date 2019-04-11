//====================================================================
//
// Copyright © 1995 - 2010 MapTel Pty. Ltd.. 
// All Rights Reserved. 
// Use subject to License Agreement.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Purpose:
//   Structures, constants, flags needed for a GPS extension. 
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// History:
//  Elvin Slavik    11/??/2001 Original coding
//  Joseph Zastrow  03/26/2002 Comments.
//
//====================================================================

#ifndef __INSTRUMENT__
#define __INSTRUMENT__

#pragma once
#include "Shapes.h"

#ifdef __cplusplus
extern "C" {
#endif
//--------------------------------------------------------------------
// Manufacturer values. Assign to Manufacturer field
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef enum INSMANUFACTURER
{
    INS_MANUF_UNKNOWN = 0,
    INS_MANUF_TRIMBLE,
    INS_MANUF_ASHTECH,
    INS_MANUF_MAGELLAN,
    INS_MANUF_GARMIN,
    INS_MANUF_ROCKWELL,
    INS_MANUF_DELORME,
    INS_MANUF_SONY,
    INS_MANUF_LEICA,
    INS_MANUF_SIRF,
	INS_MANUF_LASERATLANTA,
	INS_MANUF_LASERTECH,
	INS_MANUF_LASERCRAFT,
	INS_MANUF_MDL,
} INSMANUFACTURER;

//--------------------------------------------------------------------
// Battery technology
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef enum INSBATTERYTECHNOLOGY
{
	INS_BATTERY_UNKNOWN = 0,
	INS_BATTERY_CARBON,
	INS_BATTERY_ALKALINE,
	INS_BATTERY_LITHIUM,
	INS_BATTERY_NICAD,
	INS_BATTERY_LION,
	INS_BATTERY_NIMH,
} INSBATTERYTECHNOLOGY;

//--------------------------------------------------------------------
// Not a number constants
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define INS_NAN                         -DBL_MAX
#define INS_NAN_WORD                    0xFFFE
#define INS_NAN_DWORD                   0xFFFFFFFE
    
//--------------------------------------------------------------------
// Device type flags. Assign to one or more to InstrumentType
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define INS_TYPE_GPS                    0x00000001          // GPS
#define INS_TYPE_RANGEFINDER            0x00000002          // Rangefinder

//--------------------------------------------------------------------
// These are the data mask flags that are assigned to the DataMask
// field to indicate which data fields in the instrument structure
// have been set. 
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define INS_DATA_POSITION               0x00000001          // GPS Position (X/Y/Z)
#define INS_DATA_QUALITY                0x00000002          // GPS Quality indicator
#define INS_DATA_DOP                    0x00000004          // GPS DOP Values
#define INS_DATA_ERRORESTIMATES         0x00000008          // GPS Error Estimates
#define INS_DATA_SATELLITES             0x00000010          // GPS Satellite(s) imformation
#define INS_DATA_TIME                   0x00000020          // UTC Time
#define INS_DATA_DATE                   0x00000040          // UTC Date
#define INS_DATA_COURSE                 0x00000080          // GPS Course (SOG/COG)
#define INS_DATA_SOUNDER                0x00000100          // Depth Sounder
#define INS_DATA_WEATHER                0x00000200          // Weather information
#define INS_DATA_COMPASS                0x00000400          // Compass Heading
#define INS_DATA_VELOCITY               0x00000800          // GPS Velocity
#define INS_DATA_DATUM                  0x00001000          // GPS Map Datum
#define INS_DATA_RANGE                  0x00002000          // Rangefinder
#define INS_DATA_TRIGGER                0x00004000          // Trigger/Button
#define INS_DATA_BATTERY				0x00008000			// Battery
#define INS_DATA_MEASUREMENTS           0x10000000          // Other Measurement(s)
#define INS_DATA_INTERMEDIATE			0x20000000			// Instrument data is in an intermediate state (eg not all packets received yet)
#define INS_DATA_INTERNAL               0x40000000          // Receiver specific/internal information
#define INS_DATA_ERROR                  0x80000000          // Error condition

//--------------------------------------------------------------------
// These are error values assigned to ErrorCode field when there
// is some sort of error.
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define INS_ERROR_NONE                  0                   // No error
#define INS_ERROR_CHECKSUM              1                   // Data checksum error
#define INS_ERROR_MALFORMED             2                   // Malformed data
#define INS_ERROR_UNKNOWN               0xFFFFFFFF          // General unspecified error

//--------------------------------------------------------------------
// Instrument measurement structure (for future use)
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct INSMEASUREMENT
{
    DWORD           ID;
    WORD            Type;
    WORD            Units;
    double          Value;
} INSMEASUREMENT;

//--------------------------------------------------------------------
// These are the quality values that are assigned to the Quality 
// field to indicate quality of the signal.
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
#define GPS_QUALITY_NOFIX               0       // Fix not available
#define GPS_QUALITY_SPS                 1       // Standard Positioning Service 
#define GPS_QUALITY_DSPS                2       // Differential Standard Positioning Service 
#define GPS_QUALITY_PPS                 3       // Precise Positioning Service
#define GPS_QUALITY_RTK_FIXED           4       // RTK, fixed integers solution
#define GPS_QUALITY_RTK_FLOAT           5       // Float RTK
#define GPS_QUALITY_DR					6       // Dead Reckoning
#define GPS_QUALITY_MANUAL				7		// Manually input position
#define GPS_QUALITY_SIMLATOR			8		// Simulator mode
#define GPS_QUALITY_SBAS				9		// WAAS/EGNOS etc.
                                                        
//--------------------------------------------------------------------
// ArcPad supports a maximum of 32 satellites or channels.
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: 
//
#define GPS_MAXSATELLITES               32

//--------------------------------------------------------------------
// These are the values are assigned to Status.Track for each satellite
// that is being tracked to indicate its tracking status.
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define GPS_TRACK_NOTAVAILABLE          0
#define GPS_TRACK_AVAILABLE             1
#define GPS_TRACK_SEARCHING             2
#define GPS_TRACK_LOCKED                3
#define GPS_TRACK_INTERRUPTED           4
#define GPS_TRACK_UNHEALTHY             5

#define GPS_NAVIGATION_SYSTEM_UNKNOWN	1
#define GPS_NAVIGATION_SYSTEM_GPS		2
#define GPS_NAVIGATION_SYSTEM_SBAS		3
#define GPS_NAVIGATION_SYSTEM_GLONASS	4
#define GPS_NAVIGATION_SYSTEM_MIN		GPS_NAVIGATION_SYSTEM_UNKNOWN
#define GPS_NAVIGATION_SYSTEM_MAX		GPS_NAVIGATION_SYSTEM_GLONASS

//-------------------------------------------------------------------
// Satelite information for each satellite. This information is 
// used by ArcPad to show a sky view of the satellites and used
// for other calculations. There will be thirty two of these
// in the instrument structure.
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct GPSSATELLITE
{
    // Status of the satellite or channel.
    struct
    {
        DWORD       InView              : 1;                    // Currently in view 
                                                                // (1=yes, 0=no)
        DWORD       Track               : 3;                    // Tracking status. Assign one of
                                                                // above GPS_TRACK_* values.
        DWORD       InUse               : 1;                    // Being used for fix solutions
                                                                // (1=yes, 0=no)
        DWORD       Differential        : 1;                    // Differentially corrected
                                                                // (1=yes, 0=no)
    }   Status;                                                 
                                                                            
    short           Elevation;                                  // Sky view elevation (0-90°)
    short           Azimuth;                                    // Sky view azimuth (0-360°)
    double          SignalStrength;                             // Signal Strength (0-99 dB)
    WORD            Channel;                                    // Receiver channel tracking this 
                                                                // satellite. (Currently not used).
    INSMEASUREMENT  Measure[3];                                 // Addional measurements for
                                                                // future use.

	// ArcPad 10 SP1 extended satellite information

	WORD			NavigationSystem;							// 0 = Pre-10.0.1, 1=GPS, 2=SBAS, 3=GLONASS
	WORD			SatelliteID;
	WORD			Reserved[6];


} GPSSATELLITE;

//--------------------------------------------------------------------
// This is the INSTRUMENT structure used to pass GPS info and other 
// data between the GPSParse extension routine and ArcPad. 
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
typedef struct INSTRUMENT
{
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // Part 1. Application Mode section.
    // This section is controlled by ArcPad and it is read only for the
    // GPSParse routine. It passes status and state info concerning
    // ArcPad to the GPSParse routine
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    struct
    {
        DWORD           Debug           : 1;                    // Application is in GPS debug mode
                                                                // (1=yes, 0=no)
        DWORD           Capture         : 1;                    // Application is capturing data
                                                                // (1=yes, 0=no)
        DWORD           Averaging       : 1;                    // Application is averaging positions
                                                                // (1=yes, 0=no)
        DWORD           Tracklog        : 1;                    // Application is collecting data into
                                                                // a tracklog (1=yes, 0=no)
        SHAPETYPE   ShapeType;                                  // Application shape type
                                                                // What type of the current layer. 
                                                                // See shapes.h for SHAPE_TYPE codes.
        HANDLE          Handle[4];                              // Application handles (reserved for
                                                                // for future use)
    }   ApplicationMode;

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // Part 2. DataMask section.
    // These fields are controlled by both ArcPad and GPSParse.
    // GPSParse uses the above data mask flags (INS_DATA_*) to 
    // set the bits in DataMask to indicate which fields in the INSTRUMENT
    // structure have modified values. If GPSParse returns APEX_TRUE, 
    // ArcPad will "read" the data associated with DataMask
    // and then reset the flags in DataMask. 
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    DWORD               DataMask;                               // Bitmapped data mask INS_DATA...
    DWORD               EventMask;                              // Receiver specific event mask

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // Part 3. Data section.
    // These fields are controlled by GPSParse. GPSParse sets the
    // fields and then sets the data mask associated with the 
    // the field to indicate that the field is available to be 
    // read by ArcPad. If GPSParse returns APEX_TRUE, ArcPad will read 
    // the fields and reset the DataMask flags (Part 2). It will
    // not change the data fields.
    //
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Position (INS_DATA_POSITION)
    // See also Differential Position Info
    //++++++++++++++++++++++++++++++++++++++++++
    
    DWORD               PositionID;                             // Unique value for position
    SPOINTZ             Position;                               // Current fix coordinates 
                                                                // x=Longitude in decimal degrees with
                                                                // E=Positive and W=Negative.
                                                                // y=Latitude in decimal degrees with
                                                                // N=Postive and S=Negative.
                                                                // Z=Altitude in meters above or below
                                                                // mean sea level.
    SPOINTZ             PositionECEF;                           // ECEF fix coordinates

    struct
    {
        DWORD           Dimension       : 1;                    // 0=2D, 1=3D
        DWORD           Manual          : 1;                    // Manual 2D/3D
    }                   PositionMode;                           

    //++++++++++++++++++++++++++++++++++++++++++
    // Current position Date (INS_DATA_DATE)
    // Current position Time (INS_DATA_TIME)
    //++++++++++++++++++++++++++++++++++++++++++
    
    SYSTEMTIME          UTC;                                    // Current fix UTC date/time

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Fix Quality (INS_DATA_QUALITY)           
    // Set to GPS_QUALITY_NOFIX, GPS_QUALITY_SPS, GPS_QUALITY_DSPS or
    // GPS_QUALITY_PPS to indicate the quality of the signal.
    //++++++++++++++++++++++++++++++++++++++++++
                        
    WORD                Quality;                                // GPS_QUALITY_*

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Dilution of precision (INS_DATA_DOP)
    //++++++++++++++++++++++++++++++++++++++++++
                        
    double              GDOP;                                   // 
    double              PDOP;                                   // 
    double              HDOP;                                   //
    double              VDOP;                                   // 
    double              TDOP;                                   // Time dilution of precision
    
    //++++++++++++++++++++++++++++++++++++++++++
    // GPS (Estimated) error measures (INS_DATA_ERRORESTIMATES)
    //++++++++++++++++++++++++++++++++++++++++++
    
    SPOINTZ             PositionError;                          // Estimated position error x,y,z, 
                                                                // m=Overall error (meters)
    SPOINTZ             VelocityError;                          // Estimated velocity error x,y,z, 
                                                                // m=Overall error (meters/sec)
    double              TimeError;                              // Estimated Time error (meters)

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Differential Position Information (INS_DATA_POSITION)
    // See also GPS Position.
    //++++++++++++++++++++++++++++++++++++++++++
                            
    DWORD               DifferentialAge;                        // Time in seconds since last differntial update
    DWORD               ReferenceStationID;                     // Differential reference station identifier
                                                                
    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Speed/Heading (INS_DATA_COURSE)
    // See also Magnetic Variation 
    //++++++++++++++++++++++++++++++++++++++++++
                                                                
    double              SOG;                                    // Speed over ground (km/sec)
    double              COG;                                    // True Course over ground (decimal
                                                                // degrees North=0, increase clockwise)
    
    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Velocity (INS_DATA_VELOCITY)
    //++++++++++++++++++++++++++++++++++++++++++

    SPOINTZ             Velocity;                               // 3D Velocity
                                                                //  x = East velocity (meters/sec)
                                                                //  y = North velocity (meters/sec)
                                                                //  z = Vertical velocity (meters/sec)
                                                                //  m = Reserved

    //++++++++++++++++++++++++++++++++++++++++++
    // Magnetic Variation (INS_DATA_COURSE)
    // See also GPS heading/speed
    //++++++++++++++++++++++++++++++++++++++++++
    double              MagneticVariation;                      // Magnetic variation from magnetic 
                                                                // north to true north (decimal degrees)
                                                                // Easterly (+ve) variation subtracts
                                                                // from true
                                                                // Westerly (-ve) variation add to true

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Map datum (INS_DATA_DATUM)
    //++++++++++++++++++++++++++++++++++++++++++
                                                            
    DWORD               DatumID;                                // Vendor specific datum identifier
    BYTE                DatumName[32];                          // Vendor specific datum name
    double              DatumSemiMajorAxis;                     // Spheroid semi-major axis
    double              DatumFlattening;                        // Spheroid flattening
    SPOINTZ             DatumShift;                             // DX,DY,DY from WGS84
    SPOINTZ             DatumRotation;                          // RX,RY,RZ,SF from WGS84
    DWORD               DatumMethod;                            // EPSG Datum shift method
    DWORD               DatumEPSGID;                            // EPSG Datum ID

    //++++++++++++++++++++++++++++++++++++++++++
    // Magnetic Compass (INS_DATA_COMPASS)
    //++++++++++++++++++++++++++++++++++++++++++

    double              CompassHeading;                         // decimal degrees, North=0.

    //++++++++++++++++++++++++++++++++++++++++++
    // Depth Sounder (INS_DATA_SOUNDER)
    //++++++++++++++++++++++++++++++++++++++++++

    double              WaterDepth;                             // Depth below transducer 
                                                                // (meters)
    double              TransducerDepthOffset;                  // Transducer depth below surface
                                                                // (meters)
    double              WaterTemperature;                       // Water temperature at transducer
                                                                // (°C)

    //++++++++++++++++++++++++++++++++++++++++++
    // Weather (INS_DATA_WEATHER)
    //++++++++++++++++++++++++++++++++++++++++++

    double              AirTemperature;                         // (°C)
    double              BarometricPressure;                     // (millibars)
    double              DewPoint;                               // (°C)
    double              AbsoluteHumidity;                       // (%)
    double              RelativeHumidity;                       // (%)
    double              WindSpeed;                              // TBD 
    double              TrueWindDirection;                      // TBD decimal degrees?
    double              MagneticWindDirection;                  // TBD decimal degrees?
    double              ApparanetWindDirection;                 // TBD decimal degrees?
    double              WeatherReserved[5];                     // Reserved

    //++++++++++++++++++++++++++++++++++++++++++
    // Rangefinder (INS_DATA_RANGE)
    //++++++++++++++++++++++++++++++++++++++++++

    double              RangeDistance;                          // Slope range (meters)
    double              RangeAzimuth;                           // Range Bearing/Azimuth 
                                                                // (True decimal degrees)
    double              RangeInclination;                       // Range inclination from horizontal 
                                                                //  (decimal degrees)
    double              RangeReserved[5];                       // Reserved values

    //++++++++++++++++++++++++++++++++++++++++++
    // Trigger/button (INS_DATA_TRIGGER)
    //++++++++++++++++++++++++++++++++++++++++++

    DWORD               TriggerID;                              // Trigger/button identifier
    BYTE                TriggerTag[20];                         // Trigger tag

    //++++++++++++++++++++++++++++++++++++++++++
    // GPS Satellites (INS_DATA_SATELLITES)
    //++++++++++++++++++++++++++++++++++++++++++

    WORD                SatelliteChannels;                      // Number of satellite supported
                                                                // by the receiver
    WORD                SatellitesVisible;                      // Number of satellites in view
    WORD                SatellitesUsed;                         // Number of satellites used for
                                                                // measurement
    double              MaskAngle;                              // Satellite mask angle
                                                                // Angle from horizon in degrees.
                                                                // if Azmuth < MaskAngle then
                                                                // satellite not shown.
    double              GPSWeek;                                // GPS week

    GPSSATELLITE        Satellite[GPS_MAXSATELLITES];

    //++++++++++++++++++++++++++++++++++++++++++
    // Additonal sensor measurements (INS_DATA_MEASUREMENTS)
    //++++++++++++++++++++++++++++++++++++++++++
    
    DWORD               MeasurementStatus;
    INSMEASUREMENT      Measurement[32];

    //++++++++++++++++++++++++++++++++++++++++++
    // Packet details (INS_DATA_INTERNAL)
    // See also Sensor status.
    //++++++++++++++++++++++++++++++++++++++++++
    
    DWORD               PacketID;                               // Packet identifier
    DWORD               PacketSequenceNumber;                   // Packet sequence number
    BYTE                PacketName[40];                         // Packet name eg. NMEA Sentence address field
    BYTE                PacketData[256];                        // Packet data (may contain raw data, NMEA sentence etc.)

    //++++++++++++++++++++++++++++++++++++++++++
    // Sensor status and other receiver information (INS_DATA_INTERNAL)
    // See also Packet details.
    //++++++++++++++++++++++++++++++++++++++++++

    DWORD               InstrumentType;                         // Instrument type (can be multiple)
    DWORD               InstrumentFeatures;                     // Features available on receiver/instrument
    INSMANUFACTURER     Manufacturer;                           // Instrument manufacturer
    DWORD               ProductID;                              // Vendor specific product code
    TCHAR               Description[40];                        // Device Model Description
    TCHAR               Revision[40];                           // Device Software revision
    double              InternalTemperature;                    // Sensor internal temperature
    double              SensorReserved[5];                      // Reserved

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    // Part 4. Error section.
    // These fields are controlled both by GPSParse and ArcPad.
    // GPSParse sets the error code if there is one and sets the
    // INS_DATA_ERROR flag in DataMask and GPSParse returns APEX_FALSE.
    // If the debug error window is in use ArcPad will display
    // the error code and the ErrorDescription. It will then reset
    // the ErrorCode field. It will not read any of the other fields
    // in Part 3 and it will not reset the other DataMask flags.
    //
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  

    //++++++++++++++++++++++++++++++++++
    // Error information (INS_DATA_ERROR)
    //+++++++++++++++++++++++++++++++++++

    DWORD               ErrorCode;                              // Error code
    TCHAR               ErrorDescription[80];                   // Error description/additonal details

    //++++++++++++++++++++++++++++++++++++++++++
    // Sensor battery status and other receiver information (INS_DATA_BATTERY)
    //++++++++++++++++++++++++++++++++++++++++++
	
	INSBATTERYTECHNOLOGY	BatteryTechnology;						// 0 (Unknown)
	WORD					BatteryCharge;							// Battery charge 0% -> 100%
	double					BatteryVolts;							// Battery charge in volts
	BYTE					BatteryReserved[16];					// Reserved

} INSTRUMENT;

//--------------------------------------------------------------------
// Clear satellite information
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define GPSClearSatellites(INS) \
    { \
        memset((INS)->Satellite, 0, sizeof((INS)->Satellite)); \
    }

//--------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif
