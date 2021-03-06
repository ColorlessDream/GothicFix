#include "PreCompiled.h"

namespace COMMON
{

float FloatDivRemainder(float num, float div)
{
	int integer = (int)(num / div);
	return (num - (div * integer));
}

uInt NearestToPower2(uInt Value)
{
	uInt i = 1;
	while(i < Value && i < 0x80000000) 
		i <<= 1;

	return ((i - Value) == 0) ? Value : ((i - Value) >= i>>2) ? i>>=1 : i;
}

uInt GetFirstSetBit(uInt Value)
{
	Value ^= 0xFFFFFFFF;
	for(uInt i = 0; i < 32; i++)
	{
		if(!(Value & 1))
			return i;
		Value = Value >> 1;
	}
	return 32;
}

uInt GetCountSetBit(uInt Value)
{
	uInt Result = 0;
	for(uInt i = 0; i < 32; i++)
	{
		if(Value & (1 << i))
			Result++;
	}
	return Result;
}

const uChar Crc8Table[256] = 
{
	0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
	0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
	0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
	0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
	0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
	0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
	0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
	0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
	0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
	0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
	0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
	0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
	0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
	0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
	0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
	0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
	0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
	0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
	0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
	0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
	0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
	0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
	0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
	0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
	0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
	0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
	0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
	0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
	0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
	0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
	0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
	0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

uChar Crc8(const uChar* buf, uInt len, uChar crc)
{
	while (len--)
       crc = Crc8Table[crc ^ *buf++];
 
    return crc;
}

const uShort Crc16Table[256] = 
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 
};
 
uShort Crc16(const uChar* buf, uInt len, uShort crc)
{
    while (len--)
		crc = (crc >> 8) ^ Crc16Table[(crc & 0xFF) ^ *buf++];
 
    return crc;
}

const uLong Crc32Table[256] =
{
	0x00000000UL, 0x77073096UL, 0xee0e612cUL, 0x990951baUL, 0x076dc419UL,
	0x706af48fUL, 0xe963a535UL, 0x9e6495a3UL, 0x0edb8832UL, 0x79dcb8a4UL,
	0xe0d5e91eUL, 0x97d2d988UL, 0x09b64c2bUL, 0x7eb17cbdUL, 0xe7b82d07UL,
	0x90bf1d91UL, 0x1db71064UL, 0x6ab020f2UL, 0xf3b97148UL, 0x84be41deUL,
	0x1adad47dUL, 0x6ddde4ebUL, 0xf4d4b551UL, 0x83d385c7UL, 0x136c9856UL,
	0x646ba8c0UL, 0xfd62f97aUL, 0x8a65c9ecUL, 0x14015c4fUL, 0x63066cd9UL,
	0xfa0f3d63UL, 0x8d080df5UL, 0x3b6e20c8UL, 0x4c69105eUL, 0xd56041e4UL,
	0xa2677172UL, 0x3c03e4d1UL, 0x4b04d447UL, 0xd20d85fdUL, 0xa50ab56bUL,
	0x35b5a8faUL, 0x42b2986cUL, 0xdbbbc9d6UL, 0xacbcf940UL, 0x32d86ce3UL,
	0x45df5c75UL, 0xdcd60dcfUL, 0xabd13d59UL, 0x26d930acUL, 0x51de003aUL,
	0xc8d75180UL, 0xbfd06116UL, 0x21b4f4b5UL, 0x56b3c423UL, 0xcfba9599UL,
	0xb8bda50fUL, 0x2802b89eUL, 0x5f058808UL, 0xc60cd9b2UL, 0xb10be924UL,
	0x2f6f7c87UL, 0x58684c11UL, 0xc1611dabUL, 0xb6662d3dUL, 0x76dc4190UL,
	0x01db7106UL, 0x98d220bcUL, 0xefd5102aUL, 0x71b18589UL, 0x06b6b51fUL,
	0x9fbfe4a5UL, 0xe8b8d433UL, 0x7807c9a2UL, 0x0f00f934UL, 0x9609a88eUL,
	0xe10e9818UL, 0x7f6a0dbbUL, 0x086d3d2dUL, 0x91646c97UL, 0xe6635c01UL,
	0x6b6b51f4UL, 0x1c6c6162UL, 0x856530d8UL, 0xf262004eUL, 0x6c0695edUL,
	0x1b01a57bUL, 0x8208f4c1UL, 0xf50fc457UL, 0x65b0d9c6UL, 0x12b7e950UL,
	0x8bbeb8eaUL, 0xfcb9887cUL, 0x62dd1ddfUL, 0x15da2d49UL, 0x8cd37cf3UL,
	0xfbd44c65UL, 0x4db26158UL, 0x3ab551ceUL, 0xa3bc0074UL, 0xd4bb30e2UL,
	0x4adfa541UL, 0x3dd895d7UL, 0xa4d1c46dUL, 0xd3d6f4fbUL, 0x4369e96aUL,
	0x346ed9fcUL, 0xad678846UL, 0xda60b8d0UL, 0x44042d73UL, 0x33031de5UL,
	0xaa0a4c5fUL, 0xdd0d7cc9UL, 0x5005713cUL, 0x270241aaUL, 0xbe0b1010UL,
	0xc90c2086UL, 0x5768b525UL, 0x206f85b3UL, 0xb966d409UL, 0xce61e49fUL,
	0x5edef90eUL, 0x29d9c998UL, 0xb0d09822UL, 0xc7d7a8b4UL, 0x59b33d17UL,
	0x2eb40d81UL, 0xb7bd5c3bUL, 0xc0ba6cadUL, 0xedb88320UL, 0x9abfb3b6UL,
	0x03b6e20cUL, 0x74b1d29aUL, 0xead54739UL, 0x9dd277afUL, 0x04db2615UL,
	0x73dc1683UL, 0xe3630b12UL, 0x94643b84UL, 0x0d6d6a3eUL, 0x7a6a5aa8UL,
	0xe40ecf0bUL, 0x9309ff9dUL, 0x0a00ae27UL, 0x7d079eb1UL, 0xf00f9344UL,
	0x8708a3d2UL, 0x1e01f268UL, 0x6906c2feUL, 0xf762575dUL, 0x806567cbUL,
	0x196c3671UL, 0x6e6b06e7UL, 0xfed41b76UL, 0x89d32be0UL, 0x10da7a5aUL,
	0x67dd4accUL, 0xf9b9df6fUL, 0x8ebeeff9UL, 0x17b7be43UL, 0x60b08ed5UL,
	0xd6d6a3e8UL, 0xa1d1937eUL, 0x38d8c2c4UL, 0x4fdff252UL, 0xd1bb67f1UL,
	0xa6bc5767UL, 0x3fb506ddUL, 0x48b2364bUL, 0xd80d2bdaUL, 0xaf0a1b4cUL,
	0x36034af6UL, 0x41047a60UL, 0xdf60efc3UL, 0xa867df55UL, 0x316e8eefUL,
	0x4669be79UL, 0xcb61b38cUL, 0xbc66831aUL, 0x256fd2a0UL, 0x5268e236UL,
	0xcc0c7795UL, 0xbb0b4703UL, 0x220216b9UL, 0x5505262fUL, 0xc5ba3bbeUL,
	0xb2bd0b28UL, 0x2bb45a92UL, 0x5cb36a04UL, 0xc2d7ffa7UL, 0xb5d0cf31UL,
	0x2cd99e8bUL, 0x5bdeae1dUL, 0x9b64c2b0UL, 0xec63f226UL, 0x756aa39cUL,
	0x026d930aUL, 0x9c0906a9UL, 0xeb0e363fUL, 0x72076785UL, 0x05005713UL,
	0x95bf4a82UL, 0xe2b87a14UL, 0x7bb12baeUL, 0x0cb61b38UL, 0x92d28e9bUL,
	0xe5d5be0dUL, 0x7cdcefb7UL, 0x0bdbdf21UL, 0x86d3d2d4UL, 0xf1d4e242UL,
	0x68ddb3f8UL, 0x1fda836eUL, 0x81be16cdUL, 0xf6b9265bUL, 0x6fb077e1UL,
	0x18b74777UL, 0x88085ae6UL, 0xff0f6a70UL, 0x66063bcaUL, 0x11010b5cUL,
	0x8f659effUL, 0xf862ae69UL, 0x616bffd3UL, 0x166ccf45UL, 0xa00ae278UL,
	0xd70dd2eeUL, 0x4e048354UL, 0x3903b3c2UL, 0xa7672661UL, 0xd06016f7UL,
	0x4969474dUL, 0x3e6e77dbUL, 0xaed16a4aUL, 0xd9d65adcUL, 0x40df0b66UL,
	0x37d83bf0UL, 0xa9bcae53UL, 0xdebb9ec5UL, 0x47b2cf7fUL, 0x30b5ffe9UL,
	0xbdbdf21cUL, 0xcabac28aUL, 0x53b39330UL, 0x24b4a3a6UL, 0xbad03605UL,
	0xcdd70693UL, 0x54de5729UL, 0x23d967bfUL, 0xb3667a2eUL, 0xc4614ab8UL,
	0x5d681b02UL, 0x2a6f2b94UL, 0xb40bbe37UL, 0xc30c8ea1UL, 0x5a05df1bUL,
	0x2d02ef8dUL
};

uLong Crc32(const uChar* buf, uInt len, uLong crc)
{
	crc ^= 0xFFFFFFFFUL;

	while(len--)
        crc = Crc32Table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
}

bool Encrypt8(uChar *buf, uLong len, const uChar* pass)
{
	if(pass)
	{
		for(uLong i = 0; i < len; i++)
		{
			buf[i] += pass[0]; 
		}
		return true;
	}
	return false;
}

bool Decrypt8(uChar *buf, uLong len, const uChar* pass)
{
	if(pass)
	{
		for(uLong i = 0; i < len; i++)
		{
			buf[i] -= pass[0];
		}
		return true;
	}
	return false;
}

bool Encrypt8v2(uChar *buf, uLong len, const uChar* pass)
{
	if(pass)
	{
		uInt a = 0;
		uInt len = (uInt)strlen((char*)pass);
		for(uLong i = 0; i < len; i++)
		{
			if(a == len) a = 0;
			buf[i] += pass[a++]; 
		}
		return true;
	}
	return false;
}

bool Decrypt8v2(uChar *buf, uLong len, const uChar* pass)
{
	if(pass)
	{
		uInt a = 0;
		uInt len = (uInt)strlen((char*)pass);
		for(uLong i = 0; i < len; i++)
		{
			if(a == len) a = 0;
			buf[i] -= pass[a++];
		}
		return true;
	}
	return false;
}

// crt strings extensions

const char* _strnstr(const char* _Str, const char* _SubStr, size_t _SubStrLen)
{
	for(; *_Str; _Str++)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_Str[s] && _SubStr[s])
				Equal &= (_Str[s] == _SubStr[s]);
			else
				Equal = false;
		}
		if(Equal)
			return _Str;
	}
	return NULL;
}

