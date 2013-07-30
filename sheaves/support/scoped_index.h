
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

/// @file
/// Interface for class scoped_index

#ifndef SCOPED_INDEX_H
#define SCOPED_INDEX_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ASSERT_CONTRACT_H
#include "assert_contract.h"
#endif

#ifndef ERROR_MESSAGE_H
#include "error_message.h"
#endif

#ifndef HUB_INDEX_SPACE_HANDLE_H
#include "hub_index_space_handle.h"
#endif

#ifndef INDEX_SPACE_FAMILY_H
#include "index_space_family.h"
#endif

#ifndef INDEX_TRAITS_H
#include "index_traits.h"
#endif

#ifndef NAMESPACE_SCHEMA_MEMBER_INDEX_H
#include "namespace_schema_member_index.h"
#endif

#ifndef NAMESPACE_MEMBER_INDEX_H
#include "namespace_member_index.h"
#endif

#ifndef PRIMITIVE_ATTRIBUTES_H
#include "primitive_attributes.h"
#endif

#ifndef PRIMITIVES_SCHEMA_MEMBER_INDEX_H
#include "primitives_schema_member_index.h"
#endif

#ifndef STANDARD_DOF_TUPLE_INDEX_H
#include "standard_dof_tuple_index.h"
#endif

#ifndef STANDARD_MEMBER_INDEX_H
#include "standard_member_index.h"
#endif

#ifndef STANDARD_SUBPOSET_INDEX_H
#include "standard_subposet_index.h"
#endif

#ifndef STANDARD_VERSION_INDEX_H
#include "standard_version_index.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

#ifndef STD_SET_H
#include "std_set.h"
#endif

#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#ifndef STD_LIMITS_H
#include "std_limits.h"
#endif

namespace sheaf
{

class poset_state_handle;   

///
/// An encapsulated hub pod_index; intended only for implementing
/// scoped_index "operators" ==~ and !=~; see 
/// bool scoped_index::operator==(scoped_index_hub_pod) and
/// scoped_index_interal_pod scoped_index::operator~(const scoped_index&).
///
struct SHEAF_DLL_SPEC scoped_index_hub_pod
{
  pod_index_type pod;
};
 

///
/// An index within the external ("client") scope of a given id space.
///
class SHEAF_DLL_SPEC scoped_index
{
  // ===========================================================
  /// @name SCOPED_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data" storage type for this.
  ///
  typedef pod_index_type pod_type;

  ///
  /// Default constructor; creates an invalid instance.
  ///
  scoped_index()
    : _id_spaces(0),
      _scope_id(invalid_pod()),
      _pod(invalid_pod())
  {
    // Preconditions:

    // Body:

    // Postconditions:

    ensure(invariant());
    ensure(!is_scoped());
    ensure(!is_valid());

    // Exit:

    return;
  };

  ///
  /// Creates an invalid instance in the scope of xid_space.
  ///
  scoped_index(const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(invalid_pod())
  {
    // Preconditions:

    require(xid_space.is_attached());

    // Body:

    // Postconditions:

    ensure(invariant());
    ensure(is_scoped());
    ensure(same_scope(xid_space));
    ensure(!is_valid());

    // Exit:

    return;
  };

  ///
  /// Creates an instance with pod() == xpod in the scope of xid_space.
  ///
  scoped_index(const index_space_handle& xid_space, pod_type xpod)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(xpod)
  {
    // Preconditions:

    require(xid_space.is_attached());

    // Body:

    // Postconditions:

    ensure(invariant());
    ensure(is_scoped());
    ensure(same_scope(xid_space));
    ensure(pod() == xpod);

    // Exit:

    return;
  };

  ///
  /// Creates an instance equivalent to xother in the scope of xid_space.
  ///
  scoped_index(const index_space_handle& xid_space, const scoped_index& xother)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(xid_space.pod(xother))
  {
    // Preconditions:

    require(xid_space.is_attached());
    require(xother.same_id_space_family(xid_space));

    // Body:

    // Postconditions:

    ensure(invariant());
    ensure(is_scoped());
    ensure(same_scope(xid_space));
    ensure( !is_valid() || (*this) ==~ xother);

    // Exit:

    return;
  };

  ///
  /// Copy constructor.
  ///
  scoped_index(const scoped_index& xother)
    : _id_spaces(0),
      _scope_id(invalid_pod())
  {
    // Preconditions:

    // Body:

    (*this) = xother;

    // Postconditions:

    ensure(invariant());
    ensure((*this).is_identical_to(xother));

    // Exit:

    return;
  };

  ///
  /// Creates an invalid instance in the id space 
  /// with name xname in poset xhost.
  ///
  scoped_index(const poset_state_handle& xhost, const string& xname);

  ///
  /// Creates an instance with pod xpod
  /// in the id space with name xname in poset xhost.
  ///
  scoped_index(pod_type xpod, const poset_state_handle& xhost, const string& xname);

  ///
  /// Creates an instance equivalent to xother
  /// in the id space with name xname in poset xhost.
  ///
  scoped_index(const scoped_index& xother, const poset_state_handle& xhost, const string& xname);

  ///
  /// Destructor.
  /// Not virtual; this can not be a base class.
  ///
  ~scoped_index()
  {
    // Preconditions:

    // Body:

    // Postconditions:

    // Exit:

    return;
  };

  ///
  /// Assignment operator.
  ///
  scoped_index& operator=(const scoped_index& xother)
  {
    // Preconditions:

    // Body:

    if(this != &xother)
    {
      if(xother._id_spaces != 0)
      {
	// xother is scoped, clone the scope.

	_id_spaces = xother._id_spaces;
	_scope_id = xother._scope_id;
      }
      else
      {
	// xother is not scoped.

	_id_spaces = 0;
	_scope_id = invalid_pod();
      }

      _pod = xother._pod;
    }

    // Postconditions:

    ensure(invariant());
    ensure((*this).is_identical_to(xother));

    // Exit:

    return *this;
  };

  ///
  /// Set the scope to id space, xid_space and pod() to xpod.
  ///
  void put(const index_space_handle& xid_space, pod_type xpod)
  {
    // Preconditions:

    require(xid_space.is_attached());

    // Body:

    _id_spaces = &xid_space.id_spaces();
    _scope_id = xid_space.index();
    _pod = xpod;

    // Postconditions:

    ensure(invariant());
    ensure(pod() == xpod);
    ensure(same_scope(xid_space));

    // Exit:

    return;
  };

  ///
  /// This mapped to the hub id space.
  ///
  scoped_index hub_id() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    scoped_index result(*this);
    result.hub_scope();

    // Postconditions:

    ensure(result.is_hub_scope());

    // Exit:

    return result;
  };

