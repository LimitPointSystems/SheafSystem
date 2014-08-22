
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
/// Interface for class sec_tuple_space.

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_TUPLE_SPACE_H
#define COM_LIMITPOINT_FIBER_BUNDLE_SEC_TUPLE_SPACE_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_REP_SPACE_H
#include "ComLimitPoint/fiber_bundle/sec_rep_space.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_TUPLE_TABLE_DOFS_TYPE_H
#include "ComLimitPoint/fiber_bundle/tuple_table_dofs_type.h"
#endif

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{
using namespace sheaf;

class sec_tuple;
class tuple;
class fiber_bundles_namespace;
  

///
/// A Cartesian product section space.
///
class SHEAF_DLL_SPEC sec_tuple_space : public sec_rep_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_tuple member_type;

  ///
  /// The fiber type.
  ///
  typedef tuple fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_tuple scalar_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// True if and only if the schema of the fiber space of the section schema
  /// specified by xsection_schema_path conforms to the fiber schema specified by xfiber_schema_path.
  ///
  static bool fiber_schema_conforms(const namespace_poset& xns, 
                                    const poset_path& xsection_schema_path, 
                                    const poset_path& xfiber_schema_path, 
                                    bool xauto_access);

  ///
  /// True if and only if the fiber space of the section schema
  /// specified by xsection_schema_path conforms to type F.
  ///
  template <typename F>
  static bool fiber_space_conforms(const namespace_poset& xns, const poset_path& xsection_schema_path, bool xauto_access);
  
  ///
  /// Creates a new sec_tuple_space in namespace xns with path xpath
  /// and schema specified by xschema_path.
  ///
  static sec_tuple_space& new_table(namespace_type& xhost, 
                                    const poset_path& xpath, 
                                    const poset_path& xschema_path,
                                    bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  ///
  /// The number of factors in this product.
  ///
  int factor_ct() const;

  ///
  /// The number of factors in this product; auto access signature.
  ///
  int factor_ct(bool xauto_access) const;
  

protected:

  ///
  /// Default constructor;
  /// creates a new sec_tuple_space handle not attached to any state.
  ///
  sec_tuple_space();

  ///
  /// Copy constructor; disabled.
  ///
  sec_tuple_space(const sec_tuple_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~sec_tuple_space();

  ///
  /// Covariant constructor
  ///
  sec_tuple_space(sec_tuple* xtop, sec_tuple* xbottom);

private:

  //@}


  // ===========================================================
  /// @name SEC_REP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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

protected:

  ///
  /// Assignment operator; disabled.
  ///
  sec_tuple_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<sec_tuple_space&>(*this);
  };

private:

  //@}

 
  // ===========================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}
 
 
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual sec_tuple_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // COM_LIMITPOINT_FIBER_BUNDLE_SEC_TUPLE_SPACE_H
