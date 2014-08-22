
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

// Interface for class sec_rep_descriptor

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifdef STD_STRING_H
#include "std_string.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_TOTAL_POSET_MEMBER
#include "ComLimitPoint/sheaf/total_poset_member.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_ARRAY_POSET_DOF_MAP
#include "ComLimitPoint/sheaf/array_poset_dof_map.h"
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
class fiber_bundles_namespace;
class sec_rep_descriptor_poset;
class sec_rep_space;

///
/// A description for a section representation scheme.
///
class SHEAF_DLL_SPEC sec_rep_descriptor: public total_poset_member
{

  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset.
  ///
  typedef sec_rep_descriptor_poset host_type;

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// The standard path for host spaces for this class.
  ///
  static const poset_path& standard_host_path();

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute prototypes_path specified by xprototypes_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path,
                             const poset_path& xprototypes_path,
			     bool xauto_access);

  ///
  /// The host with path standard_host_path().
  /// Returns the host if it already exists, otherwise, creates it in namespace xns
  /// with schema specified by standard_schema_path() and standard paths for prerequisites,
  /// which are also created if needed.
  ///
  static host_type& standard_host(namespace_type& xns, bool xauto_access);

protected:

private:

  //@}

  // ===========================================================
  /// @name SEC_REP_DESCRIPTOR FACET
  // ===========================================================
  //@{

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
                     const std::string& xdiscretization_subposet_name,
                     const std::string& xmultivalued_subposet_name,
                     const std::string& xevaluation_subposet_name,
                     const std::string& xevaluation_method_name,
                     const std::string& xurl,
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
  sec_rep_descriptor(const poset *xhost, const std::string& xname);

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
                     const std::string& xdiscretization_subposet_name,
                     const std::string& xmultivalued_subposet_name,
                     const std::string& xevaluation_subposet_name,
                     const std::string& xevaluation_method_name,
                     const std::string& xurl,
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
  std::string discretization_subposet_name() const;

  ///
  /// Sets the name of the discretization subposet to xname.
  ///
  void put_discretization_subposet_name(const std::string& xname);

  ///
  /// The name of the multivalued subposet.
  ///
  std::string multivalued_subposet_name() const;

  ///
  /// Sets the name of the multivalued subposet to xname.
  ///
  void put_multivalued_subposet_name(const std::string& xname);

  ///
  /// The name of the evaluation subposet.
  ///
  std::string evaluation_subposet_name() const;

  ///
  /// Sets the name of the evaluation subposet to xname.
  ///
  void put_evaluation_subposet_name(const std::string& xname);

  ///
  /// The name of the evaluator family.
  ///
  std::string evaluator_family_name() const;

  ///
  /// Sets the name of the evaluator family to xname.
  ///
  void put_evaluator_family_name(const std::string& xname);

  ///
  /// The url for a description of this representation
  ///
  std::string url() const;

  ///
  /// Sets the url for a description of this representation to xurl.
  ///
  void put_url(const std::string& xurl);

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
    row_dof_tuple(const std::string& xdiscretization_subposet_name,
                  const std::string& xmultivalued_subposet_name,
                  const std::string& xevaluation_subposet_name,
                  const std::string& xevaluator_family_name,
                  const std::string& xurl,
                  int xmultiplicity,
                  size_type xeval_is_above_disc);

    ///
    /// Duplicates xodf_value.str() and makes xdof point to the copy.
    ///
    static void copy_string_dof(char*& xdof, const std::string& xdof_value);

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

  //@}

};

} // namespace fiber_bundle

#endif // ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_H






