/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Graphics Pipeline Extension
 *
 * Copyright 2013 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FREERDP_CHANNEL_RDPGFX_H
#define FREERDP_CHANNEL_RDPGFX_H

#include <freerdp/api.h>
#include <freerdp/dvc.h>
#include <freerdp/types.h>

#define RDPGFX_DVC_CHANNEL_NAME "Microsoft::Windows::RDS::Graphics"

/**
 * Common Data Types
 */

struct _RDPGFX_POINT16
{
	UINT16 x;
	UINT16 y;
};
typedef struct _RDPGFX_POINT16 RDPGFX_POINT16;

struct _RDPGFX_COLOR32
{
	BYTE B;
	BYTE G;
	BYTE R;
	BYTE XA;
};
typedef struct _RDPGFX_COLOR32 RDPGFX_COLOR32;

#define GFX_PIXEL_FORMAT_XRGB_8888 0x20
#define GFX_PIXEL_FORMAT_ARGB_8888 0x21

typedef BYTE RDPGFX_PIXELFORMAT;

#define RDPGFX_CMDID_UNUSED_0000 0x0000
#define RDPGFX_CMDID_WIRETOSURFACE_1 0x0001
#define RDPGFX_CMDID_WIRETOSURFACE_2 0x0002
#define RDPGFX_CMDID_DELETEENCODINGCONTEXT 0x0003
#define RDPGFX_CMDID_SOLIDFILL 0x0004
#define RDPGFX_CMDID_SURFACETOSURFACE 0x0005
#define RDPGFX_CMDID_SURFACETOCACHE 0x0006
#define RDPGFX_CMDID_CACHETOSURFACE 0x0007
#define RDPGFX_CMDID_EVICTCACHEENTRY 0x0008
#define RDPGFX_CMDID_CREATESURFACE 0x0009
#define RDPGFX_CMDID_DELETESURFACE 0x000A
#define RDPGFX_CMDID_STARTFRAME 0x000B
#define RDPGFX_CMDID_ENDFRAME 0x000C
#define RDPGFX_CMDID_FRAMEACKNOWLEDGE 0x000D
#define RDPGFX_CMDID_RESETGRAPHICS 0x000E
#define RDPGFX_CMDID_MAPSURFACETOOUTPUT 0x000F
#define RDPGFX_CMDID_CACHEIMPORTOFFER 0x0010
#define RDPGFX_CMDID_CACHEIMPORTREPLY 0x0011
#define RDPGFX_CMDID_CAPSADVERTISE 0x0012
#define RDPGFX_CMDID_CAPSCONFIRM 0x0013
#define RDPGFX_CMDID_UNUSED_0014 0x0014
#define RDPGFX_CMDID_MAPSURFACETOWINDOW 0x0015
#define RDPGFX_CMDID_QOEFRAMEACKNOWLEDGE 0x0016
#define RDPGFX_CMDID_MAPSURFACETOSCALEDOUTPUT 0x0017
#define RDPGFX_CMDID_MAPSURFACETOSCALEDWINDOW 0x0018

#define RDPGFX_HEADER_SIZE 8

struct _RDPGFX_HEADER
{
	UINT16 cmdId;
	UINT16 flags;
	UINT32 pduLength;
};
typedef struct _RDPGFX_HEADER RDPGFX_HEADER;

/**
 * Capability Sets [MS-RDPEGFX] 2.2.3
 */

#define RDPGFX_CAPVERSION_8 0x00080004   /** [MS-RDPEGFX] 2.2.3.1 */
#define RDPGFX_CAPVERSION_81 0x00080105  /** [MS-RDPEGFX] 2.2.3.2 */
#define RDPGFX_CAPVERSION_10 0x000A0002  /** [MS-RDPEGFX] 2.2.3.3 */
#define RDPGFX_CAPVERSION_101 0x000A0100 /** [MS-RDPEGFX] 2.2.3.4 */
#define RDPGFX_CAPVERSION_102 0x000A0200 /** [MS-RDPEGFX] 2.2.3.5 */
#define RDPGFX_CAPVERSION_103 0x000A0301 /** [MS-RDPEGFX] 2.2.3.6 */
#define RDPGFX_CAPVERSION_104 0x000A0400 /** [MS-RDPEGFX] 2.2.3.7 */
#define RDPGFX_CAPVERSION_105 0x000A0502 /** [MS-RDPEGFX] 2.2.3.8 */
#define RDPGFX_CAPVERSION_106 0x000A0601 /** [MS-RDPEGFX] 2.2.3.9 */

