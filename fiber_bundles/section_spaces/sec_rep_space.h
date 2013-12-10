
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
/// Interface for class sec_rep_space.

#ifndef SEC_REP_SPACE_H
#define SEC_REP_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef MUTABLE_INDEX_SPACE_HANDLE_H
#include "mutable_index_space_handle.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_MEMBER_H
#include "section_space_schema_member.h"
#endif

namespace sheaf
{
  class abstract_poset_member;
  class namespace_poset;  
  class poset_member;
}

namespace fiber_bundle
{

using namespace sheaf;

class binary_section_space_schema_member;
class sec_rep_descriptor;
class sec_rep_space_member;
class section_dof_map;

///
/// A handle for a poset whose members are
/// numerical representations of sections of a fiber bundle.
///
class SHEAF_DLL_SPEC sec_rep_space : public poset_state_handle
{
  friend class sheaf::namespace_poset; // Qualification needed by g++ 4.2.2
  friend class fiber_bundles_namespace;
  
  // ===========================================================
  /// @name SEC_REP_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// The base space for this section space (mutable version)
  ///
  abstract_poset_member& base();

  ///
  /// The base space for this section space (const version)
  ///
  const abstract_poset_member& base() const;

  ///
  /// The dimension of the base space
  ///
  int db() const;

  ///
  /// The dimension of the fiber space
  ///
  int df() const;

  ///
  /// The schema of the fiber space, i.e. fiber().schema() (mutable version).
  ///
  schema_poset_member& fiber_schema();

  ///
  /// The schema of the fiber space, i.e. fiber().schema() (const version).
  ///
  const schema_poset_member& fiber_schema() const;

  ///
  /// The schema of the fiber space, i.e. fiber(xauto_access).schema() (mutable version).
  ///
  schema_poset_member& fiber_schema(bool xauto_access);

  ///
  /// The schema of the fiber space, i.e. fiber(xauto_access).schema() (const version).
  ///
  const schema_poset_member& fiber_schema(bool xauto_access) const;

  ///
  /// The subposet on which the degrees of freedom are defined (mutable version).
  ///
  subposet& discretization();

  ///
  /// The subposet on which the degrees of freedom are defined (const version).
  ///
  const subposet& discretization() const;

  ///
  /// The number of members of the intersection of discretization with the
  /// down set of base.
  ///
  int discretization_ct() const;

  ///
  /// The number of degrees of freedom associated with each
  /// member of the discretization.
  ///
  int multiplicity() const;

  ///
  /// The subposet on which the evaluation method is defined (mutable version).
  ///
  subposet& evaluation();

  ///
  /// The subposet on which the evaluation method is defined (const version).
  ///
  const subposet& evaluation() const;

  ///
  /// The name of the evaluator family used by this section space.
  ///
  std::string evaluator_family() const;

  ///
  /// The url for a description of the representation
  ///
  std::string url() const;

  ///
  /// A representation descriptor for this sec rep space (mutable version).
  ///
  sec_rep_descriptor& rep();

  ///
  /// A representation descriptor for this sec rep space (const version).
  ///
  const sec_rep_descriptor& rep() const;

  ///
  /// True if xrep is a valid rep descriptor for sec rep spaces over xbase,
  ///
  static bool rep_is_valid(const abstract_poset_member* xbase, const sec_rep_descriptor* xrep);

protected:

  ///
  /// Default constructor; creates an unattached handle.
  ///
  sec_rep_space();

  ///
  /// Copy constructor; disabled.
  ///
  sec_rep_space(const sec_rep_space& xother) { };

  ///
  /// Covariant constructor
  ///
  sec_rep_space(sec_rep_space_member* xtop, sec_rep_space_member* xbottom);

  ///
  /// Assignment operator; disabled.
  ///
  sec_rep_space& operator=(const sec_rep_space& xother)
  {
    return const_cast<sec_rep_space&>(*this);
  };

  ///
  /// Destructor.
  ///
  virtual ~sec_rep_space();

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name MULTISECTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if the section with hub id xhub_id is a multisection.
  ///
  bool is_multisection(pod_index_type xhub_id, bool xauto_access) const;

  ///
  /// True if the section with id xid is a multisection.
  ///
  bool is_multisection(const scoped_index& xid, bool xauto_access) const;

  ///
  /// The name of the sequence id space for the branches of the
  /// multisection with hub id xhub_id.
  ///
  std::string branch_id_space_name(pod_index_type xhub_id, bool xauto_access) const;

  ///
  /// The name of the sequence id space for the branches of the
  /// multisection with id xid.
  ///
  std::string branch_id_space_name(const scoped_index& xid, bool xauto_access) const;

  ///
  /// The sequence id space for multisections (const version).
  ///
  const mutable_index_space_handle& multisection_id_space(bool xauto_access) const;

  ///
  /// The sequence id space for multisections (mutable version).
  ///
   mutable_index_space_handle& multisection_id_space(bool xauto_access);

  ///
  /// Allocate an id space handle from the handle pool attached to the
  /// branch id space of the multisection with hub id xhub_id.
  ///
  mutable_index_space_handle& get_branch_id_space(pod_index_type xhub_id, bool xauto_access);

  ///
  /// Allocate an id space handle from the handle pool attached to the
  /// branch id space of the multisection with id xid.
  ///
  mutable_index_space_handle& get_branch_id_space(const scoped_index& xid, bool xauto_access);

