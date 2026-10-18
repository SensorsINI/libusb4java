/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_INTERFACE_ASSOCIATION_DESCRIPTOR_H
#define USB4JAVA_INTERFACE_ASSOCIATION_DESCRIPTOR_H

#include "usb4java.h"

jobject wrapInterfaceAssociationDescriptor(JNIEnv*,
    const struct libusb_interface_association_descriptor*);
struct libusb_interface_association_descriptor*
    unwrapInterfaceAssociationDescriptor(JNIEnv*, jobject);

#endif
