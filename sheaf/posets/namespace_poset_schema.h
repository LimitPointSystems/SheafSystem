
//
// Copyright (c) 2014 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @file
/// Interface for class namespace_poset_schema

#ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_POSET_SCHEMA_H
#define COM_LIMITPOINT_SHEAF_NAMESPACE_POSET_SCHEMA_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_H
#include "ComLimitPoint/sheaf/poset.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/poset_member.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_STATE_HANDLE_H
#include "ComLimitPoint/sheaf/poset_state_handle.h"
#endif

namespace sheaf
{

class namespace_poset;
class subposet;
  
///
/// The schema poset for the namespace.
///
class SHEAF_DLL_SPEC namespace_poset_schema : public poset_state_handle
{

  friend class namespace_poset;
  friend class primitives_poset;

  // ===========================================================
  /// @name NAMESPACE_POSET_SCHEMA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The standard name for an instance of this class.
  ///
  static const std::string& standard_name();

protected:

private:

  ///
  /// Creates an unattached handle
  ///
  namespace_poset_schema();

  ///
  /// Creates a new handle attached to a new state not in any namespace.
  ///
  namespace_poset_schema(abstract_poset_member* xschema,
                         bool xauto_access = true);

  ///
  /// Destructor
  ///
  ~namespace_poset_schema();

  ///
  /// Handle for subposet which identifies table dofs.
  ///
  subposet* _table_dof_subposet;

  ///
  /// Handle for subposet which idnetifies row dofs.
  ///
  subposet* _row_dof_subposet;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// True if xdof_map conforms to (i.e. is derived from) the type of
  /// row dof map required by this poset
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

protected:

  ///
  /// Creates the subposets common to every poset (i.e._whole and _jims) plus
  /// those required of a schema poset (table_dofs and row_dofs)
  ///
  virtual void initialize_standard_subposets(const std::string& xname);

  ///
  /// Initializes the predefined members of the poset.
  ///
  virtual void initialize_standard_members();

private:

  using poset_state_handle::new_state;

  ///
  /// Creates a new namespace_poset_schema state, not in any namespace.
  ///
  void new_state(const abstract_poset_member* xschema, bool xauto_access = true);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant
  ///
  bool invariant() const;

protected:

private:

  ///
  /// Make a new instance of the same type as this
  ///
  virtual namespace_poset_schema* clone() const;

  //@}
};

} // namespace sheaf

#endif // ifndef COM_LIMITPOINT_SHEAF_NAMESPACE_POSET_SCHEMA_H

