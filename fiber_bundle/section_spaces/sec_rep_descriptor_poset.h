
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
/// Interface for class sec_rep_descriptor_poset

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_POSET_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_POSET_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_POSET_H
#include "ComLimitPoint/sheaf/poset.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_TABLE_DOFS_TYPE_H
#include "ComLimitPoint/fiber_bundle/sec_rep_descriptor_table_dofs_type.h"
#endif

namespace sheaf
{
  class namespace_poset;
}

namespace fiber_bundle
{

using namespace sheaf;

class base_space_poset;
class sec_rep_descriptor;

///
/// The poset for sec_rep_descriptors.
///
class SHEAF_DLL_SPEC sec_rep_descriptor_poset : public poset
{
  friend class sheaf::namespace_poset; // Qualification needed by g++ 4.2.2
  friend class fiber_bundle_namespace;

  // ===========================================================
  /// @name SEC_REP_DESCRIPTOR_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this poset.
  ///
  typedef sec_rep_descriptor member_type;
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef sec_rep_descriptor_table_dofs_type table_dofs_type;

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates a new sec_rep_descriptor_poset in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute prototypes specified
  /// by xprototypes_path.
  ///
  static sec_rep_descriptor_poset& new_table(namespace_type& xhost, 
                                             const poset_path& xpath, 
                                             const poset_path& xschema_path,
                                             const poset_path& xprototypes_path,
                                             bool xauto_access);

  ///
  /// The base space members prototypes poset.
  ///
  const base_space_poset& prototypes() const;

  ///
  /// The base space members prototypes poset.
  ///
  base_space_poset& prototypes();

protected:

  ///
  /// Creates an unattached handle
  ///
  sec_rep_descriptor_poset();

  ///
  /// Destructor
  ///
  virtual ~sec_rep_descriptor_poset();

  ///
  /// Copy constructor; disabled.
  ///
  sec_rep_descriptor_poset(const sec_rep_descriptor& xother) { };

  ///
  /// Assignment operator; disabled.
  ///
  sec_rep_descriptor_poset& operator=(const poset_state_handle& xother)
  {
    return const_cast<sec_rep_descriptor_poset&>(*this);
  };

  ///
  /// Base space members prototypes poset.
  ///
  base_space_poset* _prototypes;  

  ///
  /// Creates prototype for this class and enters in in factory.
  ///
  static bool make_prototype();

private:

  //@}


  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

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
  /// Get read access to the state associated with this.
  ///
  virtual void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  virtual void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  virtual void release_access(bool xall = false) const;

protected:

  ///
  /// Initializes the handle data members that depend on the
  /// table dofs and are required to get access when this handle
  /// is used to create a new state. Intended to be called only
  /// from new_state.
  ///
  virtual void initialize_handle_data_members(const namespace_poset& xns);

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Release all access to posets this depends on,
  /// then detach and delete the state.
  ///
  virtual void terminate_access();

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual sec_rep_descriptor_poset* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

} // namespace fiber_bundle

#endif // COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_DESCRIPTOR_POSET_H
