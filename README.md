# NMEAFilter v1.0.0

NMEAFilter is an ArcPad extension that whitelists (and blacklist) NMEA sentences.

Without this extension, ArcPad will attempt to process all NMEA messages that it receives from the Serial Port. With this extension, you can cherry pick specific messages that will be used by ArcPad.

## Installing NMEAFilter

To install NMEAFilter, you need to have ArcPad installed. This extension is compatible with ArcPad 6.0.3+.

 1. Download NMEAFilter.dll from the [Releases folder](https://github.com/stephenquan/NMEAFilter/releases)
 2. Copy it to your ArcPad extensions folder (C:\Program Files (x86)\ArcGIS\ArcPad10.2\Extensions)
 3. Optionally set NMEAFILTERS environment variable to customize ([see NMEAFILTERS wiki](https://github.com/stephenquan/NMEAFilter/wiki/Environment-Variable:-NMEAFILTERS))
 4. Optionally set NMEAFILTERS_DEBUG to generate troubleshooting messages ([see NMEAFILTERS_DEBUG wiki](https://github.com/stephenquan/NMEAFilter/wiki/Environment-Variable:-NMEAFILTERS_DEBUG))
 