const char* _strnistr(const char* _Str, const char* _SubStr, size_t _SubStrLen)
{
	for(; *_Str; _Str++)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_Str[s] && _SubStr[s])
				Equal &= (toupper(_Str[s]) == toupper(_SubStr[s]));
			else
				Equal = false;
		}
		if(Equal)
			return _Str;
	}
	return NULL;
}

const char* _strrnstr(const char* _Str, const char* _SubStr, size_t _StrLen, size_t _SubStrLen)
{
	if(!_Str || !_SubStr || !_StrLen || !_SubStrLen)
		return NULL;

	for(const char* _StrR = &_Str[_StrLen - _SubStrLen]; _StrR >= _Str; _StrR--)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_StrR[s] && _SubStr[s])
				Equal &= (_StrR[s] == _SubStr[s]);
			else
				Equal = false;
		}
		if(Equal)
			return _StrR;
	}
	return NULL;
}

const wchar_t* _wcsnstr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _SubStrLen)
{
	for(; *_Str; _Str++)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_Str[s] && _SubStr[s])
				Equal &= (_Str[s] == _SubStr[s]);
			else
				Equal = false;
		}
		if(Equal)
			return _Str;
	}
	return NULL;
}

const wchar_t* _wcsnistr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _SubStrLen)
{
	for(; *_Str; _Str++)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_Str[s] && _SubStr[s])
				Equal &= (towupper(_Str[s]) == towupper(_SubStr[s]));
			else
				Equal = false;
		}
		if(Equal)
			return _Str;
	}
	return NULL;
}

