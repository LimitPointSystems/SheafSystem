
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
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
/// Interface for class sec_jcb_space.

#ifndef SEC_JCB_SPACE_H
#define SEC_JCB_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_VD_SPACE_H
#include "sec_vd_space.h"
#endif

#ifndef JCB_TABLE_DOFS_TYPE_H
#include "jcb_table_dofs_type.h"
#endif

namespace sheaf
{
class arg_list;
class namespace_poset;
}

namespace fiber_bundle
{
using namespace sheaf;

class sec_jcb;
class jcb;

///
/// An abstract section space of Jacobians.
///
class SHEAF_DLL_SPEC sec_jcb_space : public sec_vd_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_JCB_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_jcb member_type;

  ///
  /// The fiber type.
  ///
  typedef jcb fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_jcb scalar_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef jcb_table_dofs_type table_dofs_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(const poset_path& xdomain_path, const poset_path& xrange_path);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  using sec_vd_space::d;
  
  ///
  /// Dimension d() as a function of domain dimension xdd and range dimension xdr.
  ///
  static int d(int xdd, int xdr);

  ///
  /// The dimension of the underlying ("domain") vector space.
  ///
  int dd() const;

  ///
  /// The dimension of the underlying ("domain") vector space; auto access signature.
  ///
  int dd(bool xauto_access) const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path() const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path(bool xauto_access) const;

  ///
  /// Dimension of the range.
  ///
  virtual int dr() const;

  ///
  /// Dimension of the range (auto-access version).
  ///
  int dr(bool xauto_access) const;

  ///
  /// The path of the range vector space.
  ///
  poset_path range_path() const;

  ///
  /// The path of the range vector space.
  ///
  poset_path range_path(bool xauto_access) const;

protected:

  ///
  /// Default constructor;
  /// creates a new sec_jcb_space handle not attached to any state.
  ///
  sec_jcb_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  sec_jcb_space(const sec_jcb_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~sec_jcb_space();

  ///
  /// Covariant constructor
  ///
  sec_jcb_space(sec_jcb* xtop, sec_jcb* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  sec_jcb_space(namespace_poset& xhost,
		const string& xname,
		const arg_list& xargs,
		const poset_path& xschema_path,
		bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the sec_jcb_space with
  /// index xindex in namespace xhost.
  ///
  sec_jcb_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_jcb_space with
  /// index xindex in namespace xhost.
  ///
  sec_jcb_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_jcb_space with
  /// name xname in namespace xhost.
  ///
  sec_jcb_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_jcb_space associated
  /// with namespace member xmbr.
  ///
  sec_jcb_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name SEC_VD_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_REP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Initializes xarg to satisfy class invariants.
  ///
  virtual void initialize_arg_list(const namespace_poset& xns, 
				   const string& xname,
				   arg_list& xargs,
				   const poset_path& xschema_path,
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
  sec_jcb_space& operator=(const poset_state_handle& xother);

protected:

private:

  //@}

 
  // ===========================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

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
  virtual sec_jcb_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // SEC_JCB_SPACE_H
