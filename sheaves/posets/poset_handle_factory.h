// $RCSfile: poset_handle_factory.h,v $ $Revision: 1.13 $ $Date: 2013/01/12 17:17:42 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class poset_handle_factory

#ifndef POSET_HANDLE_FACTORY_H
#define POSET_HANDLE_FACTORY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef POSET_TYPE_H
#include "poset_type.h"
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
class poset_state_handle;
  
///
/// A factory for creating poset handles.
///
class SHEAF_DLL_SPEC poset_handle_factory
{
public:

  // ===========================================================
  // POSET_HANDLE_FACTORY FACET
  // ===========================================================

  ///
  /// Default constructor.
  ///
  ///
  poset_handle_factory();

  ///
  /// Destructor
  ///
  virtual ~poset_handle_factory();

  ///
  /// Creates an unattached handle of type xclient_class_name
  /// or type xsheaf_base_class_id if no prototype for xclient_class_name.
  ///
  poset_state_handle* new_poset_handle(const string& xclient_class_name,
                                       poset_type xsheaf_base_class_id);

  ///
  /// Sets xprototype as the prototype for its client class.
  ///
  void insert_prototype(const poset_state_handle* xprototype);

  ///
  /// Sets xprototype as the prototype for type xtype_id.
  ///
  void insert_prototype(poset_type xtype_id,
                        const poset_state_handle* xprototype);

  ///
  /// Removes the prototype for handles of type xclass_name.
  ///
  void delete_prototype(const string& xclass_name);

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xclass_name.
  ///
  bool contains_prototype(const string& xclass_name) const;

  ///
  /// True if the set of prototypes contains a
  /// prototype for handles of type xtype_id.
  ///
  bool contains_prototype(poset_type xtype_id) const;

private:

  ///
  /// Copy constructor; disabled.
  ///
  ///
  poset_handle_factory(const poset_handle_factory& xother)
  {}
  ;

  ///
  /// The type of the poset handle prototypes map.
  ///
  typedef map<string, poset_state_handle*> prototypes_map_type;

  ///
  /// The client poset handle prototypes map.
  ///
  prototypes_map_type _prototypes_map;

  ///
  /// The sheaf base class handle prototypes map.
  ///
  block<poset_state_handle*> _sheaf_prototypes_map;

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef POSET_HANDLE_FACTORY_H
