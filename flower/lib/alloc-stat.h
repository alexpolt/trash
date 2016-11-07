#pragma once

#include <cstdio>

#include "macros.h"
#include "types.h"
#include "memory.h"
#include "allocator.h"
#include "value.h"


namespace lib {


  struct alloc_empty : allocator {


    static auto create() { return value< allocator >::create< alloc_empty >(); }

    value< allocator > get_copy() const override {

      return value< allocator >::create< alloc_empty >();
    }

    char* alloc( ssize_t sz ) override {

      log::memory, "alloc_stat::alloc( ", sz, " )", log::endl;

      total += sz;

      return $alloc( sz );
    }

    void free( void* ptr, ssize_t sz ) override { 

      log::memory, "alloc_empty::free( ", ptr, ", ", sz, " )", log::endl;

      $free( this, ptr, sz );
    }

    ssize_t size() const override { return 0; }

    ssize_t available() const override { return 0; }

    ssize_t _total;
 };

}

