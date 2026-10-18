/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#include "PlatformDescriptor.h"

void setPlatformDescriptor(JNIEnv* env,
    const struct libusb_platform_descriptor* descriptor, jobject object)
{
    SET_POINTER(env, descriptor, object, "platformDescriptorPointer");
}

struct libusb_platform_descriptor* unwrapPlatformDescriptor(JNIEnv* env,
    jobject descriptor)
{
    return (struct libusb_platform_descriptor*) unwrapPointer(env, descriptor,
        "platformDescriptorPointer");
}

void resetPlatformDescriptor(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "platformDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(PlatformDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(PlatformDescriptor, bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bDevCapabilityType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(PlatformDescriptor, bDevCapabilityType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDevCapabilityType;
}

/**
 * byte bReserved()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(PlatformDescriptor, bReserved)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bReserved;
}

/**
 * ByteBuffer platformCapabilityUUID()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(PlatformDescriptor, platformCapabilityUUID)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    if (!descriptor) return NULL;
    return NewDirectReadOnlyByteBuffer(env, descriptor->PlatformCapabilityUUID, 16);
}

/**
 * ByteBuffer capabilityData()
 */
JNIEXPORT jobject JNICALL METHOD_NAME(PlatformDescriptor, capabilityData)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_platform_descriptor *descriptor =
        unwrapPlatformDescriptor(env, this);
    int length;
    if (!descriptor) return NULL;
    length = (int) descriptor->bLength - LIBUSB_BT_PLATFORM_DESCRIPTOR_MIN_SIZE;
    if (length < 0) length = 0;
    return NewDirectReadOnlyByteBuffer(env, descriptor->CapabilityData, length);
}