#define RDPGFX_NUMBER_CAPSETS 9
#define RDPGFX_CAPSET_BASE_SIZE 8

struct _RDPGFX_CAPSET
{
	UINT32 version;
	UINT32 length;
	UINT32 flags;
};
typedef struct _RDPGFX_CAPSET RDPGFX_CAPSET;

#define RDPGFX_CAPS_FLAG_THINCLIENT 0x00000001U     /* 8.0+ */
#define RDPGFX_CAPS_FLAG_SMALL_CACHE 0x00000002U    /* 8.0+ */
#define RDPGFX_CAPS_FLAG_AVC420_ENABLED 0x00000010U /* 8.1+ */
#define RDPGFX_CAPS_FLAG_AVC_DISABLED 0x00000020U   /* 10.0+ */
#define RDPGFX_CAPS_FLAG_AVC_THINCLIENT 0x00000040U /* 10.3+ */

struct _RDPGFX_CAPSET_VERSION8
{
	UINT32 version;
	UINT32 capsDataLength;
	UINT32 flags;
};
typedef struct _RDPGFX_CAPSET_VERSION8 RDPGFX_CAPSET_VERSION8;

struct _RDPGFX_CAPSET_VERSION81
{
	UINT32 version;
	UINT32 capsDataLength;
	UINT32 flags;
};
typedef struct _RDPGFX_CAPSET_VERSION81 RDPGFX_CAPSET_VERSION81;

struct _RDPGFX_CAPSET_VERSION10
{
	UINT32 version;
	UINT32 capsDataLength;
	UINT32 flags;
};
typedef struct _RDPGFX_CAPSET_VERSION10 RDPGFX_CAPSET_VERSION10;

/**
 * Graphics Messages
 */

#define RDPGFX_CODECID_UNCOMPRESSED 0x0000
#define RDPGFX_CODECID_CAVIDEO 0x0003
#define RDPGFX_CODECID_CLEARCODEC 0x0008
#define RDPGFX_CODECID_PLANAR 0x000A
#define RDPGFX_CODECID_AVC420 0x000B
#define RDPGFX_CODECID_ALPHA 0x000C
#define RDPGFX_CODECID_AVC444 0x000E
#define RDPGFX_CODECID_AVC444v2 0x000F

#define RDPGFX_WIRE_TO_SURFACE_PDU_1_SIZE 17

struct _RDPGFX_WIRE_TO_SURFACE_PDU_1
{
	UINT16 surfaceId;
	UINT16 codecId;
	RDPGFX_PIXELFORMAT pixelFormat;
	RECTANGLE_16 destRect;
	UINT32 bitmapDataLength;
	BYTE* bitmapData;
};
typedef struct _RDPGFX_WIRE_TO_SURFACE_PDU_1 RDPGFX_WIRE_TO_SURFACE_PDU_1;

#define RDPGFX_CODECID_CAPROGRESSIVE 0x0009
#define RDPGFX_CODECID_CAPROGRESSIVE_V2 0x000D

#define RDPGFX_WIRE_TO_SURFACE_PDU_2_SIZE 13

struct _RDPGFX_WIRE_TO_SURFACE_PDU_2
{
	UINT16 surfaceId;
	UINT16 codecId;
	UINT32 codecContextId;
	RDPGFX_PIXELFORMAT pixelFormat;
	UINT32 bitmapDataLength;
	BYTE* bitmapData;
};
typedef struct _RDPGFX_WIRE_TO_SURFACE_PDU_2 RDPGFX_WIRE_TO_SURFACE_PDU_2;

struct _RDPGFX_SURFACE_COMMAND
{
	UINT32 surfaceId;
	UINT32 codecId;
	UINT32 contextId;
	UINT32 format; /* FreeRDP color format. @see freerdp/codec/color.h */
	UINT32 left;
	UINT32 top;
	UINT32 right;
	UINT32 bottom;
	UINT32 width;
	UINT32 height;
	UINT32 length;
	BYTE* data;
	void* extra;
};
typedef struct _RDPGFX_SURFACE_COMMAND RDPGFX_SURFACE_COMMAND;

struct _RDPGFX_DELETE_ENCODING_CONTEXT_PDU
{
	UINT16 surfaceId;
	UINT32 codecContextId;
};
typedef struct _RDPGFX_DELETE_ENCODING_CONTEXT_PDU RDPGFX_DELETE_ENCODING_CONTEXT_PDU;

