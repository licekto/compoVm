#pragma once

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/values/valueComponent.h"
#include "interpreter/memory/objects/values/boolComponent.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "interpreter/memory/objects/values/unsignedIntegerComponent.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"

using mem_component = interpreter::memory::objects::CComponent;
using mem_port = interpreter::memory::objects::CGeneralPort;
using mem_service = interpreter::memory::objects::CGeneralService;

using mem_value = interpreter::memory::objects::values::CValueComponent;
using mem_bool = interpreter::memory::objects::values::CBoolComponent;
using mem_string = interpreter::memory::objects::values::CStringComponent;
using mem_uint = interpreter::memory::objects::values::CUnsignedIntegerComponent;

using mem_primitive = interpreter::memory::objects::primitives::CAbstractPrimitive;
using mem_primitiveport = interpreter::memory::objects::primitives::CPrimitivePort;
using mem_primitiveservice = interpreter::memory::objects::primitives::CPrimitiveService;
