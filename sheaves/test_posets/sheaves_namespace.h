
// $RCSfile: sheaves_namespace.h,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:50 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class sheaves_namespace

#ifndef SHEAVES_NAMESPACE_H
#define SHEAVES_NAMESPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef NAMESPACE_POSET_H
#include "namespace_poset.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{
  
///
/// The standard sheaves name space.
///
class SHEAF_DLL_SPEC sheaves_namespace : public namespace_poset
{


public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates an unattached handle.
  ///
  sheaves_namespace();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  sheaves_namespace(const sheaves_namespace& xother);

  ///
  /// Destructor
  ///
  virtual ~sheaves_namespace();

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a sheaves namespace with name xname.
  ///
  sheaves_namespace(const string& xname);

  ///
  /// Creates a triangle schema using the primatives poset.  This
  /// static function is used for test drivers.
  ///
  static void make_triangle(sheaves_namespace* xns);

protected:

  ///
  /// Covariant constructor.
  ///
  sheaves_namespace(namespace_poset_member* xtop, namespace_poset_member* xbottom);


};
  
} // namespace sheaf

#endif // ifndef SHEAVES_NAMESPACE_H