  ///
  /// Returns the id space handle xid_space to the handle pool.
  ///
  void release_branch_id_space(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// True if the handle pool allocated xid_space.
  ///
  bool allocated_branch_handle(index_space_handle& xid_space, bool xauto_access) const;

  ///
  /// Allocate an id space iterator from the iterator pool attached to the
  /// branch id space of the multisection with hub id xhub_id.
  ///
  index_space_iterator& get_branch_id_space_iterator(pod_index_type xhub_id, bool xauto_access) const;

  ///
  /// Allocate an id space iterator from the iterator pool attached to the
  /// branch id space of the multisection with id xid.
  ///
  index_space_iterator& get_branch_id_space_iterator(const scoped_index& xid, bool xauto_access) const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  void release_branch_id_space_iterator(index_space_iterator& xitr, bool xauto_access) const;

  ///
  /// True if the iterator pool allocated xitr.
  ///
  bool allocated_branch_iterator(index_space_iterator& xitr, bool xauto_access) const;

protected:

  ///
  /// The sequence id space for multisections.
  ///
  mutable mutable_index_space_handle _multisection_id_space;

private:

  //@}


  // ===========================================================
  /// @name STATE FACET
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
  /// allow editing of jims and jim order relation
  ///
  virtual void begin_jim_edit_mode(bool xauto_access = true);

  ///
  /// prevent editing of jims and jim order relation
  ///
  virtual void end_jim_edit_mode(bool xensure_lattice_invariant = true,
                                 bool xauto_access = true);

protected:

  using poset_state_handle::new_state;

  ///
  /// Creates a new poset state with path xpath, schema xschema and table dof map xdof_map,
  /// attaches this to the state.
  ///
  virtual void new_state(const poset_path& xpath, const schema_poset_member& xschema, array_poset_dof_map& xdof_map);

private:

  //@}
 

  // ===========================================================
  /// @name MEMBERSHIP FACET
  // ===========================================================
  //@{

public:

  ///
  /// The top of member of the lattice (mutable version)
  ///
  sec_rep_space_member& top();

  ///
  /// The top of member of the lattice (const version)
  ///
  const sec_rep_space_member& top() const;

  ///
  /// The bottom of member of the lattice (mutable version)
  ///
  sec_rep_space_member& bottom();

  ///
  /// The bottom of member of the lattice (const version)
  ///
  const sec_rep_space_member& bottom() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name SCHEMA FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of schema member for this class.
  ///
  typedef binary_section_space_schema_member schema_type;

  ///
  /// The schema for this poset (mutable version)
  ///
  virtual section_space_schema_member& schema();

  ///
  /// The schema for this poset (const version)
  ///
  virtual const section_space_schema_member& schema() const;

  ///
  /// The schema for this poset, auto_accessible (mutable version).
  ///
  section_space_schema_member& schema(bool xauto_access);

  ///
  /// The schema for this poset, auto_accessible (const version).
  ///
  const section_space_schema_member& schema(bool xauto_access) const;

  ///
  /// True if xother_schema conforms to the type of schema required by this.
  ///
  virtual bool schema_is_ancestor_of(const schema_poset_member* xother_schema) const;

  ///
  /// The number of dofs in the table/row dof tuple of this sec_rep_space;
  ///
  virtual int dof_ct(bool xis_table_dof) const;

  ///
  /// True if xdof_map conforms to (i.e. is derived from) the type of
  /// row_dof map required by this poset
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

  ///
  /// The size in bytes of the table/row dof tuple.
  ///
  virtual size_t dof_tuple_ub(bool xis_table_dof) const;

  ///
  /// Creates a new row dof map for total sections of this.
  ///
  virtual const scoped_index& new_row_dof_map();

  ///
  /// Creates a new row dof map for partial sections of this,
  /// defined only on version xbase_version of the base space member
  /// with index xbase_id.
  ///
  virtual const scoped_index& new_row_dof_map(pod_index_type xbase_id,
					      int xbase_version);

  ///
  /// Creates a new row dof map for partial sections of this,
  /// defined only on version xbase_version of the base space member
  /// with index xbase_id.
  ///
  const scoped_index& new_row_dof_map(const scoped_index& xbase_id,
				      int xbase_version);

  ///
  /// The dof map associated with the member identified by xmbr_id (mutable version).
  ///
  section_dof_map& member_dof_map(pod_index_type xmbr_index,
                                  bool xrequire_write_access = false);

  ///
  /// The dof map associated with the member identified by xmbr_id (mutable version).
  ///
  section_dof_map& member_dof_map(const scoped_index& xmbr_index,
                                  bool xrequire_write_access = false);

  ///
  /// The dof map associated with the member identified by xmbr_id (const version).
  ///
  const	section_dof_map& member_dof_map(pod_index_type xmbr_index,
					bool xrequire_write_access = false) const;

  ///
  /// The dof map associated with the member identified by xmbr_id (const version).
  ///
  const	section_dof_map& member_dof_map(const scoped_index& xmbr_index,
					bool xrequire_write_access = false) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Virtual constructor.
  ///
  virtual sec_rep_space* clone() const;

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}

};

} // namespace fiber_bundle

#endif // ifndef SEC_REP_SPACE_H