struct _RDPGFX_SOLID_FILL_PDU
{
	UINT16 surfaceId;
	RDPGFX_COLOR32 fillPixel;
	UINT16 fillRectCount;
	RECTANGLE_16* fillRects;
};
typedef struct _RDPGFX_SOLID_FILL_PDU RDPGFX_SOLID_FILL_PDU;

struct _RDPGFX_SURFACE_TO_SURFACE_PDU
{
	UINT16 surfaceIdSrc;
	UINT16 surfaceIdDest;
	RECTANGLE_16 rectSrc;
	UINT16 destPtsCount;
	RDPGFX_POINT16* destPts;
};
typedef struct _RDPGFX_SURFACE_TO_SURFACE_PDU RDPGFX_SURFACE_TO_SURFACE_PDU;

struct _RDPGFX_SURFACE_TO_CACHE_PDU
{
	UINT16 surfaceId;
	UINT64 cacheKey;
	UINT16 cacheSlot;
	RECTANGLE_16 rectSrc;
};
typedef struct _RDPGFX_SURFACE_TO_CACHE_PDU RDPGFX_SURFACE_TO_CACHE_PDU;

struct _RDPGFX_CACHE_TO_SURFACE_PDU
{
	UINT16 cacheSlot;
	UINT16 surfaceId;
	UINT16 destPtsCount;
	RDPGFX_POINT16* destPts;
};
typedef struct _RDPGFX_CACHE_TO_SURFACE_PDU RDPGFX_CACHE_TO_SURFACE_PDU;

struct _RDPGFX_EVICT_CACHE_ENTRY_PDU
{
	UINT16 cacheSlot;
};
typedef struct _RDPGFX_EVICT_CACHE_ENTRY_PDU RDPGFX_EVICT_CACHE_ENTRY_PDU;

struct _RDPGFX_CREATE_SURFACE_PDU
{
	UINT16 surfaceId;
	UINT16 width;
	UINT16 height;
	RDPGFX_PIXELFORMAT pixelFormat;
};
typedef struct _RDPGFX_CREATE_SURFACE_PDU RDPGFX_CREATE_SURFACE_PDU;

struct _RDPGFX_DELETE_SURFACE_PDU
{
	UINT16 surfaceId;
};
typedef struct _RDPGFX_DELETE_SURFACE_PDU RDPGFX_DELETE_SURFACE_PDU;

#define RDPGFX_START_FRAME_PDU_SIZE 8

struct _RDPGFX_START_FRAME_PDU
{
	UINT32 timestamp;
	UINT32 frameId;
};
typedef struct _RDPGFX_START_FRAME_PDU RDPGFX_START_FRAME_PDU;

#define RDPGFX_END_FRAME_PDU_SIZE 4

struct _RDPGFX_END_FRAME_PDU
{
	UINT32 frameId;
};
typedef struct _RDPGFX_END_FRAME_PDU RDPGFX_END_FRAME_PDU;

#define QUEUE_DEPTH_UNAVAILABLE 0x00000000
#define SUSPEND_FRAME_ACKNOWLEDGEMENT 0xFFFFFFFF

struct _RDPGFX_FRAME_ACKNOWLEDGE_PDU
{
	UINT32 queueDepth;
	UINT32 frameId;
	UINT32 totalFramesDecoded;
};
typedef struct _RDPGFX_FRAME_ACKNOWLEDGE_PDU RDPGFX_FRAME_ACKNOWLEDGE_PDU;

struct _RDPGFX_RESET_GRAPHICS_PDU
{
	UINT32 width;
	UINT32 height;
	UINT32 monitorCount;
	MONITOR_DEF* monitorDefArray;
};
typedef struct _RDPGFX_RESET_GRAPHICS_PDU RDPGFX_RESET_GRAPHICS_PDU;

struct _RDPGFX_MAP_SURFACE_TO_OUTPUT_PDU
{
	UINT16 surfaceId;
	UINT16 reserved;
	UINT32 outputOriginX;
	UINT32 outputOriginY;
};
typedef struct _RDPGFX_MAP_SURFACE_TO_OUTPUT_PDU RDPGFX_MAP_SURFACE_TO_OUTPUT_PDU;

