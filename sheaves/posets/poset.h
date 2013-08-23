
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
/// Interface for class poset.

#ifndef POSET_H
#define POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

namespace sheaf
{

class arg_list;
class namespace_poset; 

///
/// A client handle for a mutable partially ordered set.
///
class SHEAF_DLL_SPEC poset : public poset_state_handle
{

  friend class abstract_poset_member;
  friend class namespace_poset;
  friend class poset_component;
  friend class poset_orderer;
  friend class poset_traverser;
  friend class storage_agent;

  // ===========================================================
  /// @name POSET FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor; creates a new poset handle not attached to any state.
  ///
  poset();

  ///
  /// Destructor
  ///
  virtual ~poset();

  ///
  /// Covariant constructor
  ///
  poset(abstract_poset_member* xtop, abstract_poset_member* xbottom);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs not initialized.
  ///
  poset(namespace_poset* xhost,
        const poset_path& xschema_path,
        const string& xname,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xtable_dofs.
  ///
  poset(namespace_poset* xhost,
        const poset_path& xschema_path,
        const string& xname,
        void* xtable_dofs,
        size_t xtable_dofs_ub,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  poset(namespace_poset* xhost,
        const poset_path& xschema_path,
        const string& xname,
        arg_list& xargs,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dof map xdof_tuple.
  ///
  poset(namespace_poset* xhost,
        const poset_path& xschema_path,
        const string& xname,
        array_poset_dof_map* xdof_tuple,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema xschema, name xname, and uninitialized table dofs.
  ///
  poset(namespace_poset* xname_space,
        abstract_poset_member* xschema,
        const string& xname,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema xschema, name xname, and table dofs initialized by xtable_dofs.
  ///
  poset(namespace_poset* xname_space,
        abstract_poset_member* xschema,
        const string& xname,
        void* xtable_dofs,
        size_t xtable_dofs_ub,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema xschema, name xname, and table dofs initialized by xargs.
  ///
  poset(namespace_poset* xname_space,
        abstract_poset_member* xschema,
        const string& xname,
        arg_list& xargs,
        bool xauto_access = true);

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema  xschema, name xname, and table dof map xdof_tuple.
  ///
  poset(namespace_poset* xhost,
        abstract_poset_member* xschema,
        const string& xname,
        array_poset_dof_map* xdof_tuple,
        bool xauto_access = true);

  ///
  /// Creates a new handle attached to the poset with
  /// index xindex in namespace xhost.
  ///
  poset(const namespace_poset* xhost, pod_index_type xindex);

  ///
  /// Creates a new handle attached to the poset with
  /// index xindex in namespace xhost.
  ///
  poset(const namespace_poset* xhost, const scoped_index& xindex);

  ///
  /// Creates a new handle attached to the poset with
  /// name xname in namespace xhost.
  ///
  poset(const namespace_poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the poset associated
  /// with namespace member xmbr
  ///
  poset(const abstract_poset_member* xmbr);

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  poset(const poset& xother);

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  poset& operator=(const poset_state_handle& xother);

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs not initialized.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xtable_dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 void* xtable_dofs,
                 size_t xtable_dofs_ub,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 arg_list& xargs,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state with schema given by
  /// the member specified by path xschema_path in namespace xhost,
  /// and with name xname, and table dofs xdof_tuple.
  ///
  ///
  void new_state(namespace_poset* xhost,
                 const poset_path& xschema_path,
                 const string& xname,
                 array_poset_dof_map* xdof_tuple,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and uninitialized table dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const abstract_poset_member* xschema,
                 const string& xname,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and table dofs initialized by xtable_dofs.
  ///
  void new_state(namespace_poset* xhost,
                 const abstract_poset_member* xschema,
                 const string& xname,
                 void* xtable_dofs,
                 size_t xtable_dofs_ub,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state in namespace xhost,
  /// schema xschema,  name xname, and table dofs initialized by xargs.
  ///
  void new_state(namespace_poset* xhost,
                 const abstract_poset_member* xschema,
                 const string& xname,
                 arg_list& xargs,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new poset state with schema xschema,
  /// name xname and table dofs xdof_tuple
  ///
  ///
  virtual void new_state(namespace_poset* xhost,
			 const abstract_poset_member* xschema,
			 const string& xname,
			 array_poset_dof_map* xdof_tuple,
			 bool xauto_access = true);

private:

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
  /// Allow editing of jims and jim order relation.
  ///
  virtual void begin_jim_edit_mode(bool xauto_access = true);

  ///
  /// Prevent editing of jims and jim order relation.
  ///
  virtual void end_jim_edit_mode(bool xensure_lattice_invariant = true,
                                 bool xauto_access = true);

protected:

  // The using declaration is placed here as opposed to being at the beginning
  // of the public "new_state" methods because putting it in the public section
  // makes the following new_state method public also.

  using poset_state_handle::new_state;

  ///
  /// Attaches this external poset to a new poset state with schema
  /// given by xschema and table dofs by xdof_map.
  /// Intended for use by i/o subsystem.
  ///
  virtual void new_state(const schema_poset_member& xschema,
                         array_poset_dof_map& xdof_map);

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
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual poset* clone() const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

} // namespace sheaf

#endif // POSET_H

