#pragma once

#include <new>

#include "assert.h"
#include "macros.h"
#include "types.h"
#include "ptr.h"
#include "range.h"
#include "memory.h"

namespace lib {


  TP<TN T0>
  struct vector_iterator;

  TP<TN T0, ssize_t N0>
  auto make_vector( T0 ( &data)[ N0 ] ); 


  TP<TN T0, ssize_t N0 = 0, bool is_string = false>
  struct vector {

    using value_type = T0;
    using size_type = ssize_t;
    using pointer = T0*;
    using reference = T0&;
    using iterator = vector_iterator< vector >;
    using const_iterator = vector_iterator< vector const >;

    vector( ) { if( N0 > 0 ) reserve( N0 ); }

    vector( ssize_t size ) { reserve( size ); }

    vector( value_type ( &data)[ N0 ] ) : _data{ data }, _capacity{ N0 } { }

    TP<TN... UU>
    vector( UU&&... args ) {

      char dummy[] { ( $this << forward<UU>( args ), '\0' )... };
      (void) dummy;
    }

    vector( vector const& other ) = delete;

    vector( vector&& other ) : 
      _data{ move( other._data ) }, 
      _capacity{ move( other._capacity ) },
      _index{ move( other._index ) } { }

    vector& operator=( vector const& other ) = delete;
    vector& operator=( vector&& other ) = delete;

    ~vector() { clear(); free(); }

    void free() {

      if( N0 > 0 ) return;

      $free( $out( _data ), $size( value_type ) * capacity() );

      _capacity = 0; 
    }

    void clear() {

      for( auto i : range{ 0, size() } ) _data[ i ].~value_type();

      _index = 0;
    }

    void reserve( ssize_t size_new ) {

      $assert( size_new > capacity(), "new size must be bigger than current capacity" );

      value_type* data_new = (value_type*) $alloc( $size( value_type ) * size_new );

      for( auto i : range{ 0, size() } ) data_new[ i ] = move( _data[ i ] );

      free();

      _data = data_new;
      _capacity = size_new;
    }

    void check_size() const { $assert( size() > 0, "vector us empty" ); }

    auto& front() { check_size(); return _data[ 0 ]; }
    auto& back() { check_size(); return _data[ _index - 1 ]; }
    auto const& front() const { check_size(); return _data[ 0 ]; }
    auto const& back() const { check_size(); return _data[ _index - 1 ]; }

    void push_back( value_type value ) {

      if( capacity() - size() == 0 ) {

        $assert( N0 == 0, "statically sized vector exceeded" );

        auto size_new = size() ? size() * 7 / 4 : 8;

        reserve( size_new );
      } 

      new( &_data[ _index++ ] ) value_type{ move( value ) }; 
    }

    value_type pop_back() {
      
      check_size();

      auto& value = back();

      --_index;

      return move( value );
    }

    TP<TN... UU>
    void emplace_back( UU... args ) { push_back( value_type{ forward< UU >( args )... } ); }

    iterator erase( size_type index ) { return erase( begin() + index ); }

    iterator erase( iterator it ) {

      $assert( it < end(), "iterator is not valid" );

      if( it == --end() ) 

        pop_back();

      else 

        *it = pop_back();

      return it; 
    }

    auto& operator[]( ssize_t index ) { $assert( index < size(), "out of bounds" ); return _data[ index ]; }
    auto const& operator[]( ssize_t index ) const { $assert( index < size(), "out of bounds" ); return _data[ index ]; }


    TP<TN U0, TN = TN enable_if< $size( U0 ) and is_string >::type >
    auto& operator<<( U0 const* other ) { 

      if( size() > 0 ) pop_back();

      while( *other ) push_back( *other++ );

      push_back( '\0' );

      return $this;
    }

    TP<TN U0, TN = enable_if_t< is_string and !is_container< U0 >::value >>
    auto& operator<<( U0&& other ) { 
      
      if( size() > 0 ) pop_back(); 
      
      emplace_back( move( other ) );

      push_back( '\0' );

      return $this; 
    }

    TP<TN U0, TN = enable_if_t< !is_string and !is_container< U0 >::value >, TN>
    auto& operator<<( U0&& other ) { emplace_back( move( other ) ); return $this; }

    TP<TN U0, TN = enable_if_t< !is_string and is_container< U0 >::value >>
    auto& operator<<( U0 const& other ) { for( auto& e : other ) emplace_back( e ); return $this; }

    TP<TN U0, TN = enable_if_t< !is_string and ! is_ref_t< U0 > and is_container< U0 >::value >, bool = true>
    auto& operator<<( U0&& other ) { for( auto& e : other ) emplace_back( move( e ) ); return $this; }


    TP<TN U0>
    void append( U0 const* data, ssize_t size ) { 
      
      for( auto i : range{ 0, size } ) emplace_back( data[ i ] );
    }


    iterator begin() { return vector_iterator< vector >{ $this, 0 }; }
    iterator end() { return vector_iterator< vector >{ $this, size() }; }

    const_iterator begin() const { return vector_iterator< vector const >{ $this, 0 }; }
    const_iterator end() const { return vector_iterator< vector const >{ $this, size() }; }

    const_iterator cbegin() const { return vector_iterator< vector const >{ $this, 0 }; }
    const_iterator cend() const { return vector_iterator< vector const >{ $this, size() }; }

    auto data() const { return _data; }
    auto size() const { return _index; }
    auto capacity() const { return _capacity; }
    bool empty() const { return size() == 0; }


    pointer _data{};
    size_type _capacity{};
    size_type _index{};
  };


  TP<TN T0>
  struct vector_iterator {

    using iterator = vector_iterator;

    auto operator=( iterator other ) { _index = other._index; return $this; }

    auto operator->() { return &_object[ _index ]; }
    auto& operator[]( ssize_t index ) { return _object[ _index + index ]; }
    auto& operator*() { return _object[ _index ]; }

    auto operator==( iterator other ) { return _index == other._index; }
    auto operator!=( iterator other ) { return _index != other._index; }
    auto operator<( iterator other ) { return _index < other._index; }

    auto operator+( ssize_t index ) { return iterator{ _object, _index + index }; }
    auto operator-( ssize_t index ) { return iterator{ _object, _index - index }; }

    auto operator+=( ssize_t index ) { return iterator{ _object, _index + index }; }
    auto operator-=( ssize_t index ) { return iterator{ _object, _index - index }; }

    auto operator++(int) { return iterator{ _object, _index++ }; }
    auto operator--(int) { return iterator{ _object, _index-- }; }

    auto operator++() { return iterator{ _object, ++_index }; }
    auto operator--() { return iterator{ _object, --_index }; }

    operator vector_iterator< T0 const >() { return vector_iterator< T0 const >{ _object, _index }; }

    T0& _object;
    ssize_t _index;
  };

  TP<TN T0, ssize_t N0>
  auto make_vector( T0 ( &data)[ N0 ] ) { return vector< T0, N0 >{ data };  }


}




