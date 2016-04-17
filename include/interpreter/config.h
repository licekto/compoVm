#pragma once

/* Main component and main component (a la "public static void main()" */
/******************************************************************************/

// Name of root component
#define COMPO_MAIN_COMPONENT_NAME "CompoContainer"

// Name of main service in root component
#define COMPO_MAIN_SERVICE_NAME "main"

/* Core Compo modules paths */
/******************************************************************************/

// Name of kernel Collection Port file
#define KERNEL_COLLECTION_PORT_PATH "../coreModules/collectionPort.cp"

// Name of kernel Component file
#define KERNEL_COMPONENT_PATH "../coreModules/component.cp"

// Name of kernel Connection Description file
#define KERNEL_CONNECTION_DESCRIPTION_PATH "../coreModules/connectionDescription.cp"

// Name of kernel Descriptor file
#define KERNEL_DESCRIPTOR_PATH "../coreModules/descriptor.cp"

// Name of kernel Interface file
#define KERNEL_INTERFACE_PATH "../coreModules/interface.cp"

// Name of kernel Port file
#define KERNEL_PORT_PATH "../coreModules/port.cp"

// Name of kernel Port Description file
#define KERNEL_PORT_DESCRIPTION_PATH "../coreModules/portDescription.cp"

// Name of kernel Service file
#define KERNEL_SERVICE_PATH "../coreModules/service.cp"

// Name of kernel Service Signature file
#define KERNEL_SERVICE_SIGNATURE_PATH "../coreModules/serviceSignature.cp"

#define KERNEL_SERVICE_INVOCATION_PATH "../coreModules/serviceInvocation.cp"

/* Names of value components */
/******************************************************************************/

// Name of core component representing string
#define COMPONENT_STRING_NAME "String"

// Name of core component representing integer
#define COMPONENT_INTEGER_NAME "Integer"

// Name of core component representing boolean
#define COMPONENT_BOOLEAN_NAME "Boolean"

/* Names of frequently used ports */
/******************************************************************************/

// Name of port that is always connected to the name of the component
#define NAME_OF_NAMEPORT "name"

/* String representation of types of inner Compo elements */
/******************************************************************************/

// String for requirement role
#define ROLE_REQUIREMENT "requires"

// String for provision role
#define ROLE_PROVISION "provides"

// String for external visibility
#define VISIBILITY_EXTERNAL "externally"

// String for internal visibility
#define VISIBILITY_INTERNAL "internally"

// String for universal port type
#define PORT_TYPE_UNIVERSAL "universal"

// String for signatures port type
#define PORT_TYPE_SIGNATURES "signatures"

// String for named port type
#define PORT_TYPE_NAMED "named"

// String for injected port type
#define PORT_TYPE_INJECTED "injected"

/* String representation of types of connection addresses */
/******************************************************************************/

// String for named port
#define CONNECTION_NAMED "named"

// String for service invocation
#define CONNECTION_INVOCATION "invocation"

// String for collection port
#define CONNECTION_COLLECTION "collection"

// String for dereference
#define CONNECTION_DEREFERENCE "dereference"

/* String representation of types of bindings */
/******************************************************************************/

// String for connection bind type
#define BIND_CONNECTION "connection"

// String for disconnection bind type
#define BIND_DISCONNECTION "disconnection"

// String for delegation bind type
#define BIND_DELEGATION "delegation"
