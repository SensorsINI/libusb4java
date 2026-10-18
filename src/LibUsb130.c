/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 *
 * JNI for libusb APIs added after 1.0.22, through 1.0.30.
 */

#include <stdlib.h>
#include "usb4java.h"
#include "Context.h"
#include "Device.h"
#include "DeviceHandle.h"
#include "BosDevCapabilityDescriptor.h"
#include "SsPlusUsbDeviceCapabilityDescriptor.h"
#include "PlatformDescriptor.h"
#include "InterfaceAssociationDescriptors.h"

static void LIBUSB_CALL logCallback(libusb_context *ctx,
    enum libusb_log_level level, const char *str)
{
    JNIEnv *env;
    jint envResult;
    jobject context;
    jstring message;

    THREAD_BEGIN(env, envResult);
    context = wrapContext(env, ctx);
    message = (*env)->NewStringUTF(env, str ? str : "");
    (*env)->CallStaticVoidMethod(env, jClassLibUsb, jMethodLogCallback,
        context, (jint) level, message);
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionClear(env);
    }
    THREAD_END(envResult);
}

/**
 * void setLogCallbackNative(Context, int, boolean)
 */
JNIEXPORT void JNICALL METHOD_NAME(LibUsb, setLogCallbackNative)
(
    JNIEnv *env, jclass class, jobject context, jint mode, jboolean enabled
)
{
    libusb_context *ctx = unwrapContext(env, context);
    if (!ctx && context) return;
    libusb_set_log_cb(ctx, enabled ? &logCallback : NULL, (int) mode);
}

/**
 * int getDeviceString(Device, int, StringBuffer)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getDeviceString)
(
    JNIEnv *env, jclass class, jobject device, jint stringType, jobject string
)
{
    libusb_device *dev;
    char buffer[LIBUSB_DEVICE_STRING_BYTES_MAX];
    int result;

    VALIDATE_NOT_NULL(env, device, return 0);
    VALIDATE_NOT_NULL(env, string, return 0);
    dev = unwrapDevice(env, device);
    if (!dev) return 0;
    result = libusb_get_device_string(dev,
        (enum libusb_device_string_type) stringType, buffer,
        (int) sizeof(buffer));
    if (result >= 0)
    {
        jobject tmp = (*env)->NewStringUTF(env, buffer);
        jclass cls = (*env)->GetObjectClass(env, string);
        jmethodID method = (*env)->GetMethodID(env, cls, "append",
            "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
        (*env)->CallObjectMethod(env, string, method, tmp);
    }
    return result;
}

/**
 * long getSessionData(Device)
 */
JNIEXPORT jlong JNICALL METHOD_NAME(LibUsb, getSessionData)
(
    JNIEnv *env, jclass class, jobject device
)
{
    libusb_device *dev;

    VALIDATE_NOT_NULL(env, device, return 0);
    dev = unwrapDevice(env, device);
    if (!dev) return 0;
    return (jlong) (uintptr_t) libusb_get_session_data(dev);
}

