#include "dq_otp.h"
#include <math.h>
#include "string.h"

//#define __DQ_LIB_LOG_ENABLED__

#ifdef __DQ_LIB_LOG_ENABLED__
#include "app_uart.h"
#endif
//#include "SEGGER_RTT.h"
//#include "SEGGER_RTT_Conf.h"

#ifdef __LOCK_FP_SUPPORT__

const unsigned char otpKeyMap[1000][5] = {
	{0x43,0x16,0x98,0x25,0x07},{0x26,0x41,0x53,0x89,0x70},{0x92,0x35,0x64,0x70,0x81},{0x72,0x59,0x03,0x18,0x46},{0x02,0x85,0x19,0x63,0x74},
	{0x12,0x05,0x69,0x43,0x87},{0x21,0x69,0x50,0x37,0x84},{0x10,0x63,0x52,0x74,0x89},{0x09,0x58,0x26,0x17,0x34},{0x18,0x95,0x42,0x76,0x30},
	{0x20,0x97,0x86,0x53,0x14},{0x13,0x94,0x05,0x28,0x67},{0x89,0x43,0x70,0x12,0x65},{0x91,0x82,0x73,0x60,0x54},{0x15,0x97,0x86,0x34,0x20},
	{0x78,0x51,0x20,0x43,0x96},{0x58,0x70,0x96,0x12,0x34},{0x56,0x91,0x32,0x84,0x07},{0x97,0x53,0x68,0x10,0x24},{0x50,0x19,0x83,0x26,0x74},
	{0x47,0x53,0x80,0x16,0x29},{0x89,0x25,0x46,0x37,0x10},{0x52,0x06,0x19,0x73,0x48},{0x18,0x03,0x56,0x72,0x49},{0x21,0x40,0x93,0x65,0x87},
	{0x94,0x16,0x85,0x20,0x37},{0x42,0x98,0x61,0x35,0x07},{0x03,0x21,0x49,0x58,0x76},{0x12,0x63,0x54,0x09,0x78},{0x46,0x27,0x98,0x51,0x03},
	{0x02,0x51,0x73,0x84,0x69},{0x20,0x97,0x51,0x84,0x36},{0x16,0x87,0x50,0x32,0x94},{0x93,0x26,0x47,0x18,0x50},{0x14,0x23,0x60,0x78,0x59},
	{0x03,0x78,0x29,0x15,0x46},{0x85,0x10,0x79,0x43,0x62},{0x96,0x71,0x05,0x82,0x43},{0x10,0x58,0x24,0x63,0x97},{0x81,0x62,0x93,0x07,0x45},
	{0x47,0x80,0x23,0x91,0x65},{0x67,0x80,0x31,0x52,0x94},{0x56,0x79,0x84,0x21,0x30},{0x97,0x53,0x46,0x01,0x28},{0x19,0x46,0x32,0x80,0x57},
	{0x37,0x48,0x90,0x62,0x51},{0x93,0x70,0x81,0x52,0x64},{0x72,0x14,0x05,0x93,0x86},{0x40,0x87,0x93,0x15,0x62},{0x10,0x34,0x68,0x97,0x52},
	{0x29,0x07,0x14,0x65,0x38},{0x59,0x73,0x81,0x20,0x64},{0x03,0x79,0x15,0x48,0x62},{0x85,0x02,0x76,0x19,0x43},{0x83,0x74,0x69,0x01,0x52},
	{0x63,0x10,0x48,0x57,0x92},{0x08,0x72,0x94,0x53,0x61},{0x98,0x41,0x63,0x25,0x70},{0x39,0x65,0x41,0x07,0x28},{0x53,0x96,0x81,0x07,0x24},
	{0x43,0x05,0x81,0x27,0x69},{0x17,0x09,0x65,0x42,0x38},{0x25,0x70,0x94,0x68,0x13},{0x36,0x95,0x87,0x24,0x01},{0x52,0x10,0x48,0x63,0x97},
	{0x14,0x27,0x83,0x59,0x60},{0x23,0x69,0x15,0x70,0x48},{0x17,0x90,0x84,0x26,0x35},{0x89,0x36,0x50,0x42,0x17},{0x81,0x64,0x70,0x92,0x35},
	{0x95,0x47,0x26,0x83,0x01},{0x60,0x43,0x59,0x27,0x81},{0x91,0x65,0x48,0x37,0x20},{0x37,0x09,0x24,0x58,0x16},{0x67,0x84,0x13,0x95,0x02},
	{0x21,0x70,0x63,0x58,0x49},{0x89,0x34,0x01,0x56,0x72},{0x28,0x34,0x59,0x16,0x70},{0x20,0x14,0x79,0x86,0x53},{0x61,0x29,0x75,0x84,0x30},
	{0x32,0x91,0x75,0x08,0x64},{0x34,0x01,0x59,0x68,0x72},{0x12,0x08,0x74,0x56,0x39},{0x10,0x48,0x95,0x63,0x27},{0x01,0x26,0x87,0x94,0x53},
	{0x25,0x84,0x10,0x76,0x39},{0x54,0x02,0x13,0x79,0x68},{0x17,0x09,0x48,0x36,0x25},{0x30,0x29,0x81,0x76,0x45},{0x70,0x25,0x64,0x38,0x19},
	{0x30,0x85,0x96,0x71,0x42},{0x20,0x17,0x98,0x64,0x35},{0x64,0x79,0x20,0x18,0x35},{0x58,0x26,0x19,0x07,0x43},{0x78,0x43,0x59,0x06,0x21},
	{0x04,0x75,0x23,0x96,0x81},{0x58,0x70,0x64,0x21,0x93},{0x53,0x74,0x86,0x91,0x02},{0x52,0x49,0x87,0x03,0x61},{0x98,0x13,0x02,0x67,0x54},
	{0x82,0x05,0x69,0x14,0x37},{0x58,0x79,0x26,0x41,0x30},{0x58,0x42,0x63,0x97,0x10},{0x40,0x32,0x19,0x56,0x87},{0x80,0x24,0x17,0x96,0x53},
	{0x62,0x51,0x79,0x43,0x08},{0x52,0x04,0x93,0x87,0x61},{0x57,0x03,0x89,0x42,0x16},{0x83,0x46,0x19,0x57,0x02},{0x84,0x65,0x92,0x13,0x07},
	{0x10,0x46,0x92,0x53,0x87},{0x75,0x13,0x09,0x84,0x62},{0x75,0x03,0x94,0x82,0x61},{0x59,0x62,0x07,0x41,0x38},{0x59,0x48,0x61,0x23,0x07},
	{0x02,0x38,0x46,0x75,0x19},{0x73,0x49,0x20,0x58,0x16},{0x52,0x86,0x47,0x91,0x30},{0x57,0x06,0x39,0x41,0x28},{0x83,0x50,0x71,0x26,0x94},
	{0x05,0x16,0x43,0x29,0x78},{0x08,0x15,0x27,0x94,0x36},{0x87,0x02,0x49,0x65,0x13},{0x53,0x94,0x18,0x72,0x06},{0x06,0x93,0x18,0x24,0x57},
	{0x08,0x94,0x35,0x17,0x62},{0x05,0x12,0x38,0x96,0x47},{0x83,0x01,0x72,0x95,0x46},{0x32,0x78,0x15,0x90,0x46},{0x17,0x59,0x43,0x62,0x80},
	{0x38,0x09,0x41,0x67,0x25},{0x92,0x41,0x83,0x67,0x50},{0x08,0x96,0x25,0x17,0x34},{0x01,0x65,0x47,0x39,0x28},{0x69,0x01,0x45,0x23,0x78},
	{0x38,0x12,0x94,0x57,0x60},{0x39,0x15,0x48,0x27,0x60},{0x51,0x89,0x67,0x32,0x04},{0x23,0x91,0x74,0x68,0x50},{0x69,0x48,0x17,0x30,0x52},
	{0x76,0x80,0x49,0x31,0x52},{0x26,0x39,0x80,0x41,0x57},{0x01,0x42,0x79,0x65,0x83},{0x64,0x71,0x83,0x09,0x52},{0x28,0x95,0x64,0x07,0x31},
	{0x72,0x53,0x41,0x90,0x86},{0x89,0x57,0x16,0x30,0x24},{0x38,0x97,0x60,0x45,0x12},{0x39,0x06,0x21,0x75,0x48},{0x31,0x85,0x26,0x94,0x70},
	{0x47,0x59,0x86,0x32,0x01},{0x05,0x14,0x89,0x67,0x32},{0x46,0x83,0x05,0x19,0x27},{0x83,0x50,0x17,0x96,0x24},{0x15,0x93,0x20,0x78,0x46},
	{0x36,0x21,0x87,0x45,0x90},{0x06,0x72,0x34,0x85,0x19},{0x02,0x75,0x64,0x89,0x13},{0x83,0x06,0x24,0x71,0x59},{0x19,0x75,0x60,0x83,0x24},
	{0x64,0x92,0x30,0x18,0x57},{0x15,0x69,0x84,0x27,0x03},{0x47,0x31,0x59,0x02,0x68},{0x32,0x04,0x65,0x91,0x78},{0x34,0x97,0x61,0x80,0x25},
	{0x04,0x76,0x28,0x91,0x35},{0x32,0x06,0x84,0x57,0x19},{0x23,0x70,0x19,0x68,0x45},{0x06,0x37,0x98,0x15,0x24},{0x48,0x97,0x56,0x10,0x32},
	{0x61,0x85,0x49,0x72,0x30},{0x17,0x85,0x64,0x92,0x03},{0x34,0x81,0x27,0x95,0x06},{0x50,0x16,0x47,0x82,0x93},{0x52,0x48,0x19,0x03,0x67},
	{0x16,0x50,0x27,0x34,0x98},{0x53,0x69,0x82,0x71,0x40},{0x27,0x65,0x04,0x18,0x93},{0x08,0x46,0x72,0x59,0x13},{0x35,0x79,0x26,0x10,0x48},
	{0x15,0x32,0x79,0x04,0x68},{0x47,0x61,0x29,0x83,0x05},{0x42,0x38,0x79,0x10,0x65},{0x32,0x91,0x64,0x05,0x78},{0x72,0x09,0x64,0x85,0x31},
	{0x90,0x83,0x24,0x51,0x67},{0x39,0x25,0x40,0x86,0x71},{0x62,0x98,0x73,0x15,0x40},{0x50,0x14,0x39,0x27,0x68},{0x14,0x62,0x79,0x85,0x03},
	{0x23,0x79,0x41,0x06,0x85},{0x20,0x14,0x38,0x95,0x67},{0x59,0x74,0x26,0x80,0x13},{0x75,0x13,0x28,0x46,0x90},{0x07,0x21,0x63,0x59,0x48},
	{0x98,0x16,0x50,0x23,0x47},{0x59,0x62,0x71,0x48,0x30},{0x84,0x71,0x59,0x26,0x30},{0x35,0x68,0x41,0x27,0x09},{0x63,0x41,0x70,0x59,0x82},
	{0x39,0x50,0x78,0x12,0x46},{0x45,0x72,0x19,0x63,0x80},{0x09,0x52,0x17,0x36,0x84},{0x43,0x68,0x29,0x51,0x70},{0x10,0x82,0x96,0x35,0x74},
	{0x54,0x83,0x62,0x01,0x79},{0x79,0x60,0x82,0x34,0x15},{0x16,0x04,0x28,0x73,0x59},{0x09,0x82,0x43,0x17,0x65},{0x48,0x31,0x25,0x97,0x06},
	{0x25,0x86,0x03,0x17,0x94},{0x79,0x53,0x62,0x84,0x10},{0x74,0x39,0x86,0x20,0x15},{0x15,0x93,0x27,0x84,0x06},{0x64,0x90,0x38,0x75,0x12},
	{0x10,0x96,0x53,0x24,0x87},{0x97,0x45,0x16,0x30,0x82},{0x08,0x41,0x52,0x36,0x97},{0x83,0x12,0x60,0x95,0x47},{0x48,0x30,0x75,0x19,0x26},
	{0x38,0x25,0x61,0x97,0x04},{0x71,0x34,0x62,0x89,0x50},{0x84,0x39,0x20,0x61,0x75},{0x13,0x96,0x70,0x82,0x54},{0x02,0x64,0x13,0x97,0x58},
	{0x87,0x39,0x51,0x46,0x20},{0x76,0x80,0x32,0x54,0x19},{0x35,0x08,0x76,0x42,0x91},{0x86,0x39,0x75,0x41,0x20},{0x57,0x34,0x82,0x61,0x90},
	{0x38,0x09,0x64,0x51,0x72},{0x72,0x63,0x95,0x04,0x18},{0x08,0x35,0x26,0x74,0x91},{0x80,0x95,0x76,0x24,0x13},{0x35,0x49,0x67,0x82,0x10},
	{0x46,0x17,0x58,0x23,0x09},{0x84,0x56,0x90,0x21,0x37},{0x80,0x31,0x76,0x92,0x54},{0x19,0x58,0x72,0x63,0x40},{0x38,0x01,0x47,0x95,0x26},
	{0x76,0x42,0x09,0x38,0x15},{0x51,0x98,0x30,0x74,0x26},{0x91,0x30,0x57,0x28,0x64},{0x67,0x53,0x94,0x28,0x10},{0x54,0x62,0x83,0x70,0x19},
	{0x48,0x16,0x37,0x05,0x92},{0x79,0x86,0x23,0x45,0x10},{0x10,0x62,0x39,0x58,0x47},{0x26,0x84,0x31,0x50,0x97},{0x91,0x04,0x36,0x75,0x28},
	{0x62,0x49,0x18,0x35,0x07},{0x90,0x64,0x35,0x81,0x27},{0x37,0x20,0x16,0x95,0x84},{0x94,0x81,0x30,0x65,0x72},{0x65,0x38,0x70,0x94,0x12},
	{0x30,0x58,0x16,0x49,0x27},{0x67,0x85,0x43,0x20,0x19},{0x15,0x86,0x47,0x92,0x30},{0x91,0x57,0x63,0x02,0x84},{0x52,0x96,0x47,0x38,0x01},
	{0x05,0x92,0x14,0x38,0x67},{0x81,0x39,0x64,0x02,0x75},{0x25,0x37,0x86,0x91,0x40},{0x78,0x96,0x40,0x15,0x32},{0x43,0x72,0x01,0x65,0x89},
	{0x29,0x73,0x16,0x84,0x50},{0x53,0x72,0x08,0x61,0x94},{0x26,0x53,0x91,0x84,0x07},{0x63,0x50,0x29,0x18,0x47},{0x71,0x90,0x43,0x85,0x26},
	{0x21,0x47,0x56,0x83,0x09},{0x89,0x72,0x40,0x35,0x61},{0x98,0x04,0x17,0x25,0x36},{0x83,0x76,0x09,0x52,0x41},{0x21,0x05,0x67,0x94,0x38},
	{0x95,0x07,0x16,0x83,0x24},{0x75,0x28,0x41,0x60,0x93},{0x71,0x95,0x02,0x43,0x68},{0x74,0x80,0x31,0x25,0x69},{0x83,0x27,0x41,0x69,0x05},
	{0x42,0x51,0x07,0x69,0x38},{0x27,0x80,0x35,0x14,0x96},{0x24,0x80,0x13,0x95,0x67},{0x49,0x31,0x86,0x72,0x50},{0x78,0x42,0x30,0x59,0x16},
	{0x28,0x65,0x31,0x90,0x74},{0x58,0x17,0x30,0x46,0x29},{0x10,0x62,0x58,0x39,0x74},{0x96,0x40,0x15,0x87,0x23},{0x32,0x78,0x56,0x90,0x14},
	{0x73,0x19,0x26,0x05,0x84},{0x05,0x16,0x74,0x29,0x83},{0x43,0x91,0x02,0x86,0x57},{0x96,0x85,0x71,0x20,0x34},{0x25,0x94,0x38,0x01,0x76},
	{0x26,0x90,0x73,0x51,0x84},{0x17,0x95,0x34,0x62,0x80},{0x94,0x03,0x85,0x76,0x21},{0x38,0x41,0x26,0x95,0x07},{0x13,0x68,0x29,0x45,0x07},
	{0x78,0x25,0x06,0x94,0x31},{0x12,0x96,0x58,0x73,0x04},{0x51,0x38,0x72,0x49,0x06},{0x29,0x80,0x76,0x43,0x51},{0x16,0x02,0x84,0x75,0x93},
	{0x61,0x48,0x29,0x75,0x03},{0x10,0x36,0x89,0x57,0x42},{0x95,0x82,0x61,0x03,0x47},{0x81,0x30,0x27,0x94,0x56},{0x68,0x20,0x74,0x53,0x91},
	{0x62,0x75,0x84,0x01,0x93},{0x54,0x13,0x67,0x28,0x09},{0x24,0x03,0x91,0x87,0x65},{0x01,0x48,0x52,0x36,0x79},{0x63,0x40,0x98,0x21,0x57},
	{0x69,0x07,0x31,0x42,0x58},{0x72,0x10,0x45,0x39,0x86},{0x36,0x58,0x10,0x74,0x92},{0x34,0x06,0x95,0x78,0x21},{0x50,0x69,0x37,0x24,0x18},
	{0x73,0x60,0x54,0x82,0x91},{0x41,0x50,0x76,0x89,0x32},{0x72,0x93,0x85,0x61,0x04},{0x81,0x09,0x52,0x46,0x37},{0x80,0x32,0x15,0x67,0x49},
	{0x57,0x43,0x96,0x10,0x82},{0x49,0x87,0x26,0x35,0x01},{0x20,0x46,0x51,0x87,0x93},{0x64,0x89,0x25,0x03,0x71},{0x26,0x89,0x53,0x40,0x17},
	{0x60,0x57,0x81,0x32,0x49},{0x25,0x69,0x47,0x83,0x10},{0x90,0x38,0x24,0x16,0x57},{0x47,0x53,0x82,0x90,0x16},{0x19,0x76,0x52,0x34,0x08},
	{0x34,0x20,0x81,0x69,0x75},{0x50,0x67,0x92,0x13,0x48},{0x65,0x41,0x37,0x92,0x80},{0x69,0x82,0x37,0x41,0x50},{0x07,0x14,0x38,0x29,0x65},
	{0x93,0x75,0x48,0x01,0x26},{0x30,0x42,0x78,0x15,0x96},{0x41,0x58,0x63,0x92,0x70},{0x97,0x32,0x48,0x56,0x01},{0x39,0x60,0x18,0x57,0x42},
	{0x79,0x02,0x35,0x81,0x46},{0x98,0x63,0x40,0x25,0x71},{0x14,0x52,0x38,0x79,0x60},{0x98,0x03,0x56,0x41,0x72},{0x80,0x53,0x12,0x94,0x76},
	{0x23,0x07,0x54,0x16,0x89},{0x63,0x08,0x74,0x29,0x51},{0x31,0x94,0x58,0x20,0x67},{0x27,0x10,0x39,0x58,0x46},{0x29,0x71,0x05,0x36,0x48},
	{0x41,0x95,0x62,0x70,0x83},{0x15,0x29,0x87,0x30,0x46},{0x04,0x63,0x98,0x51,0x72},{0x06,0x41,0x29,0x87,0x53},{0x63,0x45,0x72,0x19,0x80},
	{0x92,0x47,0x68,0x01,0x35},{0x34,0x92,0x08,0x51,0x76},{0x40,0x19,0x72,0x63,0x58},{0x32,0x45,0x68,0x70,0x19},{0x85,0x19,0x67,0x04,0x32},
	{0x91,0x38,0x50,0x26,0x47},{0x06,0x12,0x74,0x98,0x53},{0x84,0x19,0x67,0x50,0x23},{0x42,0x57,0x30,0x19,0x86},{0x75,0x82,0x69,0x14,0x03},
	{0x40,0x92,0x81,0x67,0x53},{0x71,0x42,0x35,0x98,0x06},{0x64,0x27,0x85,0x19,0x03},{0x19,0x60,0x24,0x73,0x85},{0x91,0x07,0x25,0x43,0x68},
	{0x01,0x68,0x74,0x92,0x53},{0x81,0x39,0x27,0x45,0x60},{0x79,0x82,0x13,0x64,0x05},{0x05,0x39,0x47,0x81,0x62},{0x42,0x68,0x30,0x19,0x57},
	{0x50,0x39,0x21,0x74,0x86},{0x32,0x75,0x09,0x86,0x41},{0x18,0x43,0x92,0x65,0x07},{0x61,0x72,0x54,0x38,0x09},{0x90,0x65,0x71,0x23,0x48},
	{0x27,0x30,0x98,0x56,0x14},{0x09,0x27,0x56,0x83,0x14},{0x25,0x91,0x46,0x03,0x78},{0x23,0x94,0x68,0x57,0x10},{0x06,0x89,0x25,0x14,0x73},
	{0x26,0x14,0x89,0x73,0x50},{0x49,0x32,0x67,0x05,0x18},{0x09,0x13,0x46,0x57,0x82},{0x32,0x15,0x96,0x70,0x84},{0x26,0x49,0x35,0x01,0x87},
	{0x59,0x30,0x78,0x12,0x46},{0x31,0x68,0x07,0x24,0x59},{0x95,0x37,0x80,0x14,0x62},{0x72,0x03,0x69,0x58,0x14},{0x85,0x42,0x10,0x73,0x96},
	{0x14,0x37,0x56,0x80,0x29},{0x47,0x59,0x03,0x16,0x28},{0x79,0x85,0x24,0x10,0x63},{0x25,0x84,0x07,0x69,0x31},{0x85,0x47,0x31,0x60,0x92},
	{0x30,0x72,0x98,0x61,0x45},{0x10,0x62,0x97,0x38,0x45},{0x75,0x84,0x93,0x62,0x01},{0x56,0x83,0x04,0x92,0x17},{0x59,0x84,0x63,0x12,0x70},
	{0x51,0x62,0x78,0x90,0x43},{0x29,0x46,0x87,0x01,0x53},{0x20,0x58,0x37,0x14,0x69},{0x53,0x82,0x41,0x96,0x70},{0x79,0x06,0x14,0x25,0x38},
	{0x62,0x90,0x18,0x35,0x74},{0x84,0x50,0x61,0x32,0x79},{0x46,0x50,0x21,0x98,0x37},{0x20,0x64,0x78,0x93,0x51},{0x61,0x30,0x75,0x49,0x82},
	{0x56,0x32,0x90,0x47,0x18},{0x34,0x85,0x69,0x20,0x71},{0x36,0x18,0x70,0x24,0x95},{0x29,0x08,0x73,0x15,0x64},{0x79,0x80,0x43,0x15,0x26},
	{0x81,0x46,0x90,0x35,0x72},{0x54,0x03,0x98,0x12,0x67},{0x16,0x85,0x74,0x09,0x32},{0x49,0x85,0x31,0x02,0x76},{0x36,0x92,0x45,0x70,0x18},
	{0x52,0x37,0x08,0x69,0x41},{0x40,0x25,0x71,0x93,0x68},{0x45,0x28,0x30,0x17,0x96},{0x82,0x05,0x39,0x71,0x64},{0x09,0x32,0x17,0x86,0x45},
	{0x93,0x21,0x58,0x07,0x46},{0x70,0x16,0x48,0x25,0x39},{0x95,0x14,0x76,0x32,0x08},{0x39,0x75,0x08,0x41,0x26},{0x87,0x05,0x21,0x93,0x46},
	{0x28,0x50,0x34,0x16,0x97},{0x19,0x02,0x74,0x53,0x68},{0x61,0x30,0x84,0x59,0x72},{0x29,0x78,0x50,0x36,0x41},{0x39,0x70,0x42,0x58,0x61},
	{0x92,0x03,0x18,0x76,0x54},{0x98,0x47,0x63,0x50,0x12},{0x15,0x92,0x37,0x48,0x60},{0x67,0x31,0x09,0x45,0x28},{0x13,0x85,0x40,0x26,0x79},
	{0x54,0x30,0x79,0x16,0x28},{0x70,0x84,0x23,0x59,0x61},{0x23,0x46,0x71,0x59,0x80},{0x60,0x19,0x74,0x52,0x83},{0x08,0x54,0x37,0x62,0x91},
	{0x03,0x97,0x51,0x84,0x62},{0x18,0x97,0x43,0x62,0x50},{0x62,0x04,0x38,0x15,0x79},{0x61,0x34,0x89,0x07,0x52},{0x47,0x80,0x95,0x32,0x61},
	{0x10,0x78,0x56,0x39,0x42},{0x68,0x19,0x20,0x47,0x53},{0x04,0x63,0x18,0x57,0x29},{0x45,0x72,0x13,0x89,0x06},{0x10,0x85,0x76,0x49,0x32},
	{0x74,0x83,0x51,0x02,0x69},{0x83,0x05,0x47,0x92,0x61},{0x09,0x83,0x76,0x42,0x15},{0x03,0x24,0x79,0x16,0x85},{0x60,0x78,0x25,0x13,0x94},
	{0x17,0x50,0x98,0x36,0x42},{0x54,0x98,0x12,0x70,0x63},{0x72,0x50,0x34,0x18,0x96},{0x90,0x27,0x65,0x14,0x83},{0x47,0x16,0x50,0x23,0x89},
	{0x52,0x97,0x01,0x48,0x63},{0x47,0x90,0x68,0x15,0x32},{0x80,0x43,0x17,0x26,0x95},{0x18,0x26,0x49,0x05,0x37},{0x43,0x08,0x56,0x29,0x17},
	{0x81,0x32,0x90,0x74,0x65},{0x23,0x49,0x87,0x61,0x50},{0x02,0x18,0x96,0x37,0x45},{0x80,0x92,0x63,0x14,0x75},{0x43,0x27,0x90,0x56,0x81},
	{0x23,0x58,0x96,0x71,0x04},{0x51,0x78,0x42,0x06,0x39},{0x02,0x95,0x81,0x46,0x37},{0x43,0x65,0x20,0x19,0x78},{0x72,0x16,0x95,0x83,0x40},
	{0x64,0x53,0x21,0x80,0x79},{0x76,0x90,0x38,0x12,0x54},{0x25,0x01,0x89,0x67,0x43},{0x53,0x89,0x74,0x26,0x01},{0x82,0x97,0x14,0x06,0x53},
	{0x23,0x56,0x01,0x78,0x49},{0x92,0x14,0x67,0x58,0x30},{0x42,0x58,0x13,0x90,0x67},{0x41,0x96,0x82,0x35,0x70},{0x45,0x86,0x12,0x79,0x30},
	{0x58,0x74,0x63,0x19,0x02},{0x31,0x45,0x98,0x26,0x70},{0x47,0x56,0x39,0x20,0x81},{0x82,0x90,0x15,0x43,0x76},{0x62,0x41,0x89,0x37,0x05},
	{0x94,0x52,0x60,0x71,0x38},{0x57,0x40,0x92,0x36,0x18},{0x64,0x78,0x39,0x21,0x50},{0x32,0x19,0x84,0x60,0x75},{0x67,0x24,0x85,0x93,0x10},
	{0x41,0x93,0x85,0x06,0x27},{0x57,0x23,0x94,0x80,0x16},{0x54,0x12,0x70,0x69,0x38},{0x17,0x48,0x30,0x69,0x25},{0x81,0x20,0x93,0x56,0x47},
	{0x83,0x24,0x16,0x70,0x95},{0x59,0x47,0x12,0x30,0x68},{0x82,0x03,0x75,0x19,0x46},{0x29,0x05,0x47,0x61,0x38},{0x67,0x81,0x03,0x95,0x24},
	{0x02,0x58,0x73,0x46,0x91},{0x91,0x73,0x86,0x05,0x42},{0x89,0x13,0x67,0x25,0x40},{0x37,0x48,0x92,0x60,0x51},{0x72,0x14,0x35,0x98,0x06},
	{0x71,0x30,0x45,0x89,0x62},{0x50,0x14,0x73,0x26,0x89},{0x64,0x23,0x05,0x98,0x71},{0x89,0x05,0x76,0x42,0x13},{0x93,0x64,0x05,0x18,0x72},
	{0x79,0x18,0x25,0x46,0x03},{0x27,0x85,0x90,0x31,0x64},{0x12,0x86,0x07,0x94,0x35},{0x06,0x14,0x73,0x28,0x59},{0x28,0x97,0x14,0x30,0x56},
	{0x37,0x98,0x46,0x51,0x02},{0x08,0x23,0x17,0x49,0x56},{0x40,0x83,0x17,0x52,0x96},{0x94,0x10,0x53,0x87,0x62},{0x36,0x89,0x01,0x52,0x74},
	{0x41,0x93,0x67,0x02,0x85},{0x03,0x61,0x74,0x28,0x59},{0x03,0x52,0x86,0x47,0x19},{0x94,0x05,0x68,0x32,0x17},{0x45,0x73,0x68,0x29,0x10},
	{0x10,0x58,0x63,0x49,0x27},{0x32,0x78,0x16,0x05,0x94},{0x10,0x62,0x34,0x57,0x89},{0x67,0x05,0x28,0x39,0x14},{0x65,0x32,0x84,0x09,0x17},
	{0x32,0x10,0x98,0x65,0x47},{0x61,0x52,0x89,0x74,0x30},{0x17,0x40,0x32,0x65,0x89},{0x67,0x32,0x80,0x54,0x19},{0x80,0x27,0x53,0x69,0x14},
	{0x43,0x10,0x79,0x86,0x25},{0x21,0x64,0x30,0x87,0x59},{0x68,0x21,0x04,0x35,0x97},{0x35,0x40,0x91,0x26,0x78},{0x28,0x63,0x79,0x41,0x05},
	{0x43,0x09,0x61,0x72,0x85},{0x36,0x02,0x48,0x15,0x97},{0x27,0x48,0x09,0x35,0x16},{0x65,0x78,0x30,0x14,0x92},{0x24,0x58,0x70,0x19,0x36},
	{0x52,0x07,0x36,0x49,0x81},{0x68,0x95,0x20,0x17,0x34},{0x09,0x27,0x16,0x48,0x53},{0x21,0x47,0x03,0x86,0x59},{0x42,0x91,0x63,0x78,0x05},
	{0x30,0x45,0x86,0x92,0x71},{0x40,0x81,0x26,0x39,0x57},{0x32,0x48,0x79,0x65,0x10},{0x79,0x23,0x68,0x51,0x04},{0x39,0x52,0x16,0x07,0x84},
	{0x35,0x90,0x81,0x62,0x47},{0x40,0x62,0x71,0x58,0x39},{0x28,0x91,0x56,0x04,0x37},{0x67,0x81,0x92,0x53,0x04},{0x47,0x32,0x08,0x59,0x61},
	{0x79,0x20,0x63,0x14,0x58},{0x62,0x58,0x71,0x93,0x40},{0x18,0x75,0x69,0x03,0x42},{0x85,0x67,0x34,0x20,0x19},{0x84,0x16,0x70,0x25,0x93},
	{0x70,0x12,0x89,0x46,0x53},{0x35,0x74,0x21,0x08,0x69},{0x93,0x05,0x14,0x26,0x87},{0x29,0x70,0x84,0x35,0x61},{0x52,0x34,0x67,0x89,0x10},
	{0x80,0x72,0x94,0x65,0x13},{0x95,0x83,0x46,0x27,0x01},{0x59,0x71,0x20,0x84,0x63},{0x63,0x47,0x29,0x81,0x05},{0x28,0x05,0x13,0x69,0x47},
	{0x96,0x25,0x31,0x48,0x07},{0x83,0x56,0x29,0x74,0x01},{0x46,0x27,0x01,0x38,0x59},{0x79,0x21,0x65,0x48,0x03},{0x14,0x03,0x29,0x67,0x58},
	{0x03,0x89,0x16,0x47,0x52},{0x54,0x32,0x16,0x89,0x70},{0x06,0x98,0x43,0x12,0x57},{0x19,0x26,0x74,0x53,0x80},{0x31,0x67,0x82,0x49,0x50},
	{0x18,0x46,0x30,0x25,0x97},{0x57,0x18,0x62,0x39,0x40},{0x48,0x67,0x93,0x01,0x52},{0x53,0x48,0x09,0x76,0x21},{0x59,0x47,0x68,0x12,0x30},
	{0x35,0x60,0x17,0x49,0x28},{0x65,0x82,0x19,0x04,0x73},{0x76,0x32,0x48,0x10,0x59},{0x65,0x19,0x82,0x47,0x03},{0x12,0x59,0x46,0x03,0x87},
	{0x06,0x45,0x13,0x79,0x82},{0x50,0x93,0x78,0x46,0x12},{0x38,0x40,0x91,0x52,0x67},{0x51,0x42,0x73,0x68,0x09},{0x92,0x41,0x36,0x70,0x58},
	{0x03,0x92,0x14,0x75,0x86},{0x78,0x90,0x42,0x63,0x51},{0x90,0x47,0x56,0x38,0x12},{0x82,0x51,0x97,0x63,0x04},{0x74,0x89,0x31,0x50,0x62},
	{0x93,0x04,0x15,0x62,0x78},{0x36,0x70,0x51,0x28,0x94},{0x90,0x63,0x47,0x52,0x81},{0x26,0x75,0x48,0x01,0x93},{0x76,0x95,0x13,0x48,0x20},
	{0x82,0x41,0x36,0x57,0x90},{0x97,0x43,0x65,0x01,0x82},{0x63,0x09,0x25,0x41,0x87},{0x59,0x38,0x71,0x24,0x06},{0x15,0x23,0x84,0x69,0x70},
	{0x78,0x69,0x05,0x14,0x23},{0x73,0x19,0x46,0x25,0x80},{0x93,0x72,0x14,0x05,0x68},{0x39,0x18,0x04,0x57,0x62},{0x90,0x52,0x73,0x81,0x64},
	{0x38,0x25,0x61,0x70,0x94},{0x10,0x43,0x95,0x82,0x76},{0x48,0x23,0x76,0x01,0x95},{0x25,0x69,0x03,0x14,0x87},{0x18,0x57,0x03,0x42,0x69},
	{0x19,0x52,0x08,0x76,0x43},{0x34,0x56,0x27,0x89,0x10},{0x56,0x78,0x13,0x02,0x94},{0x17,0x32,0x48,0x95,0x60},{0x52,0x79,0x48,0x30,0x61},
	{0x48,0x59,0x32,0x06,0x71},{0x79,0x80,0x35,0x12,0x64},{0x62,0x47,0x91,0x38,0x50},{0x98,0x10,0x57,0x34,0x62},{0x61,0x35,0x49,0x80,0x27},
	{0x15,0x40,0x92,0x87,0x36},{0x47,0x62,0x95,0x30,0x81},{0x49,0x18,0x72,0x63,0x05},{0x68,0x13,0x27,0x90,0x54},{0x29,0x34,0x58,0x67,0x01},
	{0x84,0x79,0x62,0x05,0x31},{0x67,0x03,0x25,0x81,0x94},{0x95,0x03,0x81,0x26,0x74},{0x52,0x70,0x36,0x89,0x14},{0x16,0x52,0x08,0x74,0x93},
	{0x86,0x10,0x75,0x29,0x43},{0x90,0x23,0x85,0x16,0x74},{0x21,0x68,0x74,0x05,0x39},{0x28,0x71,0x59,0x43,0x06},{0x61,0x53,0x74,0x09,0x82},
	{0x06,0x95,0x13,0x82,0x47},{0x83,0x92,0x14,0x60,0x57},{0x41,0x29,0x30,0x76,0x85},{0x54,0x03,0x82,0x17,0x69},{0x09,0x37,0x51,0x82,0x64},
	{0x43,0x20,0x78,0x56,0x91},{0x19,0x36,0x70,0x25,0x84},{0x96,0x14,0x25,0x80,0x73},{0x73,0x29,0x58,0x40,0x16},{0x14,0x03,0x69,0x72,0x58},
	{0x31,0x46,0x09,0x82,0x57},{0x35,0x10,0x24,0x97,0x68},{0x05,0x68,0x79,0x31,0x42},{0x76,0x39,0x85,0x41,0x20},{0x43,0x62,0x19,0x78,0x50},
	{0x69,0x72,0x58,0x34,0x10},{0x51,0x28,0x63,0x74,0x90},{0x53,0x21,0x94,0x67,0x80},{0x41,0x79,0x35,0x68,0x02},{0x06,0x29,0x75,0x34,0x18},
	{0x96,0x85,0x72,0x13,0x04},{0x31,0x87,0x29,0x45,0x60},{0x71,0x08,0x32,0x94,0x65},{0x23,0x05,0x17,0x48,0x96},{0x25,0x04,0x17,0x96,0x83},
	{0x25,0x60,0x93,0x17,0x84},{0x10,0x37,0x48,0x59,0x26},{0x95,0x20,0x64,0x83,0x71},{0x29,0x30,0x65,0x87,0x41},{0x14,0x78,0x53,0x02,0x69},
	{0x72,0x54,0x80,0x69,0x13},{0x19,0x20,0x76,0x45,0x38},{0x95,0x16,0x04,0x23,0x78},{0x65,0x01,0x84,0x29,0x73},{0x56,0x94,0x02,0x18,0x73},
	{0x17,0x69,0x80,0x32,0x54},{0x16,0x58,0x93,0x24,0x70},{0x06,0x97,0x15,0x82,0x43},{0x83,0x76,0x05,0x29,0x14},{0x80,0x39,0x45,0x16,0x72},
	{0x39,0x25,0x67,0x81,0x40},{0x58,0x31,0x04,0x76,0x92},{0x87,0x40,0x92,0x56,0x13},{0x89,0x06,0x52,0x71,0x43},{0x83,0x70,0x56,0x42,0x19},
	{0x85,0x79,0x04,0x63,0x21},{0x98,0x61,0x45,0x23,0x07},{0x21,0x46,0x07,0x89,0x53},{0x86,0x32,0x19,0x50,0x47},{0x23,0x78,0x45,0x19,0x06},
	{0x91,0x75,0x40,0x82,0x63},{0x69,0x73,0x04,0x85,0x21},{0x26,0x74,0x93,0x08,0x51},{0x94,0x32,0x56,0x81,0x07},{0x75,0x32,0x01,0x68,0x94},
	{0x71,0x85,0x63,0x90,0x42},{0x53,0x90,0x41,0x28,0x67},{0x15,0x84,0x73,0x06,0x29},{0x20,0x91,0x43,0x86,0x75},{0x05,0x91,0x72,0x84,0x63},
	{0x49,0x21,0x36,0x70,0x58},{0x74,0x95,0x28,0x10,0x63},{0x43,0x20,0x96,0x57,0x18},{0x84,0x10,0x37,0x52,0x96},{0x47,0x09,0x16,0x52,0x83},
	{0x10,0x73,0x45,0x92,0x68},{0x52,0x17,0x98,0x64,0x30},{0x24,0x07,0x16,0x58,0x39},{0x41,0x38,0x97,0x62,0x50},{0x84,0x69,0x71,0x32,0x50},
	{0x75,0x60,0x84,0x31,0x92},{0x86,0x04,0x39,0x21,0x75},{0x65,0x03,0x78,0x94,0x21},{0x91,0x85,0x72,0x60,0x34},{0x96,0x71,0x52,0x08,0x34},
	{0x08,0x45,0x67,0x12,0x39},{0x96,0x58,0x21,0x73,0x04},{0x64,0x27,0x13,0x05,0x98},{0x76,0x04,0x23,0x98,0x15},{0x27,0x41,0x53,0x08,0x69},
	{0x30,0x92,0x68,0x15,0x47},{0x08,0x51,0x64,0x97,0x23},{0x09,0x28,0x31,0x56,0x47},{0x06,0x54,0x21,0x97,0x83},{0x51,0x96,0x42,0x83,0x70},
	{0x64,0x21,0x95,0x03,0x78},{0x16,0x72,0x40,0x59,0x83},{0x48,0x60,0x51,0x37,0x29},{0x54,0x02,0x68,0x71,0x39},{0x12,0x70,0x89,0x56,0x34},
	{0x39,0x80,0x57,0x24,0x16},{0x72,0x03,0x86,0x94,0x51},{0x20,0x49,0x56,0x31,0x78},{0x83,0x74,0x20,0x56,0x91},{0x13,0x06,0x89,0x24,0x57},
	{0x35,0x24,0x90,0x81,0x67},{0x52,0x74,0x61,0x09,0x83},{0x87,0x02,0x13,0x59,0x46},{0x41,0x20,0x37,0x65,0x89},{0x47,0x13,0x69,0x82,0x05},
	{0x09,0x53,0x12,0x68,0x47},{0x51,0x78,0x94,0x20,0x36},{0x78,0x04,0x13,0x92,0x65},{0x42,0x38,0x65,0x90,0x17},{0x78,0x51,0x24,0x63,0x90},
	{0x87,0x16,0x95,0x24,0x30},{0x32,0x10,0x69,0x85,0x47},{0x71,0x69,0x52,0x38,0x04},{0x14,0x03,0x86,0x25,0x79},{0x03,0x98,0x65,0x41,0x72},
	{0x02,0x17,0x48,0x93,0x65},{0x91,0x58,0x72,0x34,0x60},{0x72,0x59,0x31,0x60,0x84},{0x52,0x60,0x47,0x31,0x89},{0x85,0x07,0x93,0x12,0x46},
	{0x61,0x73,0x02,0x94,0x58},{0x70,0x63,0x19,0x28,0x54},{0x61,0x82,0x93,0x40,0x75},{0x31,0x24,0x78,0x05,0x69},{0x58,0x34,0x16,0x29,0x07},
	{0x69,0x35,0x72,0x48,0x01},{0x13,0x59,0x40,0x68,0x27},{0x93,0x51,0x84,0x76,0x02},{0x95,0x87,0x41,0x36,0x02},{0x35,0x08,0x92,0x14,0x76},
	{0x62,0x05,0x83,0x17,0x94},{0x51,0x02,0x39,0x84,0x67},{0x70,0x26,0x91,0x85,0x34},{0x07,0x56,0x98,0x43,0x21},{0x06,0x74,0x53,0x19,0x82},
	{0x84,0x09,0x71,0x35,0x62},{0x80,0x49,0x61,0x75,0x32},{0x48,0x72,0x50,0x93,0x16},{0x84,0x25,0x09,0x37,0x16},{0x79,0x38,0x21,0x05,0x46},
	{0x86,0x07,0x13,0x29,0x54},{0x98,0x17,0x50,0x62,0x43},{0x54,0x76,0x32,0x18,0x90},{0x69,0x01,0x85,0x34,0x27},{0x67,0x84,0x29,0x05,0x31},
	{0x70,0x16,0x43,0x85,0x29},{0x79,0x80,0x41,0x56,0x23},{0x63,0x19,0x07,0x28,0x45},{0x38,0x54,0x91,0x62,0x70},{0x65,0x92,0x14,0x07,0x83},
	{0x23,0x09,0x87,0x46,0x51},{0x03,0x62,0x58,0x74,0x91},{0x64,0x98,0x37,0x50,0x21},{0x65,0x03,0x89,0x71,0x24},{0x46,0x57,0x98,0x02,0x31},
	{0x75,0x30,0x81,0x92,0x46},{0x74,0x96,0x13,0x05,0x82},{0x28,0x69,0x53,0x17,0x04},{0x78,0x64,0x03,0x12,0x95},{0x01,0x38,0x65,0x27,0x49},
	{0x63,0x15,0x92,0x74,0x08},{0x28,0x96,0x41,0x05,0x73},{0x95,0x86,0x42,0x71,0x03},{0x43,0x21,0x08,0x76,0x95},{0x53,0x79,0x01,0x42,0x68},
	{0x73,0x18,0x20,0x49,0x65},{0x75,0x13,0x06,0x28,0x94},{0x86,0x21,0x95,0x03,0x47},{0x72,0x53,0x91,0x08,0x64},{0x06,0x84,0x19,0x37,0x52},
	{0x74,0x05,0x18,0x63,0x92},{0x51,0x70,0x64,0x39,0x82},{0x19,0x32,0x56,0x07,0x48},{0x30,0x65,0x98,0x12,0x74},{0x32,0x60,0x18,0x47,0x95},
	{0x95,0x84,0x60,0x17,0x23},{0x29,0x51,0x87,0x04,0x63},{0x30,0x97,0x28,0x15,0x46},{0x62,0x48,0x03,0x71,0x95},{0x61,0x34,0x27,0x09,0x85},
	{0x42,0x79,0x65,0x81,0x03},{0x50,0x49,0x21,0x86,0x37},{0x39,0x52,0x60,0x71,0x48},{0x79,0x54,0x12,0x08,0x63},{0x16,0x48,0x79,0x32,0x50},
	{0x09,0x16,0x85,0x32,0x74},{0x65,0x27,0x14,0x83,0x09},{0x31,0x24,0x59,0x60,0x78},{0x32,0x46,0x10,0x58,0x79},{0x69,0x04,0x58,0x17,0x23},
	{0x01,0x83,0x72,0x49,0x65},{0x10,0x84,0x75,0x93,0x26},{0x42,0x08,0x96,0x57,0x13},{0x29,0x16,0x38,0x40,0x75},{0x02,0x16,0x79,0x35,0x84},
	{0x04,0x32,0x96,0x87,0x51},{0x94,0x06,0x57,0x38,0x21},{0x75,0x96,0x18,0x24,0x03},{0x72,0x51,0x40,0x89,0x63},{0x92,0x05,0x17,0x36,0x84},
	{0x17,0x59,0x60,0x32,0x48},{0x27,0x61,0x89,0x50,0x43},{0x79,0x82,0x16,0x54,0x30},{0x56,0x12,0x38,0x97,0x40},{0x93,0x17,0x62,0x45,0x80},
	{0x15,0x49,0x20,0x68,0x37},{0x17,0x82,0x35,0x94,0x06},{0x60,0x27,0x15,0x84,0x93},{0x59,0x74,0x68,0x10,0x23},{0x38,0x16,0x05,0x29,0x47},
	{0x93,0x58,0x70,0x21,0x64},{0x13,0x78,0x25,0x94,0x60},{0x68,0x23,0x50,0x19,0x47},{0x26,0x05,0x83,0x41,0x97},{0x46,0x93,0x80,0x17,0x25},
	{0x15,0x62,0x37,0x90,0x84},{0x37,0x02,0x45,0x91,0x86},{0x29,0x65,0x01,0x37,0x84},{0x19,0x30,0x28,0x54,0x76},{0x09,0x82,0x76,0x14,0x53},
	{0x54,0x28,0x71,0x36,0x90},{0x62,0x10,0x35,0x74,0x89},{0x10,0x95,0x26,0x43,0x87},{0x84,0x96,0x32,0x75,0x10},{0x92,0x01,0x54,0x86,0x37},
	{0x89,0x46,0x17,0x25,0x03},{0x31,0x04,0x69,0x57,0x28},{0x61,0x43,0x59,0x07,0x82},{0x12,0x50,0x68,0x93,0x74},{0x84,0x93,0x67,0x02,0x51},
	{0x51,0x82,0x93,0x70,0x46},{0x54,0x92,0x36,0x07,0x18},{0x68,0x19,0x53,0x24,0x70},{0x67,0x91,0x52,0x84,0x30},{0x26,0x09,0x35,0x81,0x47},
	{0x51,0x90,0x43,0x82,0x67},{0x26,0x45,0x87,0x19,0x30},{0x83,0x79,0x14,0x06,0x25},{0x26,0x74,0x89,0x05,0x13},{0x87,0x09,0x14,0x63,0x52},
	{0x41,0x80,0x29,0x35,0x67},{0x13,0x76,0x95,0x04,0x28},{0x63,0x91,0x27,0x80,0x45},{0x38,0x56,0x14,0x29,0x07},{0x06,0x51,0x98,0x47,0x23},
	{0x72,0x95,0x68,0x43,0x10},{0x26,0x98,0x71,0x05,0x43},{0x41,0x95,0x78,0x02,0x63},{0x20,0x15,0x76,0x93,0x48},{0x47,0x13,0x28,0x50,0x69},
	{0x18,0x63,0x07,0x95,0x24},{0x60,0x87,0x12,0x45,0x39},{0x84,0x12,0x53,0x79,0x60},{0x07,0x43,0x21,0x65,0x98},{0x52,0x93,0x48,0x01,0x67},
	{0x69,0x57,0x30,0x18,0x24},{0x73,0x86,0x01,0x49,0x52},{0x65,0x48,0x30,0x27,0x91},{0x68,0x21,0x39,0x70,0x45},{0x96,0x70,0x23,0x84,0x15},
	{0x72,0x96,0x48,0x03,0x51},{0x62,0x43,0x89,0x05,0x71},{0x71,0x93,0x82,0x46,0x05},{0x18,0x23,0x70,0x65,0x94},{0x71,0x48,0x25,0x96,0x30},
	{0x69,0x25,0x18,0x03,0x74},{0x71,0x90,0x42,0x63,0x85},{0x71,0x06,0x29,0x83,0x54},{0x95,0x12,0x48,0x07,0x63},{0x49,0x81,0x60,0x27,0x35},
	{0x91,0x26,0x03,0x57,0x48},{0x81,0x97,0x20,0x46,0x53},{0x35,0x47,0x61,0x82,0x09},{0x58,0x74,0x19,0x26,0x30},{0x54,0x37,0x01,0x96,0x82},
	{0x80,0x36,0x95,0x27,0x41},{0x63,0x29,0x58,0x17,0x40},{0x40,0x35,0x87,0x29,0x16},{0x74,0x06,0x93,0x85,0x21},{0x68,0x15,0x20,0x79,0x34},
	{0x63,0x74,0x52,0x18,0x09},{0x58,0x23,0x60,0x17,0x94},{0x62,0x49,0x18,0x05,0x73},{0x30,0x64,0x15,0x28,0x79},{0x49,0x50,0x61,0x87,0x32},
	{0x14,0x65,0x82,0x03,0x79},{0x12,0x76,0x90,0x84,0x35},{0x71,0x83,0x25,0x60,0x94},{0x76,0x35,0x20,0x94,0x81},{0x67,0x13,0x50,0x92,0x48},
	{0x23,0x84,0x91,0x76,0x50},{0x56,0x79,0x40,0x81,0x32},{0x64,0x50,0x92,0x18,0x37},{0x15,0x09,0x26,0x43,0x78},{0x38,0x49,0x17,0x62,0x05},
	{0x78,0x02,0x35,0x61,0x49},{0x51,0x26,0x84,0x39,0x70},{0x54,0x69,0x12,0x73,0x08},{0x14,0x80,0x32,0x79,0x56},{0x15,0x94,0x36,0x27,0x08},
	{0x23,0x81,0x05,0x79,0x46},{0x04,0x86,0x17,0x59,0x32},{0x62,0x70,0x95,0x81,0x43},{0x31,0x59,0x72,0x08,0x64},{0x96,0x80,0x37,0x25,0x14},
	{0x98,0x43,0x16,0x20,0x75},{0x78,0x36,0x40,0x19,0x25},{0x80,0x45,0x37,0x26,0x91},{0x73,0x85,0x60,0x19,0x42},{0x19,0x04,0x52,0x63,0x87},
	{0x16,0x03,0x28,0x59,0x47},{0x29,0x76,0x13,0x40,0x58},{0x56,0x14,0x92,0x07,0x83},{0x19,0x65,0x48,0x23,0x07},{0x83,0x17,0x02,0x49,0x65},
	{0x98,0x54,0x26,0x07,0x13},{0x62,0x54,0x78,0x09,0x31},{0x91,0x36,0x05,0x87,0x42},{0x65,0x20,0x14,0x79,0x38},{0x74,0x10,0x69,0x58,0x32},
	{0x84,0x05,0x91,0x27,0x63},{0x09,0x86,0x21,0x54,0x73},{0x26,0x35,0x01,0x87,0x49},{0x06,0x35,0x71,0x24,0x89},{0x07,0x58,0x12,0x43,0x69},
	{0x41,0x25,0x03,0x98,0x76},{0x15,0x24,0x06,0x83,0x79},{0x79,0x64,0x15,0x02,0x38},{0x82,0x01,0x75,0x39,0x46},{0x75,0x04,0x96,0x23,0x18},
	{0x03,0x78,0x12,0x59,0x46},{0x57,0x48,0x09,0x62,0x31},{0x65,0x73,0x14,0x20,0x98},{0x59,0x64,0x13,0x70,0x28},{0x41,0x06,0x38,0x75,0x29}
};
	static void get_otpKey_s_array(unsigned char * code_s_array,int checkCode)
	{



	unsigned char i = 0;
	for( i = 0; i <5; i++)
	{
		unsigned char value = otpKeyMap[checkCode][i];
		code_s_array[i*2] = ((value >> 4) & 0x0f);
		code_s_array[i*2+1] = value & 0x0f;
	}


	



	}
