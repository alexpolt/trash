#pragma once

#include "lib/macros.h"
#include "lib/types.h"

#include "constant.h"
#include "types.h"
#include "math.h"


namespace lib {

  namespace math {


    TP<TN T0, ssize_t A0>
    constexpr mat< T0, 3 > rotx
    {
      vec< T0, 3 >{ 1, 0, 0 },
      vec< T0, 3 >{ 0, $sin( radians( A0 ) ),  $cos( radians( A0 ) ) },
      vec< T0, 3 >{ 0, $cos( radians( A0 ) ), -$sin( radians( A0 ) ) }
    };

    TP<TN T0, ssize_t A0>
    constexpr mat< T0, 3 > roty
    {
      vec< T0, 3 >{ $cos( radians( A0 ) ), 0, -$sin( radians( A0 ) ) },
      vec< T0, 3 >{ 0, 1, 0 },
      vec< T0, 3 >{ $sin( radians( A0 ) ), 0,  $cos( radians( A0 ) ) }
    };

    TP<TN T0, ssize_t A0>
    constexpr mat< T0, 3 > rotz
    { 
      vec< T0, 3 >{ $cos( radians( A0 ) ), -$sin( radians( A0 ) ), 0 },
      vec< T0, 3 >{ $sin( radians( A0 ) ),  $cos( radians( A0 ) ), 0 },
      vec< T0, 3 >{ 0, 0, 1 }
    };


  }

}

