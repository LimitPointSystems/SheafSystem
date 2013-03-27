// $RCSfile: poset_state.h,v $ $Revision: 1.29 $ $Date: 2013/01/12 17:17:42 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET_STATE

#ifndef POSET_STATE_H
#define POSET_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef READ_WRITE_MONITOR_H
#include "read_write_monitor.h"
#endif

#ifndef POSET_TYPE_H
#include "poset_type.h"
#endif


namespace sheaf
{

class abstract_poset_member;
class array_poset_dof_map;
class poset_crg_state;
class poset_powerset_state;
class poset_table_state;
class schema_poset_member;  

///
/// The private state of a partially ordered set.
///
class SHEAF_DLL_SPEC poset_state: public read_write_monitor
{

  friend SHEAF_DLL_SPEC size_t deep_size(const poset_state& xp, bool xinclude_shallow, size_t xresults[4]);

  // ===========================================================
  /// @name POSET_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Constructor
  ///
  poset_state(const abstract_poset_member* xschema,
              poset_type xtype_id,
              size_type xmbr_ct = 16,
              size_type xlink_ct = 64,
              size_type xsubset_ct = 4);

  ///
  /// Destructor
  ///
  ~poset_state();

  ///
  /// Identifier for the type of this poset.
  ///
  poset_type type_id() const;

  //   ///
  ///   /// The name of the type of poset.
  //   ///
  //   const char* poset_class();

  ///
  /// Cover relation graph
  ///
  poset_crg_state* crg();

  ///
  /// Set of subposets (powerset)
  ///
  poset_powerset_state* powerset();

  ///
  /// Table (dof tuples).
  ///
  poset_table_state* table() const;

protected:

  ///
  /// Default constructor;
  /// private to disable default construction.
  ///
  poset_state() {};

  ///
  /// Identifier for the type of poset.
  ///
  poset_type _type_id;

  ///
  /// The cover relation graph for this poset.
  ///
  poset_crg_state* _crg;

  ///
  /// The set of subposets for this poset  .
  ///
  poset_powerset_state* _powerset;

  ///
  /// The table of dof tuples for this poset.
  ///
  poset_table_state* _table;

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual poset_state* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// The deep size of the referenced object of type poset_state.
/// if xinclude_shallow, add the sizeof xp to the result.
/// if xresults is not null, the deep size of the poset_state parts returned;
/// xresults[0] is the deep_size of poset_crg_state,
/// xresults[1] is the deep_size of poset_powerset_state,
/// xresults[2] is the deep_size of poset_table_state.
///
SHEAF_DLL_SPEC size_t deep_size(const poset_state& xp,
		 bool xinclude_shallow = true,
		 size_t xresults[4] = 0);

} // namespace poset

#endif // ifndef POSET_STATE_H