#else

//判断余数是否存在数组中
unsigned char checkArrayOnly(unsigned char yuShu, unsigned char index,unsigned char * code_s_array){
	unsigned char i;

    for(i=0;i<index;i++){
        if (code_s_array[i]==yuShu) {
            return 1;
        }
    }
    return 0;
}

/**456
* 456%19 = 0
* 456%18 = 6
* 456%17 = 14 ==> 4
* 456%16 = 8
* 456%15 = 6 ==> 7
* 456%14 = 8 ==> 9
* 456%13 = 1
* 456%12 = 0 ==> 2
* 456%11 = 5
* 456%10 = 6 ==> 3
*/
static void get_otpKey_s_array(unsigned char * code_s_array,int checkCode)
{
	unsigned char chuShu = 0; //除数
    unsigned char index = 0; //下标
	for( chuShu = 19; chuShu >=10; chuShu--)
	{
        //checkCode == 被除数
        unsigned char yuShu = checkCode%chuShu;
        if (yuShu>9) {
            yuShu-=10;
        }
        while (checkArrayOnly(yuShu, index,code_s_array)) {
            yuShu++;
            if (yuShu>9) {
                yuShu=0;
            }
        }
        code_s_array[index] = yuShu;
        index++;
	}
}


//uint8_t m_checkCode[8] = {0};


