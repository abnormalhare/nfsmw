#ifndef _VERSION_H
#define _VERSION_H

#define VERSION_PREVIEW_09_10 0
#define VERSION_USA 1

#if VERSION == VERSION_PREVIEW_09_10
#define VERSION_SELECT(PREVIEW, US) (PREVIEW)
#elif VERSION == VERSION_USA
#define VERSION_SELECT(PREVIEW, US) (USA)
#endif

#endif
