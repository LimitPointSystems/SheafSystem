

//
// Copyright (c) 2013 Limit Point Systems, Inc. 

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class gln_space.

#ifndef GLN_SPACE_H
#define GLN_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef GLN_TABLE_DOFS_TYPE_H
#include "gln_table_dofs_type.h"
#endif
 

namespace sheaf
{
  class arg_list;
  class namespace_poset;
}

namespace fiber_bundle
{

  using namespace sheaf;  

  class gln;
  
///
/// A Cartesian product space.
///
class SHEAF_DLL_SPEC gln_space : public poset
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name GLN_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef gln member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef gln_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xn,
				const poset_path& xscalar_space_path,
				const poset_path& xvector_space_path);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n() const;

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n(bool xauto_access) const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  ///
  /// Dimension of this as a vector space; auto-access version.
  ///
  int d(bool xauto_access) const;
 

protected:

  ///
  /// Default constructor;
  /// creates a new gln_space handle not attached to any state.
  ///
  gln_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  gln_space(const gln_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~gln_space();

  ///
  /// Covariant constructor
  ///
  gln_space(gln* xtop, gln* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  gln_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the gln_space with
  /// index xindex in namespace xhost.
  ///
  gln_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the gln_space with
  /// index xindex in namespace xhost.
  ///
  gln_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the gln_space with
  /// name xname in namespace xhost.
  ///
  gln_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the gln_space associated
  /// with namespace member xmbr.
  ///
  gln_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}

  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

  using poset::new_state;
 
  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  void new_state(namespace_poset& xhost,
                 const string& xname,
                 const arg_list& xargs,
                 const poset_path& xschema_path,
                 bool xauto_access);

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns, 
				   const string& xname,
				   arg_list& xargs,
				   bool xauto_access);

private:

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
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

  ///
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  gln_space& operator=(const poset_state_handle& xother);

  //@}
 
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual gln_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // GLN_SPACE_H
