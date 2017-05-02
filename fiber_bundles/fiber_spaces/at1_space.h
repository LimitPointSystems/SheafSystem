
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

// Interface for class at1_space.

#ifndef AT1_SPACE_H
#define AT1_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef ATP_SPACE_H
#include "SheafSystem/atp_space.h"
#endif
  
namespace fiber_bundle
{

  using namespace sheaf;  

  class at1;
  
  
///
/// An abstract vector space viewed as an antisymmetric tensor space of degree 1.
///
class SHEAF_DLL_SPEC at1_space : public atp_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name AT1_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef at1 member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const std::string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates a new at1_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute 
  /// scalar_space_path specified by xscalar_space_path.
  ///
  static at1_space& new_table(namespace_type& xhost, 
			      const poset_path& xpath, 
			      const poset_path& xschema_path,
			      const poset_path& xscalar_space_path,
			      bool xauto_access);
  
protected:

  ///
  /// Default constructor;
  /// creates a new at1_space handle not attached to any state.
  ///
  at1_space();

  ///
  /// Copy constructor; disabled.
  ///
  at1_space(const at1_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~at1_space();

  ///
  /// Covariant constructor
  ///
  at1_space(at1* xtop, at1* xbottom);

private:

  //@}

  // ===========================================================
  /// @name TP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

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

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

  ///
  /// Assignment operator; disabled.
  ///
  at1_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<at1_space&>(*this);
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
  virtual at1_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // AT1_SPACE_H
