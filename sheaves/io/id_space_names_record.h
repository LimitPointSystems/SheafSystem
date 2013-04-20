
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class id_space_names_record

#ifndef ID_SPACE_NAMES_RECORD_H
#define ID_SPACE_NAMES_RECORD_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ATTRIBUTES_RECORD_H
#include "attributes_record.h"
#endif

namespace sheaf
{
  
///
/// A wrapper/adapter for the id space names record.
/// Intended for transferring id map data
/// between the kernel and the i/o subsystem.
///
///
class SHEAF_DLL_SPEC id_space_names_record : public attributes_record
{
public:

  // =============================================================================
  // ANY FACET
  // =============================================================================

  ///
  /// Virtual constructor;
  /// makes a new instance of
  /// the same type as this
  ///
  virtual id_space_names_record* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // =============================================================================
  // ID_SPACE_NAMES_RECORD FACET
  // =============================================================================

  ///
  /// Creates an instance with type map xtype_map
  ///
  id_space_names_record(poset_scaffold& xscaffold);

  ///
  /// Copy constructor
  ///
  ///
  id_space_names_record(const id_space_names_record& xother);

  ///
  /// Destructor
  ///
  virtual ~id_space_names_record();

protected:

  ///
  /// Initializes member with index xmbr_id from the internal buffer.
  ///
  virtual void transfer_internal_buffer_to_poset();

  ///
  /// Initializes the internal buffer from the member with index xmbr_id.
  ///
  virtual void transfer_poset_to_internal_buffer();
};

} // namespace sheaf

#endif // ifndef ID_SPACE_NAMES_RECORD_H






