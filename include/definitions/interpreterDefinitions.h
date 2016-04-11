#pragma once

#include "interpreter/core/coreModules.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "interpreter/memory/objects/component.h"

using core_modules = interpreter::core::CCoreModules;
using core_interpreter = interpreter::core::CInterpreter;
using core_bootstrap1 = interpreter::core::bootstrap::CBootstrapStage1;

using mem_component = interpreter::memory::objects::CComponent;
