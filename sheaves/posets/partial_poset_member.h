
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
/// Interface for class partial_poset_member.

#ifndef PARTIAL_POSET_MEMBER_H
#define PARTIAL_POSET_MEMBER_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ABSTRACT_POSET_MEMBER_H
#include "abstract_poset_member.h"
#endif

#ifndef SCHEMA_POSET_MEMBER_H
#include "schema_poset_member.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{

class subposet;
class poset_dof_map;
class poset_member_dof_iterator;
class poset_member_iterator;
class storage_agent;
  
///
/// A client handle for a possibly restricted member of a poset. <br>
/// <br>
/// A partial_poset_member is a poset_member
/// which may be restricted to a subset of the host row schema,
/// but does not export the interface for changing the restriction.
////
class SHEAF_DLL_SPEC partial_poset_member : public abstract_poset_member
{
  // ===========================================================
  /// @name PARTIAL_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached partial_poset_member
  /// handle
  ///
  partial_poset_member();

  ///
  /// Copy constructor; creates a new partial_poset_member handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit partial_poset_member(const abstract_poset_member& xother, bool xnew_jem = false);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual partial_poset_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  partial_poset_member& operator=(const partial_poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~partial_poset_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline partial_poset_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new jim (join-irreducible member) attached to a new member
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset_state_handle* to partial_poset_member&)
  ///
  explicit partial_poset_member(poset_state_handle* xhost,
                                poset_dof_map* xdof_map = 0,
                                bool xcopy_dof_map = false,
                                bool xauto_access = true);

  // partial_poset_member(poset_state_handle* xhost, block@<int@>* xexpansion);

  ///
  /// creates a new jrm (join reducible member) attached to a new member state
  /// in xhost The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  partial_poset_member(poset_state_handle* xhost,
                       const scoped_index* xexpansion,
                       int xexpansion_ct,
                       const tern& xnew_jem,
                       bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new partial_poset_member handle attached to the member state
  /// with hub id xhub_id in xhost
  ///
  partial_poset_member(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new partial_poset_member handle attached to the member state
  /// with id xid in xhost
  ///
  partial_poset_member(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new partial_poset_member handle attached to the member state
  /// with name xname in xhost
  ///
  partial_poset_member(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new partial_poset_member handle attached to the member state
  /// with path xpoath in the namespace xnamespace.
  ///
  partial_poset_member(const namespace_poset* xnamespace,
                       const poset_path& xpath,
                       bool xauto_access = true);

  ///
  /// Covariant constructor
  ///
  partial_poset_member(schema_poset_member* xschema);

protected:

  ///
  /// Initializes handle data members when attaching
  /// to a different member in a different host;
  /// intended to be redefined in derived classes.
  ///
  virtual void init_handle_data_members();

  ///
  /// Initializes _schema; intended to be redefined in
  /// derived classes to initialize derived data members.
  ///
  virtual void attach_handle_data_members();

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  using abstract_poset_member::schema;

  ///
  /// The restricted schema for this poset member (mutable version).
  ///
  virtual schema_poset_member& schema();

  ///
  /// The restricted schema for this poset member (const version).
  ///
  virtual const schema_poset_member& schema() const;

protected:

  ///
  /// The restricted schema of this member
  ///
  schema_poset_member* _schema;

private:

  //@}


  // ===========================================================
  /// @name RESTRICTION FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Restricts this handle to the down set of xschema
  ///
  virtual void restrict_to(const abstract_poset_member* xschema);

  ///
  /// Restricts this handle to the same restriction as xother.
  ///
  virtual void restrict_to_same(const abstract_poset_member* xother);

  ///
  /// Removes any restriction; schema to the schema of host.
  ///
  virtual void unrestrict();

private:

  //@}


  // ===========================================================
  /// @name DEGREE OF FREEDOM (DOF) TUPLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of dofs in restricted schema of this poset member.
  ///
  virtual int dof_ct() const;

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
  inline partial_poset_member* greatest_jem() const
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline partial_poset_member* least_jem() const
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::least_jem());
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
  inline partial_poset_member* p_join(partial_poset_member* other) const
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline partial_poset_member* p_meet(partial_poset_member* other)
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::p_meet(other));
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
  inline partial_poset_member* l_join(partial_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline partial_poset_member* l_meet(partial_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline partial_poset_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<partial_poset_member*>(abstract_poset_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Detach this handle from its state, if any.
  ///
  virtual void detach_from_state();


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
  virtual partial_poset_member* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

} // namespace sheaf
 
#endif // PARTIAL_POSET_MEMBER_H