/**
 * int getMaxAltPacketSize(Device, int, int, byte)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getMaxAltPacketSize)
(
    JNIEnv *env, jclass class, jobject device, jint interfaceNumber,
    jint alternateSetting, jbyte endpoint
)
{
    libusb_device *dev;

    VALIDATE_NOT_NULL(env, device, return 0);
    dev = unwrapDevice(env, device);
    if (!dev) return 0;
    return libusb_get_max_alt_packet_size(dev, (int) interfaceNumber,
        (int) alternateSetting, (unsigned char) endpoint);
}

/**
 * int wrapSysDevice(Context, long, DeviceHandle)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, wrapSysDevice)
(
    JNIEnv *env, jclass class, jobject context, jlong sysDev, jobject handle
)
{
    libusb_context *ctx;
    libusb_device_handle *deviceHandle;
    int result;

    VALIDATE_NOT_NULL(env, handle, return 0);
    VALIDATE_POINTER_NOT_SET(env, handle, "deviceHandlePointer", return 0);
    ctx = unwrapContext(env, context);
    if (!ctx && context) return 0;
    result = libusb_wrap_sys_device(ctx, (intptr_t) sysDev, &deviceHandle);
    if (result == LIBUSB_SUCCESS) setDeviceHandle(env, deviceHandle, handle);
    return result;
}

/**
 * int getSsPlusUsbDeviceCapabilityDescriptor(Context, BosDevCapabilityDescriptor,
 *     SsPlusUsbDeviceCapabilityDescriptor)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getSsPlusUsbDeviceCapabilityDescriptor)
(
    JNIEnv *env, jclass class, jobject context, jobject devCapDescriptor,
    jobject ssPlusDescriptor
)
{
    struct libusb_bos_dev_capability_descriptor *devcap;
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor;
    libusb_context *ctx;
    int result;

    ctx = unwrapContext(env, context);
    if (!ctx && context) return 0;
    VALIDATE_NOT_NULL(env, devCapDescriptor, return 0);
    VALIDATE_NOT_NULL(env, ssPlusDescriptor, return 0);
    VALIDATE_POINTER_NOT_SET(env, ssPlusDescriptor,
        "ssPlusUsbDeviceCapabilityDescriptorPointer", return 0);
    devcap = unwrapBosDevCapabilityDescriptor(env, devCapDescriptor);
    if (!devcap) return 0;
    result = libusb_get_ssplus_usb_device_capability_descriptor(ctx, devcap,
        &descriptor);
    if (result == LIBUSB_SUCCESS)
        setSsPlusUsbDeviceCapabilityDescriptor(env, descriptor, ssPlusDescriptor);
    return result;
}

/**
 * void freeSsPlusUsbDeviceCapabilityDescriptor(SsPlusUsbDeviceCapabilityDescriptor)
 */
JNIEXPORT void JNICALL METHOD_NAME(LibUsb, freeSsPlusUsbDeviceCapabilityDescriptor)
(
    JNIEnv *env, jclass class, jobject ssPlusDescriptor
)
{
    struct libusb_ssplus_usb_device_capability_descriptor *descriptor;

    if (!ssPlusDescriptor) return;
    descriptor = unwrapSsPlusUsbDeviceCapabilityDescriptor(env, ssPlusDescriptor);
    if (!descriptor) return;
    libusb_free_ssplus_usb_device_capability_descriptor(descriptor);
    resetSsPlusUsbDeviceCapabilityDescriptor(env, ssPlusDescriptor);
}

/**
 * int getPlatformDescriptor(Context, BosDevCapabilityDescriptor, PlatformDescriptor)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getPlatformDescriptor)
(
    JNIEnv *env, jclass class, jobject context, jobject devCapDescriptor,
    jobject platformDescriptor
)
{
    struct libusb_bos_dev_capability_descriptor *devcap;
    struct libusb_platform_descriptor *descriptor;
    libusb_context *ctx;
    int result;

    ctx = unwrapContext(env, context);
    if (!ctx && context) return 0;
    VALIDATE_NOT_NULL(env, devCapDescriptor, return 0);
    VALIDATE_NOT_NULL(env, platformDescriptor, return 0);
    VALIDATE_POINTER_NOT_SET(env, platformDescriptor, "platformDescriptorPointer",
        return 0);
    devcap = unwrapBosDevCapabilityDescriptor(env, devCapDescriptor);
    if (!devcap) return 0;
    result = libusb_get_platform_descriptor(ctx, devcap, &descriptor);
    if (result == LIBUSB_SUCCESS)
        setPlatformDescriptor(env, descriptor, platformDescriptor);
    return result;
}

/**
 * void freePlatformDescriptor(PlatformDescriptor)
 */
JNIEXPORT void JNICALL METHOD_NAME(LibUsb, freePlatformDescriptor)
(
    JNIEnv *env, jclass class, jobject platformDescriptor
)
{
    struct libusb_platform_descriptor *descriptor;

    if (!platformDescriptor) return;
    descriptor = unwrapPlatformDescriptor(env, platformDescriptor);
    if (!descriptor) return;
    libusb_free_platform_descriptor(descriptor);
    resetPlatformDescriptor(env, platformDescriptor);
}

