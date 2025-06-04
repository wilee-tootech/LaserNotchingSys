#pragma once

#include <stdio.h>


#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_BUILD 0

// 빌드 날짜 및 시간 정보
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__

#define BUILD_YEAR	(__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100 + (__DATE__[9] - '0') * 10 + (__DATE__[10] - '0')
#define BUILD_MONTH	(__DATE__[0] == 'J') ? ((__DATE__[1] == 'a') ? 1 : ((__DATE__[2] == 'n') ? 6 : 7)) \
					: (__DATE__[0] == 'F') ? 2 \
					: (__DATE__[0] == 'M') ? ((__DATE__[2] == 'r') ? 3 : 5) \
					: (__DATE__[0] == 'A') ? ((__DATE__[1] == 'p') ? 4 : 8) \
					: (__DATE__[0] == 'S') ? 9 \
					: (__DATE__[0] == 'O') ? 10 \
					: (__DATE__[0] == 'N') ? 11 \
					: (__DATE__[0] == 'D') ? 12 : 0
#define BUILD_DAY	(__DATE__[4] == ' ') ? (__DATE__[5] - '0') : ((__DATE__[4] - '0') * 10 + (__DATE__[5] - '0'))

#define BUILD_HOUR ((__TIME__[0]-'0')*10+(__TIME__[1]-'0'))
#define BUILD_MIN  ((__TIME__[3]-'0')*10+(__TIME__[4]-'0'))
#define BUILD_SEC  ((__TIME__[6]-'0')*10+(__TIME__[7]-'0'))


// 버전 문자열 생성
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VERSION_STRING TOSTRING(VERSION_MAJOR) "." TOSTRING(VERSION_MINOR) "." TOSTRING(VERSION_PATCH)
//#define FULL_VERSION_STRING VERSION_STRING " (" BUILD_DATE " " BUILD_TIME ")"
#define FULL_VERSION_STRING VERSION_STRING " (" BUILD_DATE " )"




