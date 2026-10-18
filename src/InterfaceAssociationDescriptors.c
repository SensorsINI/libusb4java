/*
 * Copyright 2026 SensorsINI
 * See LICENSE.md file for copying conditions
 */

#include "InterfaceAssociationDescriptors.h"
#include "InterfaceAssociationDescriptor.h"

void setInterfaceAssociationDescriptors(JNIEnv* env,
    const struct libusb_interface_association_descriptor_array* array,
    jobject object)
{
    SET_POINTER(env, array, object, "interfaceAssociationDescriptorsPointer");
}

struct libusb_interface_association_descriptor_array*
unwrapInterfaceAssociationDescriptors(JNIEnv* env, jobject array)
{
    return (struct libusb_interface_association_descriptor_array*) unwrapPointer(
        env, array, "interfaceAssociationDescriptorsPointer");
}

void resetInterfaceAssociationDescriptors(JNIEnv* env, jobject obj)
{
    RESET_POINTER(env, obj, "interfaceAssociationDescriptorsPointer");
}

/**
 * int length()
 */
JNIEXPORT jint JNICALL METHOD_NAME(InterfaceAssociationDescriptors, getLength)
(
    JNIEnv *env, jobject this
)
{
    struct libusb_interface_association_descriptor_array *array =
        unwrapInterfaceAssociationDescriptors(env, this);
    if (!array) return 0;
    return array->length;
}

/**
 * InterfaceAssociationDescriptor get(int)
 */
JNIEXPORT jobject JNICALL METHOD_NAME(InterfaceAssociationDescriptors, get)
(
    JNIEnv *env, jobject this, jint index
)
{
    struct libusb_interface_association_descriptor_array *array =
        unwrapInterfaceAssociationDescriptors(env, this);
    if (!array) return NULL;
    if (index < 0 || index >= array->length)
    {
        illegalArgument(env, "interface association index out of range");
        return NULL;
    }
    return wrapInterfaceAssociationDescriptor(env, &array->iad[index]);
}
