
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

// Interface for class tuple_space.

#ifndef TUPLE_SPACE_H
#define TUPLE_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef TUPLE_TABLE_DOFS_TYPE_H
#include "tuple_table_dofs_type.h"
#endif
 

namespace sheaf
{
  class namespace_poset;
}

namespace fiber_bundle
{

  using namespace sheaf;  

  class fiber_bundles_namespace;
  class tuple;
  
///
/// A Cartesian product space.
///
class SHEAF_DLL_SPEC tuple_space : public poset
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name TUPLE_SPACE FACET
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
  typedef tuple member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const std::string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef tuple_table_dofs_type table_dofs_type;

  ///
  /// Creates a new tuple_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute 
  /// factor_ct specified by xfactor_ct.
  ///
  static tuple_space& new_table(namespace_type& xhost, 
				const poset_path& xpath, 
				const poset_path& xschema_path,
				int xfactor_ct,
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
  /// creates a new tuple_space handle not attached to any state.
  ///
  tuple_space();

  ///
  /// Copy constructor; disabled.
  ///
  tuple_space(const tuple_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~tuple_space();

  ///
  /// Covariant constructor
  ///
  tuple_space(tuple* xtop, tuple* xbottom);

private:

  //@}

  // ===========================================================
  /// @name POSET FACET
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
  tuple_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<tuple_space&>(*this);
  };

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
  virtual tuple_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // TUPLE_SPACE_H
