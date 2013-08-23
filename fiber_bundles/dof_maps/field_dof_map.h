
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

// $$SCRIBBLE: remove this class from build.

// Interface for class field_dof_map;
// A specialized section_dof_map that knows
// the dofs are all type double

#ifndef FIELD_DOF_MAP_H
#define FIELD_DOF_MAP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_DOF_MAP_H
#include "section_dof_map.h"
#endif

namespace sheaf
{
class poset_state_handle;
}

namespace fiber_bundle
{

///
/// OBSOLETE: Use array_sec_vd_dof_map or sparse_section_dof_map.
/// The abstract map from section_space_schema_member ids
/// to section dof values of homogeneous type double.
///
class SHEAF_DLL_SPEC field_dof_map : public section_dof_map
{
  friend class sec_rep_space_member;

public:

  ///
  /// The name of the actual (possibly derived) class of this instance.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  // CANONICAL MEMBERS

  ///
  /// Assignment operator
  ///
  field_dof_map& operator=(const field_dof_map& xother);

  ///
  /// Destructor
  ///
  virtual ~field_dof_map();

  ///
  /// The class invariant.
  ///
  virtual bool invariant() const;

  // MAP INTERFACE

  using section_dof_map::get_dofs;
  using section_dof_map::put_dofs;

  /// @hack Following 2 redefinitions provided only to silence warnings
  /// about hiding virtual function.
  /// @todo implement product posets so inheritance is correct.

  virtual void get_dofs(const client_index* xclient_ids, int xclient_id_ct,
                        void* xbuf, size_t xbuf_len) const
  {
    not_implemented();
  };

  virtual void put_dofs(const client_index* xclient_ids, int xclient_id_ct,
                        const void* xbuf, size_t xbuf_len)
  {
    not_implemented();
  };

   ///
  /// Double version of get_dofs
  ///
  inline void get_dofs(const client_index* xclient_base_ids,  int xclient_base_id_ct,
                       const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
                       double* xbuf, int xbuf_len) const
  {
    get_dofs(xclient_base_ids, xclient_base_id_ct,
             xclient_fiber_ids, xclient_fiber_id_ct,
             static_cast<void*>(xbuf), xbuf_len*sizeof(double));
  };

  ///
  /// Double version of put_dofs.
  ///
  inline void put_dofs(const client_index* xclient_base_ids,  int xclient_base_id_ct,
                       const client_index* xclient_fiber_ids, int xclient_fiber_id_ct,
                       const double* xbuf, int xbuf_len)
  {
    put_dofs(xclient_base_ids, xclient_base_id_ct,
             xclient_fiber_ids, xclient_fiber_id_ct,
             static_cast<const void*>(xbuf), xbuf_len*sizeof(double));
  };


protected:

  ///
  /// Default constructor
  ///
  field_dof_map();

  ///
  /// Copy constructor
  ///
  field_dof_map(const field_dof_map& xother);

  ///
  /// Creates a  map for the poset dofs of xhost
  ///
  field_dof_map(const sec_rep_space* xhost);

};

} // namespace fiber_bundle

#endif // ifndef FIELD_DOF_MAP_H
