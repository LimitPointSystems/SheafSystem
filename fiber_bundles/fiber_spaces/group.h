
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
/// Interface for abstract class group

#ifndef GROUP_H
#define GROUP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_LITE_H
#include "any_lite.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef PARTIAL_POSET_MEMBER_H
#include "partial_poset_member.h"
#endif

// #ifndef POSET_H
// #include "poset.h"
// #endif


namespace sheaf
{
  class poset;
}

namespace fiber_bundle
{
  using namespace sheaf;  

  class fiber_bundles_namespace;

//==============================================================================
// CLASS GROUP_LITE
//==============================================================================

///
/// The general, abstract mathematical group
/// (volatile version).
///
class SHEAF_DLL_SPEC group_lite : public any_lite
{
  //============================================================================
  /// @name GROUP FACET OF CLASS GROUP_LITE
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  group_lite();

  ///
  /// Copy constructor.
  ///
  group_lite(const group_lite& xother);

  ///
  /// Assignment operator.
  ///
  group_lite& operator=(const group_lite& xother);

  ///
  /// Destructor.
  ///
  virtual ~group_lite();

protected:
private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GROUP_LITE
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
  /// Virtual constructor, makes a new instance of the same type as this.
  ///
  virtual group_lite* clone() const;

protected:
private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS GROUP_LITE
  //============================================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any_lite& xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:
private:

  //@}
};

//==============================================================================
// CLASS GROUP
//==============================================================================

///
/// The general, abstract mathematical group
/// (persistent version)
///
class SHEAF_DLL_SPEC group : public total_poset_member
{

  //============================================================================
  /// @name FACTORY FACET OF CLASS GROUP
  //============================================================================
  //@{

public:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset.
  ///
  typedef poset host_type;

  ///
  /// The standard path with poset name suffix xsuffix for host spaces for type F.
  ///
  template <typename F>
  SHEAF_DLL_SPEC
  static poset_path standard_host_path(const std::string& xsuffix);

  ///
  /// True, if standard_host_path<F>(xsuffix) does not exist or is a path
  /// to a poset of type F::host_type.
  ///
  template <typename F>
  SHEAF_DLL_SPEC
  static bool standard_host_is_available(namespace_type& xns, const std::string& xsuffix, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name GROUP FACET OF CLASS GROUP
  //============================================================================
  //@{

public:

  ///
  /// The associated volatile type.
  ///
  typedef group_lite volatile_type;

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual group& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  group& operator=(const group& xother);

  ///
  /// Destructor.
  ///
  virtual ~group();

  ///
  /// The poset this is a member of.
  ///
  host_type* host() const;

protected:

  ///
  /// Default constructor.
  ///
  group();

private:


  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS GROUP
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const = 0;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();
  
  ///
  /// Make a new handle, no state instance of current
  ///
  virtual group* clone() const = 0;

  

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline group* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<group*>(total_poset_member::clone(xnew_state, xauto_access));
  }

protected:
private:

  //@}


  //===========================================================================
  /// @name ANY FACET OF CLASS GROUP
  //===========================================================================
  //@{

public:

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  ///
  /// Conformance test; true if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* other) const;

protected:
private:

  //@}
};

} // namespace fiber_bundle

#endif // ifndef GROUP_H






