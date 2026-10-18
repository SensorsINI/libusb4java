/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#ifndef USB4JAVA_INTERFACE_ASSOCIATION_DESCRIPTORS_H
#define USB4JAVA_INTERFACE_ASSOCIATION_DESCRIPTORS_H

#include "usb4java.h"

void setInterfaceAssociationDescriptors(JNIEnv*,
    const struct libusb_interface_association_descriptor_array*, jobject);
struct libusb_interface_association_descriptor_array*
    unwrapInterfaceAssociationDescriptors(JNIEnv*, jobject);
void resetInterfaceAssociationDescriptors(JNIEnv*, jobject);

#endif
