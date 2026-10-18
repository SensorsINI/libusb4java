/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_SSPLUS_USB_DEVICE_CAPABILITY_DESCRIPTOR_H
#define USB4JAVA_SSPLUS_USB_DEVICE_CAPABILITY_DESCRIPTOR_H

#include "usb4java.h"

void setSsPlusUsbDeviceCapabilityDescriptor(JNIEnv*,
    const struct libusb_ssplus_usb_device_capability_descriptor*, jobject);
struct libusb_ssplus_usb_device_capability_descriptor*
    unwrapSsPlusUsbDeviceCapabilityDescriptor(JNIEnv*, jobject);
void resetSsPlusUsbDeviceCapabilityDescriptor(JNIEnv*, jobject);

#endif
