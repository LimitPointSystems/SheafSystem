
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class connectivity_array

#ifndef CONNECTIVITY_ARRAY_H
#define CONNECTIVITY_ARRAY_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef RAGGED_ARRAY_H
#include "ragged_array.h"
#endif

#ifndef SCOPED_INDEX_H
#include "scoped_index.h"
#endif

namespace fiber_bundle
{
  
  using namespace sheaf;

///
/// A ragged array for storing the results of
/// a connectivity query.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC connectivity_array : public ragged_array<scoped_index>
{

public:

  ///
  /// Reference counted pointer type.
  ///
  typedef rc_ptr<connectivity_array> ptr;

  // CANONICAL MEMBERS

  ///
  /// Copy constructor
  ///
  ///
  connectivity_array(const connectivity_array& xother);

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual connectivity_array* clone() const;


  ///
  /// Destructor
  ///
  virtual ~connectivity_array();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;


  // CONNECTIVITY_ARRAY FACET

  //$$SCRIBBLE: Note that this is NOT currently private.
  //            Maybe this constructor should be moved to the
  //            private section.

  ///
  /// Default constructor; private to prevent default construction.
  ///
  connectivity_array() {};

  ///
  /// Creates an instance with xrow_ct rows, with the number
  /// of columns in the i-th row given by xcol_cts[i].
  ///
  connectivity_array(index_type* xcol_cts,
                     index_type xcol_cts_ub);

  ///
  /// Creates an instance with xrow_ct rows and
  /// xvalue_ct values.
  ///
  connectivity_array(index_type xrow_ct, index_type xvalue_ct);

  ///
  /// The naked, underlying storage for the type of each upper level cell.
  ///
  scoped_index* types() const;

  ///
  /// The local coordinate type for row xrow_index.
  ///
  scoped_index type(index_type xrow_index) const;

protected:


private:

  ///
  /// The local coordinate type for each upper level cell.
  ///
  block<scoped_index> _types;


};
  
} // namespace fiber_bundle

#endif // ifndef CONNECTIVITY_ARRAY_H






