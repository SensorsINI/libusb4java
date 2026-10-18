/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#include "InterfaceAssociationDescriptor.h"

jobject wrapInterfaceAssociationDescriptor(JNIEnv* env,
    const struct libusb_interface_association_descriptor* descriptor)
{
    return wrapPointer(env, descriptor, CLASS_PATH("InterfaceAssociationDescriptor"),
        "interfaceAssociationDescriptorPointer");
}

struct libusb_interface_association_descriptor*
unwrapInterfaceAssociationDescriptor(JNIEnv* env, jobject descriptor)
{
    return (struct libusb_interface_association_descriptor*) unwrapPointer(env,
        descriptor, "interfaceAssociationDescriptorPointer");
}

/**
 * byte bLength()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bLength;
}

/**
 * byte bDescriptorType()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bDescriptorType)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bDescriptorType;
}

/**
 * byte bFirstInterface()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bFirstInterface)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bFirstInterface;
}

/**
 * byte bInterfaceCount()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bInterfaceCount)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bInterfaceCount;
}

/**
 * byte bFunctionClass()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bFunctionClass)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bFunctionClass;
}

/**
 * byte bFunctionSubClass()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bFunctionSubClass)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bFunctionSubClass;
}

/**
 * byte bFunctionProtocol()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, bFunctionProtocol)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->bFunctionProtocol;
}

/**
 * byte iFunction()
 */
JNIEXPORT jbyte JNICALL METHOD_NAME(InterfaceAssociationDescriptor, iFunction)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor *descriptor =
        unwrapInterfaceAssociationDescriptor(env, this);
    if (!descriptor) return 0;
    return (jbyte) descriptor->iFunction;
}