const wchar_t* _wcsrnstr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _StrLen, size_t _SubStrLen)
{
	if(!_Str || !_SubStr || !_StrLen || !_SubStrLen)
		return NULL;

	for(const wchar_t* _StrR = &_Str[_StrLen - _SubStrLen]; _StrR >= _Str; _StrR--)
	{
		bool Equal = true;
		for(size_t s = 0; Equal && (s < _SubStrLen); s++)
		{
			if(_StrR[s] && _SubStr[s])
				Equal &= (_StrR[s] == _SubStr[s]);
			else
				Equal = false;
		}
		if(Equal)
			return _StrR;
	}
	return NULL;
}

// Mem extensions

const uChar* _memstr(const uChar* buffer, size_t bufsize, const uChar* str, size_t strsize)
{
	for(size_t b = 0; b <= (bufsize - strsize); b++)
	{
		for(size_t s = 0; s < strsize; s++)
		{
			if(buffer[b + s] != str[s])
				break;
			if(s == strsize - 1)
				return &buffer[b];
		}
	}
	return NULL;
}

const uChar* _memrstr(const uChar* buffer, size_t bufsize, const uChar* str, size_t strsize)
{
	if(bufsize >= strsize)
	{
		for(size_t b = (bufsize - strsize) + 1; b > 0; b--)
		{
			for(size_t s = 0; s < strsize; s++)
			{
				if(buffer[b - 1 + s] != str[s])
					break;
				if(s == strsize - 1)
					return &buffer[b - 1];
			}
		}
	}
	return NULL;
}