  ///
  /// Maps this to the hub id space.
  ///
  void hub_scope()
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    if(!is_hub_scope())
    {
      // Map the pod to the hub id space.

      _pod = _id_spaces->hub_pod(_scope_id, _pod);

       // Set the current scope to the hub id space.

      _scope_id = _id_spaces->hub_id_space().index();
    }
    else
    {
      // Already in the hub id space; do nothing.
    }

    // Postconditions:

    ensure(is_hub_scope());

    // Exit:

    return;
  };


  ///
  /// Class invariant.
  ///
  bool invariant() const
  {
    /// @todo implement invariant for scoped_index.

    return true;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name SCOPE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Sets the scope to xid_space.
  ///
  void put_scope(const index_space_handle& xid_space)
  {
    // Preconditions:

    require(xid_space.is_attached());

    // Body:

    _id_spaces = &xid_space.id_spaces();
    _scope_id = xid_space.index();

    // Postconditions:

    ensure(same_scope(xid_space));

    // Exit:

    return;
  };

  ///
  /// True if and only if this is in the same id space as xother.
  ///
  bool same_scope(const scoped_index& xother) const
  {
    return is_scoped() && (_id_spaces == xother._id_spaces) && (_scope_id == xother._scope_id);
  };

  ///
  /// True if and only if this is in the same id space as xid_space.
  ///
  bool same_scope(const index_space_handle& xid_space) const
  {
    return is_scoped() && (_id_spaces == &xid_space.id_spaces()) && (_scope_id == xid_space.index());
  };

  ///
  /// True if and only if this is in the same id space family as xother.
  ///
  bool same_id_space_family(const scoped_index& xother) const
  {
    return is_scoped() && xother.is_scoped() &&
      (_id_spaces == xother._id_spaces);
  };

  ///
  /// True if and only if this is in the same id space family as xid_space.
  ///
  bool same_id_space_family(const index_space_handle& xid_space) const
  {
    return is_scoped() && (xid_space.is_attached()) &&
      (_id_spaces == &(xid_space.id_spaces()));
  };

  ///
  /// The id space family for this scope.
  ///
  const index_space_family& id_spaces() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    // Postconditions:

    // Exit:

    return *_id_spaces;
  };

  ///
  /// The index of the scope id space.
  ///
  pod_type scope_id() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    // Postconditions:

    // Exit:

    return _scope_id;
  };

  ///
  /// Allocate an id space handle to the scope from the handle pool..
  ///
  index_space_handle& get_scope() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    // Postconditions:

    // Exit:

    return _id_spaces->get_id_space(_scope_id);
  };

  ///
  /// Return the id space handle, xid_space to the handle pool.
  ///	
  void release_scope(index_space_handle& xid_space) const
  {
    // Preconditions:

    require(is_scoped());
    require(same_scope(xid_space));

    // Body:

    _id_spaces->release_id_space(xid_space);

    // Postconditions:

    ensure(!xid_space.is_attached());

    // Exit:

    return;
  };

  ///
  /// True if and only if the id space of this is the hub id space.
  ///
  bool is_hub_scope() const
  {
    return is_scoped() &&
      (_id_spaces->hub_id_space().index() == _scope_id);
  };

  ///
  /// True if and only if scope() contains an entry for pod().
  ///
  bool in_scope() const
  {
    return is_scoped() && _id_spaces->contains(_scope_id, _pod);
  };

  ///
  /// True if and only if scope() is attached.
  ///
  bool is_scoped() const
  {
    return (_id_spaces != 0) && _id_spaces->contains(_scope_id);
  };

  ///
  /// Maps xother to the id space of this; sets this to the image
  /// of xother in the id space of this; returns this.
  ///
  scoped_index& operator<<(const scoped_index& xother)
  {
    // Preconditions:

    require(is_scoped());
    require(xother.is_scoped());
    
    // Body:

    _pod = _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure( !is_valid() || (*this) ==~ xother);

    // Exit:

    return *this;
  };

  ///
  /// Maps this to the id space of xother; sets xother to the image
  /// of this in the id space of xother; returns xother.
  ///
  scoped_index& operator>>(scoped_index& xother) const
  {
    // Preconditions:

    require(is_scoped());
    require(xother.is_scoped());
    
    // Body:

    xother._pod = xother._id_spaces->pod(xother._scope_id, this->hub_pod());

    // Postconditions:

    ensure( !xother.is_valid() || (*this) ==~ xother);

    // Exit:

    return xother;
  };

protected:

private:

  ///
  /// The id space family of the scope.
  ///
  const index_space_family* _id_spaces;

  ///
  /// The index of the scope id space.
  ///
  pod_type _scope_id;

  //@}

  // ===========================================================
  /// @name POD FACET
  // ===========================================================
  //@{