#endif

static void parseOTPKey(char *p_password,char *p_adminKey,unsigned char *p_checkData)
{
	int checkCode = (p_password[5]-0x30)*100 + (p_password[6]-0x30)*10 + (p_password[7]-0x30);
	int code_array[5];
	int i = 0;
	char adminsKeyChar[8+1];
    int keyLength = strlen(p_adminKey);
	
	int s_data[5];
	int checkCodeT = 0;
	
	unsigned char code_s_array[10];
	get_otpKey_s_array(code_s_array,checkCode);
	for(i = 0;i<5;i++){
	    int code_t = p_password[i] - 0x30;
	    code_array[i] = code_s_array[code_t];
	}
	#ifdef __DQ_LIB_LOG_ENABLED__
	printf("\r\nparseOTPKey code_array:%d%d%d%d%d\r\n",code_array[0],code_array[1],code_array[2],code_array[3],code_array[4]);
	#endif
    memset(adminsKeyChar,0,8+1);
    if(keyLength==8){
        strcpy(adminsKeyChar,p_adminKey);
    } else if(keyLength>8){
        strncpy(adminsKeyChar,p_adminKey,8);
    } else{
        strcpy(adminsKeyChar,p_adminKey);
        strncat(adminsKeyChar,"????????",8-keyLength);
    }
	//SEGGER_RTT_printf(0,"\r\ndq_check_otp adminsKeyChar:%s\r\n",adminsKeyChar);

    s_data[0] = adminsKeyChar[0] - adminsKeyChar[1] + adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
    s_data[1] = 0x30 - adminsKeyChar[1] + adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
    s_data[2] = adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
    s_data[3] = 0x30 - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
    s_data[4] = adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];

	//SEGGER_RTT_printf(0,"\r\ndq_check_otp s_data:%d\r\n",s_data[0]);
	
    for(i = 0;i<5;i++){
        code_array[i] = ((code_array[i] - s_data[i])+100)%10;
    }

	//SEGGER_RTT_printf(0,"\r\ndq_check_otp code_array:%d%d%d%d%d\r\n",code_array[0],code_array[1],code_array[2],code_array[3],code_array[4]);
	
	//SEGGER_RTT_printf(1,"\r\ndq_check_otp code_array:%d%d%d%d%d\r\n",code_array[0],code_array[1],code_array[2],code_array[3],code_array[4]);
    for(i = 0;i<5;i++){
        if (i % 2 == 0) {
            checkCodeT += pow(code_array[i]*2,2);
        } else{
            checkCodeT += pow(code_array[i]*3,2);
        }
    }
 
	if(checkCode == checkCodeT){
	   p_checkData[0] = code_array[0];
	   p_checkData[1] = code_array[1];
	   p_checkData[2] = code_array[2];
	   p_checkData[3] = code_array[3];
	   p_checkData[4] = code_array[4];
	   p_checkData[5] = (p_password[5]-0x30);
	   p_checkData[6] = (p_password[6]-0x30);
	   p_checkData[7] = (p_password[7]-0x30);
    }
	else
	{
		for(i = 0; i<8;i++)
		{
			p_checkData[i] = 0xFF;
		}
	}
	#ifdef __DQ_LIB_LOG_ENABLED__
	printf("\r\nparseOTPKey p_checkData:%d%d%d%d%d%d%d%d\r\n",p_checkData[0],p_checkData[1],p_checkData[2],p_checkData[3],p_checkData[4],p_checkData[5],p_checkData[6],p_checkData[7]);
	#endif
}


