#pragma once

/* Fixed error winsock
 * Macro call on Windows.h
 *
 */
#define WIN32_LEAN_AND_MEAN

#define YUH_API_IMPORT __declspec(dllimport)

#define YUH_API_EXPORT __declspec(dllexport)

#define BEGIN_NS_YUH namespace yuh {

#define END_NS_YUH 