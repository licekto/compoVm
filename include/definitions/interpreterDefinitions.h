#pragma once

#include "interpreter/core/coreModules.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/memory/manager/manager.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitivePort.h"
#include "interpreter/memory/objects/serviceCode.h"

using core_modules = interpreter::core::CCoreModules;
using core_interpreter = interpreter::core::CInterpreter;

using mem_manager = interpreter::memory::manager::CManager;

using mem_component = interpreter::memory::objects::CComponent;
using mem_primitivePort = interpreter::memory::objects::CPrimitivePort;
using mem_service = interpreter::memory::objects::CService;