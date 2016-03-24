#pragma once

#include <memory>

#define ptr(x) std::shared_ptr<x>
#define wptr(x) std::weak_ptr<x>
#define new_ptr(x) std::make_shared<x>
#define cast(x) std::dynamic_pointer_cast<x>