static void parseOTPCheckData(unsigned char *p_checkData,char *p_adminKey,unsigned char *p_restulData)
{
	int checkCode = p_checkData[5]*100 + p_checkData[6]*10 + p_checkData[7];
	int code_array[5];
	char adminsKeyChar[8+1];
    int keyLength = strlen(p_adminKey);
	int i = 0;
	int s_data[5];
	int checkCodeT = 0;
	
	unsigned char code_s_array[10];
	get_otpKey_s_array(code_s_array,checkCode);
	
	for(i = 0;i<5;i++){
	    int code_t = p_checkData[i];
	    code_array[i] = code_s_array[code_t];
	}
	
	#ifdef __DQ_LIB_LOG_ENABLED__
	printf("\r\nparseOTPCheckData code_array:%d%d%d%d%d\r\n",code_array[0],code_array[1],code_array[2],code_array[3],code_array[4]);
	#endif
	
    memset(adminsKeyChar,0,8+1);
    if(keyLength==8){
        strcpy(adminsKeyChar,p_adminKey);
    } else if(keyLength>8){
        strncpy(adminsKeyChar,p_adminKey,8);
    } else{
        strcpy(adminsKeyChar,p_adminKey);
        strncat(adminsKeyChar,"????????",8-keyLength);
    }

	
	s_data[0] = adminsKeyChar[0] - adminsKeyChar[1] + adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
	s_data[1] = 0x30 - adminsKeyChar[1] + adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
	s_data[2] = adminsKeyChar[2] - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
	s_data[3] = 0x30 - adminsKeyChar[3] + adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];
	s_data[4] = adminsKeyChar[4] - adminsKeyChar[5] + adminsKeyChar[6] - adminsKeyChar[7];

    for(i = 0;i<5;i++){
        code_array[i] = ((code_array[i] - s_data[i])+100)%10;
    }

	for(i = 0;i<5;i++){
		if (i % 2 == 0) {
		    checkCodeT += pow(code_array[i]*2,2);
		} else{
		    checkCodeT += pow(code_array[i]*3,2);
		}
	}
	
	if(checkCode == checkCodeT){
		p_restulData[0] = code_array[0];
		p_restulData[1] = code_array[1];
		p_restulData[2] = code_array[2];
		p_restulData[3] = code_array[3];
		p_restulData[4] = code_array[4];
		p_restulData[5] = p_checkData[5];
		p_restulData[6] = p_checkData[6];
		p_restulData[7] = p_checkData[7];
	}
	else
	{
		for(i = 0; i<8;i++)
		{
			p_restulData[i] = 0xFF;
		}
	}

	#ifdef __DQ_LIB_LOG_ENABLED__
	printf("\r\nparseOTPCheckData p_restulData:%d%d%d%d%d\r\n",p_restulData[0],p_restulData[1],p_restulData[2],p_restulData[3],p_restulData[4]);
	#endif
}


