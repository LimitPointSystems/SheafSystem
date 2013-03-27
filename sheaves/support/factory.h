// $RCSfile: factory.h,v $ $Revision: 1.19 $ $Date: 2013/01/12 17:17:46 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//



// Interface for class factory

#ifndef FACTORY_H
#define FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_MAP_H
#include "std_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class namespace_poset;
  
// Forward declarations to enable friend declaration.

template <typename T>
class factory;

template <typename T>
ostream& operator << (ostream &os, const factory<T>& xf);


///
/// A factory for instanting descendants of an abstract type T,
/// given the class name of the descendant.
/// Requires:
///  virtual const string& T::class_name()
///     the actual (descendant) class name of the prototype.
///  virtual T* T::clone()
///     virtual default constructor
///  virtual bool is_initialized()
///     true if instance is fully initialized
///
template <typename T>
class factory
{
  friend ostream& operator << <T> (ostream& xos, const factory<T>& xf);

public:

  // ===========================================================
  // FACTORY FACET
  // ===========================================================

  ///
  /// Default constructor.
  ///
  ///
  factory();

  ///
  /// Destructor
  ///
  virtual ~factory();

  ///
  /// Creates an instance of type xclient_class_name.
  ///
  T* new_instance(const string& xclient_class_name);

  ///
  /// Creates an instance of type xclient_class_name and initializes it with xname_space.
  ///
  template<typename S>
  T* new_instance(const string& xclient_class_name, S& xarg);

  ///
  /// Sets xprototype as the prototype for its client class.
  ///
  void insert_prototype(T* xprototype);

  ///
  /// Removes the prototype for handles of type xclass_name.
  ///
  void delete_prototype(const string& xclass_name);

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xclass_name.
  ///
  bool contains_prototype(const string& xclass_name) const;

private:

  ///
  /// Copy constructor; disabled.
  ///
  ///
  factory(const factory& xother);

  ///
  /// The type of the prototypes map.
  ///
  typedef map<string, T*> prototypes_map_type;

  ///
  /// The client prototypes map.
  ///
  prototypes_map_type _prototypes_map;
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// Inserts factory& xf in stream xos.
///
template <typename T>
ostream& operator << (ostream& xos, const factory<T>& xf);
 
} // namespace sheaf

#endif // ifndef FACTORY_H
