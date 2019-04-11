# NMEAFilter v1.0.0

NMEAFilter is an ArcPad extension that whitelists (and blacklsit) NMEA sentences.

Without this extension, ArcPad will attempt to process all NMEA messages that it receives from the Serial Port. With this extension, one can selectively cherry pick specific message that will be used by ArcPad.

## Installing NMEAFilter

To install NMEAFilter, you need to have ArcPad installed. This extension is compatible with almost all versions of ArcPad since ArcPad 6.0.3.

 1. Download NMEAFilter.dll from the Releases folder
 2. Install it to your ArcPad extensions folder (C:\Program Files (x86)\ArcGIS\ArcPad10.2\Extensions)
 3. Set NMEAFILTERS environment variable to customize (see NMEAFILTERS wiki)
 4. Set NMEAFILTERS_DEBUG to generate troubleshooting messages (see NMEAFILTERS_DEBUG wiki)
 