unsigned char dq_check_otp(char *p_password,char *p_adminKey,unsigned char *p_checkCode_in,unsigned char *p_checkCode_out)
{
	unsigned char checkData[8];
	unsigned char passwordData[8];
	unsigned char checkData2[8];
	unsigned char pass = 0;
	int currCode = 0;
	int preCode = 0;
	int i = 0;
	
	memset(checkData,0,8);
	memset(passwordData,0,8);
	memset(checkData2,0,8);

	if(p_checkCode_in)
	{
		if(p_checkCode_in[0] == 0xFF && p_checkCode_in[1] == 0xFF && p_checkCode_in[2] == 0xFF &&p_checkCode_in[3] == 0xFF &&p_checkCode_in[4] == 0xFF
			&& p_checkCode_in[5] == 0xFF && p_checkCode_in[6] == 0xFF && p_checkCode_in[7] == 0xFF)
		{
			parseOTPKey(p_password,p_adminKey,checkData);
			if(checkData[0] == 0xFF)
			{
			
				pass = 0;
				return pass;
			}
			currCode = checkData[0]*10000 + checkData[1]*1000 + checkData[2]*100 + checkData[3]*10 + checkData[4];
			//int preCode = m_checkCode[0]*10000 + m_checkCode[1]*1000 + m_checkCode[2]*100 + m_checkCode[3]*10 + m_checkCode[4];

			#ifdef __DQ_LIB_LOG_ENABLED__
			printf("\r\ndq_check_otp currCode:%05d preCode:%05d\r\n",currCode,preCode);
			#endif
			if(currCode>preCode)
			{
				//memcpy(m_checkCode,checkData,8);
				for(i=0;i<8;i++)
				{
					passwordData[i] = p_password[i] - 0x30;
				}
				pass = 1;
			}
			memset(p_checkCode_out,0,8);
			memcpy(p_checkCode_out,passwordData,8);
			return pass;
		}
		else
		{
			parseOTPCheckData(p_checkCode_in,p_adminKey,checkData2);
			if(checkData2[0] == 0xFF)
			{
			
				pass = 0;
				memset(p_checkCode_out,0,8);
				memcpy(p_checkCode_out,passwordData,8);
				return pass;
			}
			

			parseOTPKey(p_password,p_adminKey,checkData);
			if(checkData[0] == 0xFF)
			{
			
				pass = 0;
				memset(p_checkCode_out,0,8);
				memcpy(p_checkCode_out,passwordData,8);
				return pass;
			}

			
			currCode = checkData[0]*10000 + checkData[1]*1000 + checkData[2]*100 + checkData[3]*10 + checkData[4];
			preCode = checkData2[0]*10000 + checkData2[1]*1000 + checkData2[2]*100 + checkData2[3]*10 + checkData2[4];
			//int preCode = m_checkCode[0]*10000 + m_checkCode[1]*1000 + m_checkCode[2]*100 + m_checkCode[3]*10 + m_checkCode[4];

			#ifdef __DQ_LIB_LOG_ENABLED__
			printf("\r\ndq_check_otp currCode:%05d preCode:%05d\r\n",currCode,preCode);
			#endif
			if(currCode>preCode)
			{
				//memcpy(m_checkCode,checkData,8);
				for(i=0;i<8;i++)
				{
					passwordData[i] = p_password[i] - 0x30;
				}
				pass = 1;
			}
			memset(p_checkCode_out,0,8);
			memcpy(p_checkCode_out,passwordData,8);
			return pass;
		}
		 
	}
	else
	{
		pass = 0;
		memset(p_checkCode_out,0,8);
		memcpy(p_checkCode_out,passwordData,8);
		return pass;
	}
}

#if 0
int main(void)
{
	bool pass = 0;
	unsigned char checkData[8];
	unsigned char check_code_array[8];
	
	memset(checkData,0xFF,sizeof(checkData));
	memset(check_code_array,0x00,sizeof(check_code_array));
	
	pass = dq_check_otp("48019036","123456",checkData,check_code_array);
	
	return pass;
}
#endif
