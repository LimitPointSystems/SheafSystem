

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

// Interface for class sec_rep_descriptor

#ifndef SEC_REP_DESCRIPTOR_H
#define SEC_REP_DESCRIPTOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifdef STD_STRING_H
#include "std_string.h"
#endif

#ifndef TOTAL_POSET_MEMBER
#include "total_poset_member.h"
#endif

#ifndef ARRAY_POSET_DOF_MAP
#include "array_poset_dof_map.h"
#endif

namespace sheaf
{
class any;
class namespace_poset;
class poset;
class poset_state_handle;
}

namespace fiber_bundle
{

using namespace sheaf;
  
class eval_family;
class sec_rep_descriptor_poset;
class sec_rep_space;

///
/// A description for a section representation scheme.
///
class SHEAF_DLL_SPEC sec_rep_descriptor: public total_poset_member
{

public:

  ///
  /// Assignment operator
  ///
  virtual sec_rep_descriptor& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  sec_rep_descriptor& operator=(const sec_rep_descriptor& xother);

  // CANONICAL MEMBERS

  ///
  /// Default constructor
  ///
  ///
  sec_rep_descriptor();

  ///
  /// Copy constructor
  ///
  ///
  sec_rep_descriptor(const sec_rep_descriptor& xother, bool xnew_jem);

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual sec_rep_descriptor* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_rep_descriptor* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_rep_descriptor*>(total_poset_member::clone(xnew_state, xauto_access));
  }

  ///
  /// Destructor
  ///
  virtual ~sec_rep_descriptor();

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  ///
  sec_rep_descriptor(poset *xhost,
                     const string& xdiscretization_subposet_name,
                     const string& xmultivalued_subposet_name,
                     const string& xevaluation_subposet_name,
                     const string& xevaluation_method_name,
                     const string& xurl,
                     int xmultiplicity,
                     bool xeval_is_above_disc,
                     bool xauto_access);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to
  /// the member state with index xindex in xhost.
  ///
  sec_rep_descriptor(const poset *xhost, pod_index_type xindex);

  ///
  /// Creates a new handle attached to
  /// the member state with index xindex in xhost.
  ///
  sec_rep_descriptor(const poset *xhost, const scoped_index& xindex);

  ///
  /// Creates a new handle attached to
  /// the member state with name xname in xhost.
  ///
  sec_rep_descriptor(const poset *xhost, const string &xname);

  ///
  /// Creates a new sec_rep_descriptor handle attached to the member state
  /// specified by path xpath in namespace xns.
  ///
  sec_rep_descriptor(const namespace_poset* xns,
                     const poset_path& xpath,
                     bool xauto_access = true);

  ///
  /// Creates a new sec_rep_descriptor handle attached to the member state
  /// with index xmember_id in the poset with index xposet_id in the
  /// namespace xnamespace
  ///
  sec_rep_descriptor(const namespace_poset* xnamespace,
                     pod_index_type xposet_id,
                     pod_index_type xmember_id,
                     bool xauto_access = true);

  ///
  /// Creates a new sec_rep_descriptor handle attached to the member state
  /// with index xmember_id in the poset with index xposet_id in the
  /// namespace xnamespace
  ///
  sec_rep_descriptor(const namespace_poset* xnamespace,
                     const scoped_index& xposet_id,
                     const scoped_index& xmember_id,
                     bool xauto_access = true);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  using total_poset_member::new_jim_state;

  ///
  /// Creates a new jim (join-irreducible member) state in host() and attaches
  /// this to it. If xdof_map == 0 a new dof map is created. If xdof_map != 0
  /// and xcopy_dof_map == false, xdof_map is used as the dof map. If
  /// xdof_map != 0 and xcopy_dof_map is true, a copy of xdof_map is used.
  ///
  virtual void new_jim_state(poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true);

  ///
  /// Creates a new jim (join-irreducible member) state in xhost and attaches
  /// this to it.
  ///
  virtual void new_jim_state(poset_state_handle* xhost,
                             poset_dof_map* xdof_map = 0,
                             bool xcopy_dof_map = false,
                             bool xauto_access = true);


  ///
  /// Creates a new jim state in xhost and attaches this to it.
  ///
  void new_jim_state(poset *xhost,
                     const string& xdiscretization_subposet_name,
                     const string& xmultivalued_subposet_name,
                     const string& xevaluation_subposet_name,
                     const string& xevaluation_method_name,
                     const string& xurl,
                     int xmultiplicity,
                     bool xeval_is_above_disc,
                     bool xauto_access);

  // DEGREE OF FREEDOM (DOF) TUPLE INTERFACE

