
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
/// Interface for class poset_member.

#ifndef COM_LIMITPOINT_SHEAF_POSET_MEMBER_H
#define COM_LIMITPOINT_SHEAF_POSET_MEMBER_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_PARTIAL_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/partial_poset_member.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_SCHEMA_POSET_MEMBER_H
#include "ComLimitPoint/sheaf/schema_poset_member.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf 
{

class poset_dof_map;
class poset_member_dof_iterator;
class poset_member_iterator;
class storage_agent;
class subposet;

///
/// A client handle for a restrictable member of a poset. <br>
/// <br>
/// A poset_member is a poset_member
/// which can be restricted to a subset of the host row schema.
///
class SHEAF_DLL_SPEC poset_member : public partial_poset_member
{
  // ===========================================================
  /// @name POSET_MEMBER
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached poset_member handle.
  ///
  poset_member();

  ///
  /// Copy constructor; creates a new poset_member handle.
  /// If xnew_jem is false the handle is attached to the same state as xother.
  /// If xnew_jem is true, the handle is attached to a new state which is a copy
  /// (i.e. is join equivalent to) the state of xother.
  ///
  explicit poset_member(const abstract_poset_member& xother, bool xnew_jem = false);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual poset_member& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(xother).
  ///
  poset_member& operator=(const poset_member& xother);

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~poset_member();

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline poset_member* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<poset_member*>(partial_poset_member::clone(xnew_state, xauto_access));
  }

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new jim (join-irreducible member) attached to a new member
  /// state in xhost. ("explicit"  prevents interpretation as implicit
  /// conversion from poset_state_handle* to poset_member&)
  ///
  explicit poset_member(poset_state_handle* xhost,
                        poset_dof_map* xdof_map = 0,
                        bool xcopy_dof_map = false,
                        bool xauto_access = true);

  // poset_member(poset_state_handle* xhost, block@<int@>* xexpansion);

  ///
  /// Creates a new jrm (join reducible member) attached to a new member state
  /// in xhost.  The jrm created is the join of the members with the indices
  /// given in xexpansion.
  ///
  poset_member(poset_state_handle* xhost,
               const scoped_index* xexpansion,
               int xexpansion_ct,
               const tern& xnew_jem,
               bool xauto_access);


  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new poset_member handle attached to the member state with
  /// hub id xhub_id in xhost
  ///
  poset_member(const poset_state_handle* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new poset_member handle attached to the member state with
  /// id xid in xhost
  ///
  poset_member(const poset_state_handle* xhost, const scoped_index& xid);

  ///
  /// Creates a new poset_member handle attached to the member state with name
  /// xname in xhost
  ///
  poset_member(const poset_state_handle* xhost, const std::string& xname);

  ///
  /// Creates a new poset_member handle attached to the member state with
  /// path xpath  in the namespace xnamespace.
  ///
  poset_member(const namespace_poset* xnamespace,
               const poset_path& xpath,
               bool xauto_access = true);

protected:

private:

  //@}


  // ===========================================================
  /// @name RESTRICTION FACET
  // ===========================================================
  //@{

public:

  // Member functions in restriction facet redefined only
  // to change access status from protected to public.

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
  inline poset_member* greatest_jem() const
  {
    return static_cast<poset_member*>(abstract_poset_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline poset_member* least_jem() const
  {
    return static_cast<poset_member*>(abstract_poset_member::least_jem());
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
  /// poset join of this with other, auto-allocated <br>
  /// the poset join is the least upper bound in the poset
  ///
  inline poset_member* p_join(poset_member* other) const
  {
    return static_cast<poset_member*>(abstract_poset_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-allocated <br>
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline poset_member* p_meet(poset_member* other)
  {
    return static_cast<poset_member*>(abstract_poset_member::p_meet(other));
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
  /// lattice join of this with other, auto-allocated <br>
  /// the lattice join is the least upper bound in the lattice generated by
  /// the jims in the poset
  ///
  inline poset_member* l_join(poset_member* other, bool xnew_jem = true)
  {
    return static_cast<poset_member*>(abstract_poset_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-allocated <br>
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline poset_member* l_meet(poset_member* other, bool xnew_jem = true)
  {
    return static_cast<poset_member*>(abstract_poset_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-allocated <br>
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline poset_member* l_not(bool xnew_jem = true) const
  {
    return static_cast<poset_member*>(abstract_poset_member::l_not(xnew_jem));
  };

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
  virtual poset_member* clone() const;  

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};


// ===========================================================
// NONMEMBER FUNCTIONS
// ===========================================================

} // namespace sheaf

#endif // COM_LIMITPOINT_SHEAF_POSET_MEMBER_H
