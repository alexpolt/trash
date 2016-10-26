#pragma once

#include "config.h"
#include "macros.h"
#include "assert.h"
#include "types.h"
#include "range.h"
#include "buffer.h"
#include "error.h"
#include "memory.h"
#include "log.h"
#include "algo.h"
#include "scope-guard.h"
#include "vector.h"
#include "string.h"
#include "value.h"
#include "object.h"
#include "result.h"
#include "owner-ptr.h"
#include "shared-ptr.h"

//#include ""

using lib::object;
using lib::interface;
using lib::component;
using lib::value;
using lib::make_out;
using lib::range;
using lib::move;
using lib::forward;
using lib::log::info;
using lib::log::endl;
using lib::vector;
using lib::string;
using lib::result;
using lib::optional;
using lib::owner_ptr;
using lib::shared_ptr;
using lib::weak_ptr;
using lib::make_owner;
using lib::make_shared;

