#pragma once

#include "macros.h"

namespace lib {

  TP<TN T0, TN T1> 
  auto max( T0 const& arg0, T1 const& arg1 ) { return arg0 > arg1 ? arg0 : arg1; }

}

