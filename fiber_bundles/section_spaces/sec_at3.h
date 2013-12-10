
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
/// Interface for class sec_at3.

#ifndef SEC_AT3_H
#define SEC_AT3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_ATP_H
#include "sec_atp.h"
#endif

#ifndef AT3_H
#include "at3.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_AT3
//==============================================================================

///
/// A section of a bundle with fiber type at3.
///
class SHEAF_DLL_SPEC sec_at3 : public sec_atp
{

  // ===========================================================
  /// @name HOST_FACTORY FACET OF CLASS SEC_AT3
  // ===========================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef at3 fiber_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xscalar_space_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name AT3 FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_at3();

  ///
  /// Creates a new sec_at3 handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_at3(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_at3 handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_at3(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_at3 handle attached to the member state with name
  /// xname in xhost.
  ///
  sec_at3(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_at3(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_at3 handle attached to the same state as xother.
  ///
  explicit sec_at3(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_at3(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_at3(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_at3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_at3& operator=(const sec_at3& xother);

  ///
  /// Assignment operator.
  ///
  sec_at3& operator=(const at3& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_at3& operator=(const at3_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_at3();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name SEC_REP_SPACE_MEMBER FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual sec_at3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_at3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_at3*>(sec_atp::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_AT3
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// true if other conforms to current
  ///
  bool is_ancestor_of(const any* other) const;

  ///
  /// class invariant
  ///
  bool invariant() const;

protected:

private:

  //@}


//##############################################################################

public:

  ///
  /// component indexed by row and col
  ///
//   virtual scalar_type* comp2(int row, int col);

  ///
  /// Returns index into linear storage of the component
  /// in a specified row and column
  ///
//   int index_for_row_column(int row, int column);

  ///
  /// set component indexed by row and col
  ///
//   virtual void set_comp2(int row, int col, scalar_type* new_comp);

};

} // namespace fiber_bundle

#endif // ifndef SEC_AT3_H