struct _RDPGFX_MAP_SURFACE_TO_SCALED_OUTPUT_PDU
{
	UINT16 surfaceId;
	UINT16 reserved;
	UINT32 outputOriginX;
	UINT32 outputOriginY;
	UINT32 targetWidth;
	UINT32 targetHeight;
};
typedef struct _RDPGFX_MAP_SURFACE_TO_SCALED_OUTPUT_PDU RDPGFX_MAP_SURFACE_TO_SCALED_OUTPUT_PDU;

struct _RDPGFX_CACHE_ENTRY_METADATA
{
	UINT64 cacheKey;
	UINT32 bitmapLength;
};
typedef struct _RDPGFX_CACHE_ENTRY_METADATA RDPGFX_CACHE_ENTRY_METADATA;

struct _RDPGFX_CACHE_IMPORT_OFFER_PDU
{
	UINT16 cacheEntriesCount;
	RDPGFX_CACHE_ENTRY_METADATA* cacheEntries;
};
typedef struct _RDPGFX_CACHE_IMPORT_OFFER_PDU RDPGFX_CACHE_IMPORT_OFFER_PDU;

struct _RDPGFX_CACHE_IMPORT_REPLY_PDU
{
	UINT16 importedEntriesCount;
	UINT16* cacheSlots;
};
typedef struct _RDPGFX_CACHE_IMPORT_REPLY_PDU RDPGFX_CACHE_IMPORT_REPLY_PDU;

struct _RDPGFX_CAPS_ADVERTISE_PDU
{
	UINT16 capsSetCount;
	RDPGFX_CAPSET* capsSets;
};
typedef struct _RDPGFX_CAPS_ADVERTISE_PDU RDPGFX_CAPS_ADVERTISE_PDU;

struct _RDPGFX_CAPS_CONFIRM_PDU
{
	RDPGFX_CAPSET* capsSet;
};
typedef struct _RDPGFX_CAPS_CONFIRM_PDU RDPGFX_CAPS_CONFIRM_PDU;

struct _RDPGFX_MAP_SURFACE_TO_WINDOW_PDU
{
	UINT16 surfaceId;
	UINT64 windowId;
	UINT32 mappedWidth;
	UINT32 mappedHeight;
};
typedef struct _RDPGFX_MAP_SURFACE_TO_WINDOW_PDU RDPGFX_MAP_SURFACE_TO_WINDOW_PDU;

struct _RDPGFX_MAP_SURFACE_TO_SCALED_WINDOW_PDU
{
	UINT16 surfaceId;
	UINT64 windowId;
	UINT32 mappedWidth;
	UINT32 mappedHeight;
	UINT32 targetWidth;
	UINT32 targetHeight;
};
typedef struct _RDPGFX_MAP_SURFACE_TO_SCALED_WINDOW_PDU RDPGFX_MAP_SURFACE_TO_SCALED_WINDOW_PDU;

/* H264 */

struct _RDPGFX_H264_QUANT_QUALITY
{
	BYTE qpVal;
	BYTE qualityVal;

	BYTE qp;
	BYTE r;
	BYTE p;
};
typedef struct _RDPGFX_H264_QUANT_QUALITY RDPGFX_H264_QUANT_QUALITY;

struct _RDPGFX_H264_METABLOCK
{
	UINT32 numRegionRects;
	RECTANGLE_16* regionRects;
	RDPGFX_H264_QUANT_QUALITY* quantQualityVals;
};
typedef struct _RDPGFX_H264_METABLOCK RDPGFX_H264_METABLOCK;

struct _RDPGFX_AVC420_BITMAP_STREAM
{
	RDPGFX_H264_METABLOCK meta;
	UINT32 length;
	BYTE* data;
};
typedef struct _RDPGFX_AVC420_BITMAP_STREAM RDPGFX_AVC420_BITMAP_STREAM;

struct _RDPGFX_AVC444_BITMAP_STREAM
{
	UINT32 cbAvc420EncodedBitstream1;
	BYTE LC;
	RDPGFX_AVC420_BITMAP_STREAM bitstream[2];
};
typedef struct _RDPGFX_AVC444_BITMAP_STREAM RDPGFX_AVC444_BITMAP_STREAM;

struct _RDPGFX_QOE_FRAME_ACKNOWLEDGE_PDU
{
	UINT32 frameId;
	UINT32 timestamp;
	UINT16 timeDiffSE;
	UINT16 timeDiffEDR;
};
typedef struct _RDPGFX_QOE_FRAME_ACKNOWLEDGE_PDU RDPGFX_QOE_FRAME_ACKNOWLEDGE_PDU;

#endif /* FREERDP_CHANNEL_RDPGFX_H */
