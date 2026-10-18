/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#include "SsPlusUsbDeviceCapabilityDescriptor.h"

void setSsPlusUsbDeviceCapabilityDescriptor(JNIEnv* env,
    const struct libusb_ssplus_usb_device_capability_descriptor* descriptor,
    jobject object)
{
    SET_POINTER(env, descriptor, object, "ssPlusUsbDeviceCapabilityDescriptorPointer");
}

struct libusb_ssplus_usb_device_capability_descriptor*
unwrapSsPlusUsbDeviceCapabilityDescriptor(JNIEnv* env, jobject descriptor)
{
    return (struct libusb_ssplus_usb_device_capability_descriptor*) unwrapPointer(
        env, descriptor, "ssPlusUsbDeviceCapabilityDescriptorPointer");
}

void resetSsPlusUsbDeviceCapabilityDescriptor(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "ssPlusUsbDeviceCapabilityDescriptorPointer");
}

static struct libusb_ssplus_sublink_attribute* sublinkAt(JNIEnv* env,
    jobject this, jint index)
{
    struct libusb_ssplus_usb_device_capability_descriptor* descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return NULL;
    if (index < 0 || index >= descriptor->numSublinkSpeedAttributes)
    {
        illegalArgument(env, "sublink index out of range");
        return NULL;
    }
    return &descriptor->sublinkSpeedAttributes[index];
}

/**
 * byte numSublinkSpeedAttributes()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    numSublinkSpeedAttributes)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->numSublinkSpeedAttributes;
}

/**
 * byte numSublinkSpeedIDs()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    numSublinkSpeedIDs)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->numSublinkSpeedIDs;
}

/**
 * byte ssid()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor, ssid)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->ssid;
}

/**
 * byte minRxLaneCount()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    minRxLaneCount)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->minRxLaneCount;
}

/**
 * byte minTxLaneCount()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    minTxLaneCount)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor =
        unwrapSsPlusUsbDeviceCapabilityDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->minTxLaneCount;
}

/**
 * byte sublinkSsid(int)
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkSsid)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jbyte) attr->ssid;
}

/**
 * int sublinkExponent(int)
 */
JNIEXPORT jint JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkExponent)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jint) attr->exponent;
}

/**
 * int sublinkType(int)
 */
JNIEXPORT jint JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkType)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jint) attr->type;
}

/**
 * int sublinkDirection(int)
 */
JNIEXPORT jint JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkDirection)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jint) attr->direction;
}

/**
 * int sublinkProtocol(int)
 */
JNIEXPORT jint JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkProtocol)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jint) attr->protocol;
}

/**
 * int sublinkMantissa(int)
 */
JNIEXPORT jint JNICALL METHOD_NAME(SsPlusUsbDeviceCapabilityDescriptor,
    sublinkMantissa)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_ssplus_sublink_attribute *attr = sublinkAt(env, this, index);
    if (!attr) return 0;
    return (jint) attr->mantissa;
}
