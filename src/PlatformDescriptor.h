/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_PLATFORM_DESCRIPTOR_H
#define USB4JAVA_PLATFORM_DESCRIPTOR_H

#include "usb4java.h"

void setPlatformDescriptor(JNIEnv*,
    const struct libusb_platform_descriptor*, jobject);
struct libusb_platform_descriptor* unwrapPlatformDescriptor(JNIEnv*, jobject);
void resetPlatformDescriptor(JNIEnv*, jobject);

#endif
