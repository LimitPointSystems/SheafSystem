
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class dof_tuple_domain_offsets_record

#ifndef DOF_TUPLE_DOMAIN_OFFSETS_RECORD_H
#define DOF_TUPLE_DOMAIN_OFFSETS_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATTRIBUTES_RECORD_H
#include "attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the dof tuple domain offsets record.
/// Intended for transferring index-offsets map data
/// between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC dof_tuple_domain_offsets_record : public attributes_record
{
public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  // CANONICAL MEMBERS

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual dof_tuple_domain_offsets_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;


  // =============================================================================
  // DOF_TUPLE_DOMAIN_OFFSETS_RECORD FACET
  // =============================================================================

  ///
  /// Creates an instance with type map xtype_map
  ///
  dof_tuple_domain_offsets_record(poset_scaffold& xscaffold);

  ///
  /// Copy constructor
  ///
  ///
  dof_tuple_domain_offsets_record(const dof_tuple_domain_offsets_record& xother);

  ///
  /// Destructor
  ///
  virtual ~dof_tuple_domain_offsets_record();

protected:

  ///
  /// Initializes the poset from the internal buffer.
  ///
  void transfer_internal_buffer_to_poset();

  ///
  /// Initializes the internal buffer from the poset.
  ///
  void transfer_poset_to_internal_buffer();

};
  
} // namespace sheaf

#endif // ifndef DOF_TUPLE_DOMAIN_OFFSETS_RECORD_H