/**
 * int getInterfaceAssociationDescriptors(Device, byte, InterfaceAssociationDescriptors)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getInterfaceAssociationDescriptors)
(
    JNIEnv *env, jclass class, jobject device, jbyte configIndex, jobject array
)
{
    libusb_device *dev;
    struct libusb_interface_association_descriptor_array *iad;
    int result;

    VALIDATE_NOT_NULL(env, device, return 0);
    VALIDATE_NOT_NULL(env, array, return 0);
    VALIDATE_POINTER_NOT_SET(env, array, "interfaceAssociationDescriptorsPointer",
        return 0);
    dev = unwrapDevice(env, device);
    if (!dev) return 0;
    result = libusb_get_interface_association_descriptors(dev,
        (uint8_t) configIndex, &iad);
    if (result == LIBUSB_SUCCESS)
        setInterfaceAssociationDescriptors(env, iad, array);
    return result;
}

/**
 * int getActiveInterfaceAssociationDescriptors(Device, InterfaceAssociationDescriptors)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getActiveInterfaceAssociationDescriptors)
(
    JNIEnv *env, jclass class, jobject device, jobject array
)
{
    libusb_device *dev;
    struct libusb_interface_association_descriptor_array *iad;
    int result;

    VALIDATE_NOT_NULL(env, device, return 0);
    VALIDATE_NOT_NULL(env, array, return 0);
    VALIDATE_POINTER_NOT_SET(env, array, "interfaceAssociationDescriptorsPointer",
        return 0);
    dev = unwrapDevice(env, device);
    if (!dev) return 0;
    result = libusb_get_active_interface_association_descriptors(dev, &iad);
    if (result == LIBUSB_SUCCESS)
        setInterfaceAssociationDescriptors(env, iad, array);
    return result;
}

/**
 * void freeInterfaceAssociationDescriptors(InterfaceAssociationDescriptors)
 */
JNIEXPORT void JNICALL METHOD_NAME(LibUsb, freeInterfaceAssociationDescriptors)
(
    JNIEnv *env, jclass class, jobject array
)
{
    struct libusb_interface_association_descriptor_array *iad;

    if (!array) return;
    iad = unwrapInterfaceAssociationDescriptors(env, array);
    if (!iad) return;
    libusb_free_interface_association_descriptors(iad);
    resetInterfaceAssociationDescriptors(env, array);
}

/**
 * int endpointSupportsRawIo(DeviceHandle, byte)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, endpointSupportsRawIo)
(
    JNIEnv *env, jclass class, jobject handle, jbyte endpoint
)
{
    libusb_device_handle *dev_handle;

    VALIDATE_NOT_NULL(env, handle, return 0);
    dev_handle = unwrapDeviceHandle(env, handle);
    if (!dev_handle) return 0;
    return libusb_endpoint_supports_raw_io(dev_handle, (uint8_t) endpoint);
}

/**
 * int endpointSetRawIo(DeviceHandle, byte, boolean)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, endpointSetRawIo)
(
    JNIEnv *env, jclass class, jobject handle, jbyte endpoint, jboolean enable
)
{
    libusb_device_handle *dev_handle;

    VALIDATE_NOT_NULL(env, handle, return 0);
    dev_handle = unwrapDeviceHandle(env, handle);
    if (!dev_handle) return 0;
    return libusb_endpoint_set_raw_io(dev_handle, (uint8_t) endpoint,
        enable ? 1 : 0);
}

/**
 * int getMaxRawIoTransferSize(DeviceHandle, byte)
 */
JNIEXPORT jint JNICALL METHOD_NAME(LibUsb, getMaxRawIoTransferSize)
(
    JNIEnv *env, jclass class, jobject handle, jbyte endpoint
)
{
    libusb_device_handle *dev_handle;

    VALIDATE_NOT_NULL(env, handle, return 0);
    dev_handle = unwrapDeviceHandle(env, handle);
    if (!dev_handle) return 0;
    return libusb_get_max_raw_io_transfer_size(dev_handle, (uint8_t) endpoint);
}