  ///
  /// The map from client_ids to dof values for this poset member (mutable version)
  ///
  virtual array_poset_dof_map& dof_map(bool xrequire_write_access = false);

  ///
  /// The map from client_ids to dof values for this poset member (const version)
  ///
  virtual const array_poset_dof_map& dof_map(bool xrequire_write_access = false) const;

  ///
  /// True if xdof_map conforms to (i.e. is derived from) the type of
  /// dof map required by this member
  ///
  virtual bool dof_map_is_ancestor_of(const poset_dof_map* xdof_map) const;

  // SEC_REP_DESCRIPTOR FACET

  ///
  /// The name of the discretization subposet.
  ///
  string discretization_subposet_name() const;

  ///
  /// Sets the name of the discretization subposet to xname.
  ///
  void put_discretization_subposet_name(const string& xname);

  ///
  /// The name of the multivalued subposet.
  ///
  string multivalued_subposet_name() const;

  ///
  /// Sets the name of the multivalued subposet to xname.
  ///
  void put_multivalued_subposet_name(const string& xname);

  ///
  /// The name of the evaluation subposet.
  ///
  string evaluation_subposet_name() const;

  ///
  /// Sets the name of the evaluation subposet to xname.
  ///
  void put_evaluation_subposet_name(const string& xname);

  ///
  /// The name of the evaluator family.
  ///
  string evaluator_family_name() const;

  ///
  /// Sets the name of the evaluator family to xname.
  ///
  void put_evaluator_family_name(const string& xname);

  ///
  /// The url for a description of this representation
  ///
  string url() const;

  ///
  /// Sets the url for a description of this representation to xurl.
  ///
  void put_url(const string& xurl);

  ///
  /// The number of degrees of freedom associated with each
  /// (discretization member, fiber_schema member) pair.
  ///
  int multiplicity() const;

  ///
  /// Sets the number of degrees of freedom associated with each
  /// (discretization member, fiber_schema member) pair.
  ///
  void put_multiplicity(int xmultiplicity);

  ///
  /// True is the evaluation subposet is strictly above
  /// the discretization subposet.
  ///
  bool eval_is_above_disc() const;

  ///
  /// Sets eval_is_above_disc to xvalue.
  ///
  void put_eval_is_above_disc(bool xvalue);

  ///
  /// The family of evaluators for this rep.
  //// @hack return type any because can't return type eval_family
  //// until we've finished refactoring sheaves and fiber_bundles.
  //// Client should down cast to eval_family*.
  //// @todo convert to eval_family when refactoring complete.
  ////
  eval_family* evaluators() const;

protected:

  ///
  /// Initializes handle data members when attaching
  /// to a different member of the same host.
  ///
  virtual void attach_handle_data_members();

private:
  ///
  /// Class represention of the row dofs
  ///
  class SHEAF_DLL_SPEC row_dof_tuple
  {
  public:

    ///
    /// The name of the discretization subposet
    ///
    char* discretization_subposet_name;

    ///
    /// The name of the multivalued subposet
    ///
    char* multivalued_subposet_name;

    ///
    /// The name of the evaluation subposet
    ///
    char* evaluation_subposet_name;

    ///
    /// The name of the evaluator family.
    ///
    char* evaluator_family_name;

    ///
    /// The url
    ///
    char* url;

    ///
    /// The multiplicity value
    ///
    int multiplicity;

    ///
    /// True if evaluation is above discretization.
    ///
    size_type eval_is_above_disc;

    ///
    /// Constructor
    ///
    row_dof_tuple(const string& xdiscretization_subposet_name,
                  const string& xmultivalued_subposet_name,
                  const string& xevaluation_subposet_name,
                  const string& xevaluator_family_name,
                  const string& xurl,
                  int xmultiplicity,
                  size_type xeval_is_above_disc);

    ///
    /// Duplicates xodf_value.str() and makes xdof point to the copy.
    ///
    static void copy_string_dof(char*& xdof, const string& xdof_value);

  };

  ///
  /// Pointer to the storage for the row dofs (const version).
  ///
  inline const row_dof_tuple* row_dof_tuple_ptr() const
  {
    return reinterpret_cast<const row_dof_tuple*>(dof_map(false).dof_tuple());
  };

  ///
  /// Pointer to the storage for the row dofs (mutable version).
  ///
  inline row_dof_tuple* row_dof_tuple_ptr()
  {
    return reinterpret_cast<row_dof_tuple*>(dof_map(true).dof_tuple());
  };

  ///
  /// The family of evaluators for this rep.
  ///
  eval_family* _evaluators;


};

} // namespace fiber_bundle

#endif // ifndef SEC_REP_DESCRIPTOR_H






