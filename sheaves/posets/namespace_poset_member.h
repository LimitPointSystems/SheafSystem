

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

/// @file
/// Interface for class namespace_poset_member.

#ifndef NAMESPACE_POSET_MEMBER_H
#define NAMESPACE_POSET_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TOTAL_POSET_MEMBER_H
#include "total_poset_member.h"
#endif

#ifndef NAMESPACE_POSET_DOF_MAP_H
#include "namespace_poset_dof_map.h"
#endif

#ifndef POSET_TYPE_H
#include "poset_type.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class poset_state_handle;
class namespace_poset;
  
///
/// A client handle for a member of a namespace poset.
///
class SHEAF_DLL_SPEC namespace_poset_member : public total_poset_member
{

  friend class poset_state_handle;
  friend class namespace_poset;

  // ===========================================================
  /// @name NAMESPACE_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached namespace_poset_member handle.
  ///
  namespace_poset_member();

  ///
  /// Copy constructor; creates a new namespace_poset_member handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit namespace_poset_member(const namespace_poset_member& xother,
                                  bool xnew_jem = false);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual namespace_poset_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  namespace_poset_member& operator=(const namespace_poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~namespace_poset_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline namespace_poset_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<namespace_poset_member*>(total_poset_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// creates a new jrm (join reducible member) attached to a new member state
  /// in xhost.  The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  namespace_poset_member(namespace_poset* xhost,
                         const scoped_index* xexpansion,
                         int xexpansion_ct,
                         const tern& xnew_jem,
                         bool xauto_access);


  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new namespace_poset_member handle attached to the member state
  /// with hub id xhub_id in xhost
  ///
  namespace_poset_member(const namespace_poset* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new namespace_poset_member handle attached to the member state
  /// with id xid in xhost
  ///
  namespace_poset_member(const namespace_poset* xhost, const scoped_index& xid);

  ///
  /// Creates a new namespace_poset_member handle attached to the member state
  /// with name xname in xhost
  ///
  namespace_poset_member(const namespace_poset* xhost, const string& xname);

  ///
  /// Creates a new namespace_poset_member handle attached to the member state
  /// corresponding to xmember_poset
  ///
  namespace_poset_member(const poset_state_handle& xmember_poset);

  ///
  /// The pointer to the poset associated
  /// with this namespace member.
  ///
  poset_state_handle* poset_pointer() const;

  ///
  /// The type id of the poset associated
  /// with this namespace member.
  ///
  poset_type poset_type_id() const;

  ///
  /// The class of the poset associated
  /// with this namespace member.
  ///
  const char* poset_class() const;

  ///
  /// The id of the xi-th prerequisite poset
  /// for the poset associated with this namespace member.
  ///
  pod_index_type poset_prereq_id(int xi) const;

  ///
  /// True if the poset associated with this member is external.
  ///
  bool poset_is_external() const;

protected:

  ///
  /// Creates a new jim (join-irreducible member) attached to a new member
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset_state_handle* to namespace_poset_member&).
  /// Protected because jim creation must be controlled by poset creation.
  ///
  explicit namespace_poset_member(namespace_poset* xhost,
                                  namespace_poset_dof_map* xdof_map = 0,
                                  bool xcopy_dof_map = false,
                                  bool xauto_access = true);

  ///
  /// Set the pointer to the poset associated
  /// with this namespace member to xposet.
  ///
  void put_poset_pointer(const poset_state_handle* xposet);

  ///
  /// Set the type id of the poset associated
  /// with this namespace member to xtype_id.
  ///
  void put_poset_type_id(poset_type xtype_id);

  ///
  /// Set the class of the poset associated
  /// with this namespace member to xclass.
  ///
  void put_poset_class(const char* xclass);

  ///
  /// Sets the xi-th poset_prereq_ids to xid.
  ///
  void put_poset_prereq_id(int xi, pod_index_type xid);

  ///
  /// Sets the poset_pointer, poset_type_id, and poset_class
  /// to the corresponding values of xposet.
  ///*
  void put_poset(const poset_state_handle& xposet);

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public: 

  ///
  /// The map from client_ids to dof values for this poset member (mutable version)
  ///
  virtual namespace_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from client_ids to dof values for this poset member (const version)
  ///
  virtual const namespace_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (is derived from) the type of
  /// dof map required by this handle.
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public: 

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline namespace_poset_member* greatest_jem() const
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline namespace_poset_member* least_jem() const
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::least_jem());
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public: 

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline namespace_poset_member* p_join(abstract_poset_member* other) const
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline namespace_poset_member* p_meet(abstract_poset_member* other)
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::p_meet(other));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public: 

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline namespace_poset_member* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline namespace_poset_member* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline namespace_poset_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<namespace_poset_member*>(abstract_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name HOST POSET FACET
  // ===========================================================
  //@{

public: 

  ///
  /// The name space poset this is a member of
  ///
  namespace_poset* host() const;

  ///
  /// True if xother conforms to host
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* xther) const;

protected:

private:

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
  /// Make a new handle, no state instance of current
  ///
  virtual namespace_poset_member* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};
  
} // namespace sheaf

#endif // NAMESPACE_POSET_MEMBER_H