// UtilityEx

bool PlatformGetComputerName(TString& name)
{
	DWORD Size = 0;
	if(!GetComputerName(NULL, &Size) && (GetLastError() == ERROR_BUFFER_OVERFLOW) && Size)
	{
		name.Resize(Size - 1);
		if(GetComputerName((TCHAR*)name.GetData(), &Size))
			return true;
	}
	name.Clear();
	return false;
}

uInt PlatformGetCurrentProcessId(void)
{
	return (uInt)GetCurrentProcessId();
}

uInt PlatformGetCurrentThreadId(void)
{
	return (uInt)GetCurrentThreadId();
}

bool PlatformGetWorkPath(TString& path)
{
	uInt Size = GetCurrentDirectory(0, NULL);
	if(Size)
	{
		path.Resize(Size);
		return (GetCurrentDirectory(path.Length(), (TCHAR*)path.GetData()) == Size - 1);
	}
	return false;
}

bool PlatformGetTempPath(TString& path)
{
	path.Resize(MAX_PATH);
	DWORD Length = GetTempPath(path.Length(), (TCHAR*)path.GetData());
	if(!Length)
		return false;

	if(Length > path.Length())
	{
		path.Resize(Length);
		if(!(Length = GetTempPath(path.Length(), (TCHAR*)path.GetData())))
			return false;
	}

	path.SetSizeDirectly(Length);
	return true;
}

bool PlatformGetTempFileName(TString& name)
{
	TString Path;

	Path.Resize(MAX_PATH);
	DWORD Length = GetTempPath(Path.Length(), (TCHAR*)Path.GetData());
	if(!Length)
		return false;

	if(Length > Path.Length())
	{
		Path.Resize(Length);
		if(!GetTempPath(Path.Length(), (TCHAR*)Path.GetData()))
			return false;
	}

	name.Resize(MAX_PATH + 1);
	if(GetTempFileName(Path, _T("VDF"), 0, (TCHAR*)name.GetData()))
	{
		name.Assign(name.GetData());
		return true;
	}

	return false;
}

bool PlatformGetExePath(TString& name)
{
	SetLastError(ERROR_INSUFFICIENT_BUFFER);
	for(uInt i = 1; GetLastError() == ERROR_INSUFFICIENT_BUFFER; i++)
	{
		name.Resize(i * MAX_PATH);
		SetLastError(0);
		DWORD Size = GetModuleFileName(NULL, (TCHAR*)name.GetData(), i * MAX_PATH);
		if(!Size)
			return false;
		name.SetSizeDirectly(Size);
	}
	return (name.Length() != 0);
}

bool PlatformReadTextFile(const TString& file, TStringArray& lines)
{
	FILE* fp = _tfopen(file, _T("rb"));
	if(!fp)
		return false;
	uChar BOM[3];
	if(fread(BOM, 1, 3, fp) != 3)
	{
		fclose(fp);
		return false;
	}
	fclose(fp);

	const TCHAR* Mode = _T("r");
	if((BOM[0] == 0xFF) && (BOM[1] == 0xFE))
		Mode = _T("r, ccs=UTF-16LE");
	else
	if((BOM[0] == 0xFE) && (BOM[1] == 0xFF))
		Mode = _T("r, ccs=UNICODE");
	else
	if((BOM[0] == 0xEF) && (BOM[1] == 0xBB) && (BOM[2] == 0xBF))
		Mode = _T("r, ccs=UTF-8");

	fp = _tfopen(file, Mode);
	if(!fp)
		return false;

	setvbuf(fp, NULL, _IOFBF, 1024);

	TString Line;
	TCHAR Char = _T('\0');
	while(Char = _fgettc(fp))
	{
		if(Char == _T('\n'))
		{
			lines.Add(Line);
			Line.Clear();
		}
		else
		if(Char == WEOF)
			break;
		else
			Line.Append(Char);
	}
	if(Line.Length())
	{
		lines.Add(Line);
		Line.Clear();
	}

	fclose(fp);
	return true;
}

}