#pragma once

#include "common.h"


namespace lib {


  namespace m {


    TP<TN T0, ssize_t... NN>
    struct vec_t {

      static constexpr ssize_t _size = sizeof...( NN );

      TP<TN U0>
      constexpr explicit vec_t( U0 arg ) : _data{ ( (void)NN, arg )... } { }

      TP<TN... UU>
      constexpr explicit vec_t( UU... args ) : _data{ args... } { }

      auto& operator[]( ssize_t idx ) { check_bounds( idx ); return _data[ idx ]; }
      auto& operator[]( ssize_t idx ) const { check_bounds( idx ); return _data[ idx ]; }

      auto& data() { return _data; }
      auto& data() const { return _data; }
      auto  size() const { return _size; }

      auto length() const { sqrt( dot( $this, $this ) ); }

      void check_bounds( ssize_t idx ) const { $assert( idx < size(), "out of bounds" ); }


      T0 _data[ _size ];
    };


    TP<TN T0, TN T1> 
    struct define_vector_t;

    TP<TN T0, ssize_t... NN> 
    struct define_vector_t< T0, lib::index_list< NN...> > { using type = vec_t< T0, NN... >; };

    TP<TN T0, ssize_t N0>
    using vec = typename define_vector_t< T0, lib::index_list_t< N0 > >::type;

    TP<ssize_t N0>
    using vecf = typename define_vector_t< float, lib::index_list_t< N0 > >::type;

    TP<ssize_t N0>
    using vecd = typename define_vector_t< double, lib::index_list_t< N0 > >::type;



    TP<TN T0, ssize_t... NN>
    struct mat_t {

      static constexpr ssize_t _size = sizeof...( NN );

      TP<TN U0>
      constexpr explicit mat_t( U0 arg ) : _data{ ( (void)NN, vec< T0, _size >{ arg } )... } { }

      TP<TN... UU>
      constexpr explicit mat_t( UU... args ) : _data{ args... } { }

      auto& operator[]( ssize_t idx ) { check_bounds( idx ); return _data[ idx ]; }
      auto& operator[]( ssize_t idx ) const { check_bounds( idx ); return _data[ idx ]; }

      auto& data() { return _data; }
      auto& data() const { return _data; }
      auto  size() const { return _size; }

      void check_bounds( ssize_t idx ) const { $assert( idx < size(), "out of bounds" ); }


      vec< T0, _size > _data[ _size ];
    };


    TP<TN T0, TN T1> 
    struct define_mat_t;

    TP<TN T0, ssize_t... NN> 
    struct define_mat_t< T0, lib::index_list< NN...> > { using type = mat_t< T0, NN... >; };

    TP<TN T0, ssize_t N0>
    using mat = typename define_mat_t< T0, lib::index_list_t< N0 > >::type;

    TP<ssize_t N0>
    using matf = typename define_mat_t< float, lib::index_list_t< N0 > >::type;

    TP<ssize_t N0>
    using matd = typename define_mat_t< double, lib::index_list_t< N0 > >::type;


  }

}