public:

  ///
  /// The "plain old data"  storage of this;
  /// the value in the external id space.
  ///
  const pod_type& pod() const
  {
    return _pod;
  };

  ///
  /// Sets pod() to xpod.
  ///
  void put_pod(pod_type xpod)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = xpod;

    // Postconditions:

    ensure(pod() == xpod);

    // Exit:

    return;
  };

  ///
  /// The pod value of the invalid index.
  ///
  static pod_type invalid_pod()
  {
    return invalid_pod_index();
  };

  ///
  /// The pod value of this mapped to the unglued hub id space.
  ///
  pod_type hub_pod() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    return _id_spaces->unglued_hub_pod(_scope_id, _pod);
  };

  ///
  /// The pod value of this mapped to the unglued hub id space.
  ///
  pod_type unglued_hub_pod() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    return _id_spaces->unglued_hub_pod(_scope_id, _pod);
  };

  ///
  /// The pod value of this mapped to the glued hub id space.
  ///
  pod_type glued_hub_pod() const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    return _id_spaces->glued_hub_pod(_scope_id, _pod);
  };

  ///
  /// The hub pod value of this; intended only for use 
  /// with "operators" ==~ and !=~.
  ///
  scoped_index_hub_pod operator~() const
  {
    scoped_index_hub_pod result;
    result.pod = hub_pod();
    return result;
  };
  
  ///
  /// True if and only if the hub_pod of this is equal to xother.
  ///
  bool operator==(scoped_index_hub_pod xother) const
  {
    return hub_pod() == xother.pod;
  };

  ///
  /// True if and only if the hub_pod of this is equal to xother.
  ///
  bool operator!=(scoped_index_hub_pod xother) const
  {
    return hub_pod() != xother.pod;
  };

  ///
  /// True if and only if the hub_pod of this is less than to xother.
  ///
  bool operator<(scoped_index_hub_pod xother) const
  {
    return hub_pod() < xother.pod;
  };

  ///
  /// True if and only if the hub_pod of this is less than or equal
  /// to xother.
  ///
  bool operator<=(scoped_index_hub_pod xother) const
  {
    return hub_pod() <= xother.pod;
  };

  ///
  /// True if and only if the hub_pod of this is greater than to xother.
  ///
  bool operator>(scoped_index_hub_pod xother) const
  {
    return hub_pod() > xother.pod;
  };

  ///
  /// True if and only if the hub_pod of this is greater than or equal
  /// to xother.
  ///
  bool operator>=(scoped_index_hub_pod xother) const
  {
    return hub_pod() >= xother.pod;
  };

protected:

