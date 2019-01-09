//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: CATEGORY_FOLIO
//
// MessageText:
//
// Folio
//
#define CATEGORY_FOLIO                   0x00000001L

//
// MessageId: EVENT_ID_FOLIO
//
// MessageText:
//
// %1.%n
//
#define EVENT_ID_FOLIO                   0x00000065L

//
// MessageId: MSG_NEWLINE
//
// MessageText:
//
// %n
//
#define MSG_NEWLINE                      0x000000C9L

//
// MessageId: MSG_TAB
//
// MessageText:
//
// %t
//
#define MSG_TAB                          0x000000CAL