private:

  ///
  /// The "plain old data" index of this.
  ///
  pod_type _pod;

  //@}


  // ===========================================================
  /// @name IDENTIFIER FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is a valid id.
  ///
  bool is_valid() const
  {
    bool result;

    // Preconditions:

    // Body:

    result = (_pod != invalid_pod());

    // Postconditions:

    // Exit:

    return result;
  };

  ///
  /// Make this id invalid.
  ///
  void invalidate()
  {

    // Preconditions:

    // Body:

    _pod = invalid_pod();

    // Postconditions:

    ensure(!is_valid());

    // Exit:
  };

  ///
  /// The invalid id.
  ///
  static const scoped_index& INVALID()
  {
    // Preconditions:

    // Body:

    // Default constructor ensures invalid.

    static const scoped_index result;

    // Postconditions:

    ensure(!result.is_valid());

    // Exit:

    return result;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDER FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is identical to xother, that is, they both
  /// have the same id_space and pod.
  ///
  bool is_identical_to(const scoped_index& xother) const
  {
    bool result;

    // Preconditions:

    // Body:

    result =
      (_pod == xother._pod) &&
      (_id_spaces == xother._id_spaces) &&
      (_scope_id == xother._scope_id);

    // Postconditions:

    // Exit:

    return result;
  };

  ///
  /// True if this is equivalent to xother, that is, if
  /// this refers to the same member as xother.
  ///
  bool is_equivalent_to(const scoped_index& xother) const
  {
    bool result;

    // Preconditions:

    require(is_scoped());
    require(xother.is_scoped());

    // Body:

    /// @issue is_equivalent_to will return true if neither
    /// this nor xother are in_scope. Is that right?
    /// Is there a single non-member that they both refer to?

    result = (hub_pod() == xother.hub_pod());

    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this is identical to xother, that is, if
  /// this refers to the same member in the same id space as xother.
  ///
  bool operator==(const scoped_index& xother) const
  {
    bool result;

    // Preconditions:

    // Body:

    result = is_identical_to(xother);
      
    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this not identical to as xother.
  ///
  bool operator!=(const scoped_index& xother) const
  {
    bool result;

    // Preconditions:

    // Body:

    result = !is_identical_to(xother);

    // Postconditions:

    // Exit:

    return result;
  };

  ///
  /// True if this is less than xother.
  ///
  bool operator<(const scoped_index& xother) const
  {
    // Preconditions:

    require(same_scope(xother));

    // Body:

    bool result = (_pod < xother._pod);

    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this is less than or equal to xother.
  ///
  bool operator<=(const scoped_index& xother) const
  {
    // Preconditions:

    require(same_scope(xother));

    // Body:

    bool result = (_pod <= xother._pod);

    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this is greater than xother.
  ///
  bool operator>(const scoped_index& xother) const
  {
    // Preconditions:

    require(same_scope(xother));

    // Body:

    bool result = (_pod > xother._pod);

    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this is greater than or equal to xother.
  ///
  bool operator>=(const scoped_index& xother) const
  {
    // Preconditions:

    require(same_scope(xother));

    // Body:

    bool result = (_pod >= xother._pod);

    // Postconditions:

    ensure(is_basic_query);

    // Exit:

    return result;
  };

  ///
  /// True if this is greater than or equal to xbegin and less than
  /// xend in the id space of xbegin and xend.
  ///
  bool in_range(const scoped_index& xbegin, const scoped_index& xend) const
  {
    // Preconditions:

    require(xbegin.same_scope(xend));
    require(same_id_space_family(xbegin));
    
    // Body:

    pod_index_type lpod = xbegin._id_spaces->pod(xbegin._scope_id, this->hub_pod());

    bool result = ((xbegin.pod() <= lpod) && (xend.pod() > lpod));
    
    // Postconditions:

    // Exit:

    return result;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name ARITHMETIC FACET
  // ===========================================================
  //@{

public:

  ///
  /// This + xother.
  ///
  scoped_index operator+(const scoped_index& xother) const
  {
    // Preconditions:

    // Body:

    scoped_index result(*this);
    result += xother;

    // Postconditions:

    ensure(result.same_scope(*this));
    ensure(result.pod() == (pod() + id_spaces().pod(scope_id(), xother)));

    // Exit:

    return result;
  };


  ///
  /// This := this + xother.
  ///
  scoped_index& operator+=(const scoped_index& xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    _pod += _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure(pod() == (old_pod + id_spaces().pod(scope_id(), xother)));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// Prefix increment.
  ///
  scoped_index& operator++()
  {
    // Preconditions:

    require(is_valid());

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    ++_pod;

    // Postconditions:

    ensure(pod() == (old_pod + 1));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// Postfix increment.
  ///
  const scoped_index operator++(int)
  {
    // Preconditions:

    require(is_valid());

    // Body:

    define_old_variable(pod_type old_pod = pod());

    scoped_index result(*this);

    ++_pod;

    // Postconditions:

    ensure(pod() == (old_pod + 1));
    ensure(result.pod() == old_pod);


    // Exit:

    return result;
  };

  ///
  /// Negation (unary minus).
  ///
  scoped_index operator-() const
  {
    scoped_index result;
    result._pod = -_pod;
    return result;
  };

  ///
  /// This - xother.
  ///
  scoped_index operator-(const scoped_index& xother) const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    scoped_index result(*this);
    result -= xother;

    // Postconditions:

    ensure(result.pod() == (pod() - id_spaces().pod(scope_id(), xother)));

    // Exit:

    return result;
  };


  ///
  /// This := this - xother.
  ///
  scoped_index& operator-=(const scoped_index& xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    _pod -= _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure(pod() == (old_pod - id_spaces().pod(scope_id(), xother)));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// Prefix decrement.
  ///
  scoped_index& operator--()
  {
    // Preconditions:

    require(is_valid());

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    --_pod;

    // Postconditions:

    ensure(pod() == (old_pod - 1));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// Postfix decrement.
  ///
  const scoped_index operator--(int)
  {
    // Preconditions:

    require(is_valid());

    // Body:

    define_old_variable(pod_type old_pod = pod());

    scoped_index result(*this);

    --_pod;

    // Postconditions:

    ensure(pod() == (old_pod - 1));
    ensure(result.pod() == old_pod);


    // Exit:

    return result;
  };

  ///
  /// This * xother.
  ///
  scoped_index operator*(const scoped_index& xother) const
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    scoped_index result(*this);
    result *= xother;

    // Postconditions:

    ensure(result.pod() == (pod() * id_spaces().pod(scope_id(), xother)));

    // Exit:

    return result;
  };


  ///
  /// This := this * xother.
  ///
  scoped_index& operator*=(const scoped_index& xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    _pod *= _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure(pod() == (old_pod * id_spaces().pod(scope_id(), xother)));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// This / xother.
  ///
  scoped_index operator/(const scoped_index& xother) const
  {
    // Preconditions:

    require(xother.pod() != 0);

    // Body:

    scoped_index result(*this);
    result /= xother;

    // Postconditions:

    ensure(result.pod() == (pod() / xother.pod()));

    // Exit:

    return result;
  };


  ///
  /// This := this / xother.
  ///
  scoped_index& operator/=(const scoped_index& xother)
  {
    // Preconditions:

    require(is_scoped());
    require(id_spaces().pod(scope_id(), xother) != 0);

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    _pod /= _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure(pod() == (old_pod / id_spaces().pod(scope_id(), xother)));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// This modulo xother.
  ///
  scoped_index operator%(const scoped_index& xother) const
  {
    // Preconditions:

    require(is_scoped());
    require(id_spaces().pod(scope_id(), xother) != 0);

    // Body:

    scoped_index result(*this);
    result %= xother;

    // Postconditions:

    ensure(result.pod() == (pod() % id_spaces().pod(scope_id(), xother)));

    // Exit:

    return result;
  };


  ///
  /// This := this modulo xother.
  ///
  scoped_index& operator%=(const scoped_index& xother)
  {

    // Preconditions:

    require(is_scoped());
    require(id_spaces().pod(scope_id(), xother) != 0);

    // Body:

    define_old_variable(pod_type old_pod = pod());
    define_old_variable(scoped_index& result = *this);

    _pod %= _id_spaces->pod(_scope_id, xother.hub_pod());

    // Postconditions:

    ensure(pod() == (old_pod % id_spaces().pod(scope_id(), xother)));
    ensure(&result == this);

    // Exit:

    return *this;
  };

  ///
  /// True if this is greater than or equal to ZERO.
  ///
  bool is_positive() const
  {
    return _pod >= 0;
  };

  ///
  /// True if this is greater than ZERO.
  ///
  bool is_positive_definite() const
  {
    return _pod > 0;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIMITIVE_TYPE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(primitive_type x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_PRIMITIVE_TYPE) == (!is_valid()));
  };

  ///
  /// Conversion to primitive_type
  ///
  operator primitive_type() const
  {
    return primitive_attributes::id(_pod);
  };

  ///
  /// Assignment from primitive_type.
  ///
  scoped_index& operator=(primitive_type x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as primitive_type x.
  ///
  bool operator==(primitive_type x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as primitive_type x.
  ///
  bool operator!=(primitive_type x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than primitive_type x.
  ///
  bool operator<(primitive_type x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to primitive_type x.
  ///
  bool operator<=(primitive_type x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than primitive_type x.
  ///
  bool operator>(primitive_type x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to primitive_type x.
  ///
  bool operator>=(primitive_type x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STANDARD_MEMBER_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(standard_member_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_STANDARD_MEMBER_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to standard_member_index
  ///
  operator standard_member_index() const
  {
    return standard_member_index_from_index(_pod);
  };

  ///
  /// Assignment from standard_member_index.
  ///
  scoped_index& operator=(standard_member_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as standard_member_index x.
  ///
  bool operator==(standard_member_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as standard_member_index x.
  ///
  bool operator!=(standard_member_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than standard_member_index x.
  ///
  bool operator<(standard_member_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to standard_member_index x.
  ///
  bool operator<=(standard_member_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than standard_member_index x.
  ///
  bool operator>(standard_member_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to standard_member_index x.
  ///
  bool operator>=(standard_member_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIMITIVES_SCHEMA_MEMBER_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(primitives_schema_member_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_PRIMITIVES_SCHEMA_MEMBER_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to primitives_schema_member_index
  ///
  operator primitives_schema_member_index() const
  {
    return primitives_schema_member_index_from_index(_pod);
  };

  ///
  /// Assignment from primitives_schema_member_index.
  ///
  scoped_index& operator=(primitives_schema_member_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as primitives_schema_member_index x.
  ///
  bool operator==(primitives_schema_member_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as primitives_schema_member_index x.
  ///
  bool operator!=(primitives_schema_member_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than primitives_schema_member_index x.
  ///
  bool operator<(primitives_schema_member_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to primitives_schema_member_index x.
  ///
  bool operator<=(primitives_schema_member_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than primitives_schema_member_index x.
  ///
  bool operator>(primitives_schema_member_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to primitives_schema_member_index x.
  ///
  bool operator>=(primitives_schema_member_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name NAMESPACE_SCHEMA_MEMBER_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(namespace_schema_member_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_NAMESPACE_SCHEMA_MEMBER_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to namespace_schema_member_index
  ///
  operator namespace_schema_member_index() const
  {
    return namespace_schema_member_index_from_index(_pod);
  };

  ///
  /// Assignment from namespace_schema_member_index.
  ///
  scoped_index& operator=(namespace_schema_member_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as namespace_schema_member_index x.
  ///
  bool operator==(namespace_schema_member_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as namespace_schema_member_index x.
  ///
  bool operator!=(namespace_schema_member_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than namespace_schema_member_index x.
  ///
  bool operator<(namespace_schema_member_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to namespace_schema_member_index x.
  ///
  bool operator<=(namespace_schema_member_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than namespace_schema_member_index x.
  ///
  bool operator>(namespace_schema_member_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to namespace_schema_member_index x.
  ///
  bool operator>=(namespace_schema_member_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name NAMESPACE_MEMBER_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(namespace_member_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_NAMESPACE_MEMBER_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to namespace_member_index
  ///
  operator namespace_member_index() const
  {
    return namespace_member_index_from_index(_pod);
  };

  ///
  /// Assignment from namespace_member_index.
  ///
  scoped_index& operator=(namespace_member_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as namespace_member_index x.
  ///
  bool operator==(namespace_member_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as namespace_member_index x.
  ///
  bool operator!=(namespace_member_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than namespace_member_index x.
  ///
  bool operator<(namespace_member_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to namespace_member_index x.
  ///
  bool operator<=(namespace_member_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than namespace_member_index x.
  ///
  bool operator>(namespace_member_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to namespace_member_index x.
  ///
  bool operator>=(namespace_member_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STANDARD_SUBPOSET_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(standard_subposet_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_STANDARD_SUBPOSET_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to standard_subposet_index
  ///
  operator standard_subposet_index() const
  {
    return standard_subposet_index_from_index(_pod);
  };

  ///
  /// Assignment from standard_subposet_index.
  ///
  scoped_index& operator=(standard_subposet_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as standard_subposet_index x.
  ///
  bool operator==(standard_subposet_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as standard_subposet_index x.
  ///
  bool operator!=(standard_subposet_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than standard_subposet_index x.
  ///
  bool operator<(standard_subposet_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to standard_subposet_index x.
  ///
  bool operator<=(standard_subposet_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than standard_subposet_index x.
  ///
  bool operator>(standard_subposet_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to standard_subposet_index x.
  ///
  bool operator>=(standard_subposet_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STANDARD_VERSION_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(standard_version_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_STANDARD_VERSION_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to standard_version_index
  ///
  operator standard_version_index() const
  {
    return standard_version_index_from_index(_pod);
  };

  ///
  /// Assignment from standard_version_index.
  ///
  scoped_index& operator=(standard_version_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as standard_version_index x.
  ///
  bool operator==(standard_version_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as standard_version_index x.
  ///
  bool operator!=(standard_version_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than standard_version_index x.
  ///
  bool operator<(standard_version_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to standard_version_index x.
  ///
  bool operator<=(standard_version_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than standard_version_index x.
  ///
  bool operator>(standard_version_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to standard_version_index x.
  ///
  bool operator>=(standard_version_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name STANDARD_DOF_TUPLE_INDEX FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(standard_dof_tuple_index x, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(x)
  {
    ensure((x == NOT_A_STANDARD_DOF_TUPLE_INDEX) == (!is_valid()));
  };

  ///
  /// Conversion to standard_dof_tuple_index
  ///
  operator standard_dof_tuple_index() const
  {
    return standard_dof_tuple_index_from_index(_pod);
  };

  ///
  /// Assignment from standard_dof_tuple_index.
  ///
  scoped_index& operator=(standard_dof_tuple_index x)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = x;

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as standard_dof_tuple_index x.
  ///
  bool operator==(standard_dof_tuple_index x) const
  {
    return _pod == x;
  };

  ///
  /// True if this does not have the same value as standard_dof_tuple_index x.
  ///
  bool operator!=(standard_dof_tuple_index x) const
  {
    return _pod != x;
  };

  ///
  /// True if this is less than standard_dof_tuple_index x.
  ///
  bool operator<(standard_dof_tuple_index x) const
  {
    return _pod < x;
  };

  ///
  /// True if this is less than or equal to standard_dof_tuple_index x.
  ///
  bool operator<=(standard_dof_tuple_index x) const
  {
    return _pod <= x;
  };

  ///
  /// True if this is greater than standard_dof_tuple_index x.
  ///
  bool operator>(standard_dof_tuple_index x) const
  {
    return _pod > x;
  };

  ///
  /// True if this is greater than or equal to standard_dof_tuple_index x.
  ///
  bool operator>=(standard_dof_tuple_index x) const
  {
    return _pod >= x;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name UNSIGNED CHAR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(unsigned char xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to unsigned char
  ///
  operator unsigned char() const
  {
    return static_cast<unsigned char>(_pod);
  };

  ///
  /// Assignment from unsigned char.
  ///
  scoped_index& operator=(unsigned char xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as unsigned char xother.
  ///
  bool operator==(unsigned char xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as unsigned char xother.
  ///
  bool operator!=(unsigned char xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than unsigned char xother.
  ///
  bool operator<(unsigned char xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to unsigned char xother.
  ///
  bool operator<=(unsigned char xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than unsigned char xother.
  ///
  bool operator>(unsigned char xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to unsigned char xother.
  ///
  bool operator>=(unsigned char xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + unsigned char xother.
  ///
  scoped_index& operator+=(unsigned char xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + unsigned char xother.
  ///
  scoped_index operator+(unsigned char xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - unsigned char xother.
  ///
  scoped_index& operator-=(unsigned char xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - unsigned char xother.
  ///
  scoped_index operator-(unsigned char xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * unsigned char xother.
  ///
  scoped_index& operator*=(unsigned char xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * unsigned char xother.
  ///
  scoped_index operator*(unsigned char xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / unsigned char xother.
  ///
  scoped_index& operator/=(unsigned char xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / unsigned char xother.
  ///
  scoped_index operator/(unsigned char xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo unsigned char xother.
  ///
  scoped_index& operator%=(unsigned char xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo unsigned char xother.
  ///
  scoped_index operator%(unsigned char xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name UNSIGNED SHORT INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(unsigned short int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to unsigned short int
  ///
  operator unsigned short int() const
  {
    return static_cast<unsigned short int>(_pod);
  };

  ///
  /// Assignment from unsigned short int.
  ///
  scoped_index& operator=(unsigned short int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as unsigned short int xother.
  ///
  bool operator==(unsigned short int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as unsigned short int xother.
  ///
  bool operator!=(unsigned short int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than unsigned short int xother.
  ///
  bool operator<(unsigned short int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to unsigned short int xother.
  ///
  bool operator<=(unsigned short int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than unsigned short int xother.
  ///
  bool operator>(unsigned short int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to unsigned short int xother.
  ///
  bool operator>=(unsigned short int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + unsigned short int xother.
  ///
  scoped_index& operator+=(unsigned short int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + unsigned short int xother.
  ///
  scoped_index operator+(unsigned short int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - unsigned short int xother.
  ///
  scoped_index& operator-=(unsigned short int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - unsigned short int xother.
  ///
  scoped_index operator-(unsigned short int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * unsigned short int xother.
  ///
  scoped_index& operator*=(unsigned short int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * unsigned short int xother.
  ///
  scoped_index operator*(unsigned short int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / unsigned short int xother.
  ///
  scoped_index& operator/=(unsigned short int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / unsigned short int xother.
  ///
  scoped_index operator/(unsigned short int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo unsigned short int xother.
  ///
  scoped_index& operator%=(unsigned short int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo unsigned short int xother.
  ///
  scoped_index operator%(unsigned short int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name UNSIGNED INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(unsigned int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to unsigned int
  ///
  operator unsigned int() const
  {
    return static_cast<unsigned int>(_pod);
  };

  ///
  /// Assignment from unsigned int.
  ///
  scoped_index& operator=(unsigned int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as unsigned int xother.
  ///
  bool operator==(unsigned int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as unsigned int xother.
  ///
  bool operator!=(unsigned int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than unsigned int xother.
  ///
  bool operator<(unsigned int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to unsigned int xother.
  ///
  bool operator<=(unsigned int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than unsigned int xother.
  ///
  bool operator>(unsigned int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to unsigned int xother.
  ///
  bool operator>=(unsigned int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + unsigned int xother.
  ///
  scoped_index& operator+=(unsigned int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + unsigned int xother.
  ///
  scoped_index operator+(unsigned int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - unsigned int xother.
  ///
  scoped_index& operator-=(unsigned int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - unsigned int xother.
  ///
  scoped_index operator-(unsigned int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * unsigned int xother.
  ///
  scoped_index& operator*=(unsigned int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * unsigned int xother.
  ///
  scoped_index operator*(unsigned int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / unsigned int xother.
  ///
  scoped_index& operator/=(unsigned int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / unsigned int xother.
  ///
  scoped_index operator/(unsigned int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo unsigned int xother.
  ///
  scoped_index& operator%=(unsigned int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo unsigned int xother.
  ///
  scoped_index operator%(unsigned int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name UNSIGNED LONG INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(unsigned long int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to unsigned long int
  ///
  operator unsigned long int() const
  {
    return static_cast<unsigned long int>(_pod);
  };

  ///
  /// Assignment from unsigned long int.
  ///
  scoped_index& operator=(unsigned long int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as unsigned long int xother.
  ///
  bool operator==(unsigned long int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as unsigned long int xother.
  ///
  bool operator!=(unsigned long int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than unsigned long int xother.
  ///
  bool operator<(unsigned long int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to unsigned long int xother.
  ///
  bool operator<=(unsigned long int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than unsigned long int xother.
  ///
  bool operator>(unsigned long int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to unsigned long int xother.
  ///
  bool operator>=(unsigned long int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + unsigned long int xother.
  ///
  scoped_index& operator+=(unsigned long int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + unsigned long int xother.
  ///
  scoped_index operator+(unsigned long int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - unsigned long int xother.
  ///
  scoped_index& operator-=(unsigned long int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - unsigned long int xother.
  ///
  scoped_index operator-(unsigned long int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * unsigned long int xother.
  ///
  scoped_index& operator*=(unsigned long int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * unsigned long int xother.
  ///
  scoped_index operator*(unsigned long int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / unsigned long int xother.
  ///
  scoped_index& operator/=(unsigned long int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / unsigned long int xother.
  ///
  scoped_index operator/(unsigned long int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo unsigned long int xother.
  ///
  scoped_index& operator%=(unsigned long int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo unsigned long int xother.
  ///
  scoped_index operator%(unsigned long int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name SIGNED CHAR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(signed char xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to signed char
  ///
  operator signed char() const
  {
    return static_cast<signed char>(_pod);
  };

  ///
  /// Assignment from signed char.
  ///
  scoped_index& operator=(signed char xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as signed char xother.
  ///
  bool operator==(signed char xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as signed char xother.
  ///
  bool operator!=(signed char xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than signed char xother.
  ///
  bool operator<(signed char xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to signed char xother.
  ///
  bool operator<=(signed char xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than signed char xother.
  ///
  bool operator>(signed char xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to signed char xother.
  ///
  bool operator>=(signed char xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + signed char xother.
  ///
  scoped_index& operator+=(signed char xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + signed char xother.
  ///
  scoped_index operator+(signed char xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - signed char xother.
  ///
  scoped_index& operator-=(signed char xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - signed char xother.
  ///
  scoped_index operator-(signed char xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * signed char xother.
  ///
  scoped_index& operator*=(signed char xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * signed char xother.
  ///
  scoped_index operator*(signed char xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / signed char xother.
  ///
  scoped_index& operator/=(signed char xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / signed char xother.
  ///
  scoped_index operator/(signed char xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo signed char xother.
  ///
  scoped_index& operator%=(signed char xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo signed char xother.
  ///
  scoped_index operator%(signed char xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name SHORT INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(short int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to short int
  ///
  operator short int() const
  {
    return static_cast<short int>(_pod);
  };

  ///
  /// Assignment from short int.
  ///
  scoped_index& operator=(short int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as short int xother.
  ///
  bool operator==(short int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as short int xother.
  ///
  bool operator!=(short int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than short int xother.
  ///
  bool operator<(short int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to short int xother.
  ///
  bool operator<=(short int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than short int xother.
  ///
  bool operator>(short int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to short int xother.
  ///
  bool operator>=(short int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + short int xother.
  ///
  scoped_index& operator+=(short int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + short int xother.
  ///
  scoped_index operator+(short int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - short int xother.
  ///
  scoped_index& operator-=(short int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - short int xother.
  ///
  scoped_index operator-(short int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * short int xother.
  ///
  scoped_index& operator*=(short int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * short int xother.
  ///
  scoped_index operator*(short int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / short int xother.
  ///
  scoped_index& operator/=(short int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / short int xother.
  ///
  scoped_index operator/(short int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo short int xother.
  ///
  scoped_index& operator%=(short int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo short int xother.
  ///
  scoped_index operator%(short int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to int
  ///
  operator int() const
  {
    return static_cast<int>(_pod);
  };

  ///
  /// Assignment from int.
  ///
  scoped_index& operator=(int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as int xother.
  ///
  bool operator==(int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as int xother.
  ///
  bool operator!=(int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than int xother.
  ///
  bool operator<(int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to int xother.
  ///
  bool operator<=(int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than int xother.
  ///
  bool operator>(int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to int xother.
  ///
  bool operator>=(int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + int xother.
  ///
  scoped_index& operator+=(int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + int xother.
  ///
  scoped_index operator+(int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - int xother.
  ///
  scoped_index& operator-=(int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - int xother.
  ///
  scoped_index operator-(int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * int xother.
  ///
  scoped_index& operator*=(int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * int xother.
  ///
  scoped_index operator*(int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / int xother.
  ///
  scoped_index& operator/=(int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / int xother.
  ///
  scoped_index operator/(int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo int xother.
  ///
  scoped_index& operator%=(int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo int xother.
  ///
  scoped_index operator%(int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LONG INT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with pod() == x in the scope of xid_space.
  ///
  scoped_index(long int xother, const index_space_handle& xid_space)
    : _id_spaces(&xid_space.id_spaces()),
      _scope_id(xid_space.index()),
      _pod(static_cast<pod_type>(xother))
  {
  };

  ///
  /// Conversion to long int
  ///
  operator long int() const
  {
    return static_cast<long int>(_pod);
  };

  ///
  /// Assignment from long int.
  ///
  scoped_index& operator=(long int xother)
  {
    // Preconditions:

    require(is_scoped());

    // Body:

    _pod = static_cast<pod_type>(xother);

    // Postconditions:

    // Exit:

    return *this;
  };

  ///
  /// True if this has the same value as long int xother.
  ///
  bool operator==(long int xother) const
  {
    return _pod == static_cast<pod_type>(xother);
  };

  ///
  /// True if this does not have the same value as long int xother.
  ///
  bool operator!=(long int xother) const
  {
    return _pod != static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than long int xother.
  ///
  bool operator<(long int xother) const
  {
    return _pod < static_cast<pod_type>(xother);
  };

  ///
  /// True if this is less than or equal to long int xother.
  ///
  bool operator<=(long int xother) const
  {
    return _pod <= static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than long int xother.
  ///
  bool operator>(long int xother) const
  {
    return _pod > static_cast<pod_type>(xother);
  };

  ///
  /// True if this is greater than or equal to long int xother.
  ///
  bool operator>=(long int xother) const
  {
    return _pod >= static_cast<pod_type>(xother);
  };

  ///
  /// This := this + long int xother.
  ///
  scoped_index& operator+=(long int xother)
  {
    _pod += static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This + long int xother.
  ///
  scoped_index operator+(long int xother) const
  {
    scoped_index result(*this);
    return result += xother;
  };

  ///
  /// This := this - long int xother.
  ///
  scoped_index& operator-=(long int xother)
  {
    _pod -= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This - long int xother.
  ///
  scoped_index operator-(long int xother) const
  {
    scoped_index result(*this);
    return result -= xother;
  };

  ///
  /// This := this * long int xother.
  ///
  scoped_index& operator*=(long int xother)
  {
    _pod *= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This * long int xother.
  ///
  scoped_index operator*(long int xother) const
  {
    scoped_index result(*this);
    return result *= xother;
  };

  ///
  /// This := this / long int xother.
  ///
  scoped_index& operator/=(long int xother)
  {
    _pod /= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This / long int xother.
  ///
  scoped_index operator/(long int xother) const
  {
    scoped_index result(*this);
    return result /= xother;
  };

  ///
  /// This := this modulo long int xother.
  ///
  scoped_index& operator%=(long int xother)
  {
    _pod %= static_cast<pod_type>(xother);
    return *this;
  };

  ///
  /// This modulo long int xother.
  ///
  scoped_index operator%(long int xother) const
  {
    scoped_index result(*this);
    return result %= xother;
  };

protected:

private:

  //@}

};

// =============================================================================
// NON-MEMBER FUNCTIONS
// =============================================================================

///
/// Inserts xid into ostream xos.
///
SHEAF_DLL_SPEC
ostream& operator<<(ostream& xos, const scoped_index& xid);

///
/// Extracts xid from istream xis.
///
SHEAF_DLL_SPEC
istream& operator>>(istream& xis, scoped_index& xid);

///
/// The deep size of the referenced object of type scoped_index.
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC
size_t deep_size(const scoped_index& xp, bool xinclude_shallow = true);


// =============================================================================
// TEMPLATE SPECIALIZATIONS
// =============================================================================

///
/// Features describing scoped_index as an index type.
///
template <>
struct SHEAF_DLL_SPEC index_traits<scoped_index>
{
  ///
  /// The index type.
  ///
  typedef scoped_index index_type;

  ///
  /// The plain old data (POD) type associated with the index type.
  ///
  typedef index_type::pod_type pod_type;

  ///
  /// Converts an index type xindex to pod_type.
  ///
  static pod_type pod(const index_type& xindex)
  {
    return xindex.pod();
  };

  ///
  /// Sets the pod of an index type xindex to xpod.
  ///
  static void put_pod(index_type& xindex, pod_type& xpod)
  {
    xindex.put_pod(xpod);
    return;
  };

  ///
  /// The invalid index value.
  ///
  static index_type invalid()
  {
    return index_type::INVALID();
  };

  ///
  /// True if xindex is valid.
  ///
  static bool is_valid(const index_type& xindex)
  {
    return xindex.is_valid();
  };

  ///
  /// True if xindex is >= 0.
  ///
  static bool is_positive(const index_type& xindex)
  {
    return xindex.is_positive();
  };

  ///
  /// True if xindex is > 0.
  ///
  static bool is_positive_definite(const index_type& xindex)
  {
    return xindex.is_positive_definite();
  };

};
 
} // namespace sheaf

#ifndef SWIG

// Swig doesn't replace preprocessor macros, except to
// process ifdef, ifndef, etc. So the follwoing macro creates
// a syntax error when processed by swig.
// But swig would ignore the namespace and template declaration
// any way, so just don't process it.

SHEAF_BEGIN_HASH_NAMESPACE

///
/// Specialization of hash function to scoped_index.
///
template<> struct SHEAF_DLL_SPEC hash<sheaf::scoped_index>
{
  size_t operator()(sheaf::scoped_index xindex) const;
};

SHEAF_END_HASH_NAMESPACE

#endif // SWIG


#endif // ifndef SCOPED_INDEX_H

