
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
/// Interface for class index_space_interval

#ifndef INDEX_SPACE_INTERVAL_H
#define INDEX_SPACE_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef FACTORY_2_H
#include "factory_2.h"
#endif

#ifndef INDEX_SPACE_COLLECTION_H
#include "index_space_collection.h"
#endif

namespace sheaf
{
  
class arg_list;

///
/// An implemenation of index_space_collection that adds an interface
/// for the interval [begin(), end()) in the id space family.
///
class SHEAF_DLL_SPEC index_space_interval : public index_space_collection
{

  friend class index_space_family_iterator;
  friend class index_space_interval_iterator;

  // ===========================================================
  /// @name INDEX_SPACE_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an arg list for constructing an instance of this.
  ///
  static arg_list make_arg_list();

  ///
  /// Destructor
  ///
  virtual ~index_space_interval();

  using index_space_collection::begin;

  ///
  /// Beginning space id of this interval in the id space family scope.
  ///
  pod_type begin() const;

  using index_space_collection::end;

  ///
  /// Ending space id of this interval in the id space family scope.
  ///
  pod_type end() const;

  ///
  /// True if id xspace_id is in the bounds [begin(), end()).
  ///
  bool in_bounds(pod_type xspace_id) const;

protected:

  ///
  /// Default constructor
  ///
  index_space_interval();

  ///
  /// Constructor: Creates an instance from arguments, xargs.
  ///
  index_space_interval(const arg_list& xargs);

  ///
  /// Copy constructor; disabled.
  ///
  index_space_interval(const index_space_interval& xother) { };

  ///
  /// True, if this interval supports persistent id spaces.
  ///
  virtual bool supports_persistent_id_spaces() const;

  ///
  /// Beginning space id of this interval in the id space family scope.
  ///
  pod_type _begin;

  ///
  /// Ending space id of this interval in the id space family scope.
  ///
  pod_type _end;

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_COLLECTION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const index_space_collection& xother) const;

  using index_space_collection::contains;

  ///
  /// True if this collection contains the id space with local id xlocal_id.
  ///
  virtual bool contains(pod_type xlocal_id) const;

  ///
  /// True if this collection contains the id space with family id xspace_id.
  ///
  virtual bool contains_family(pod_type xspace_id) const;

  ///
  /// Id relative to this collection equivalent to the id space family id xspace_id.
  ///
  virtual pod_type local_scope(pod_type xspace_id) const;

  ///
  /// Id relative to the id space family equivalent to the local id xlocal_id.
  ///
  virtual pod_type family_scope(pod_type xlocal_id) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual index_space_interval& operator=(const index_space_collection& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The id space family for this (const version).
  ///
  virtual const index_space_family& id_spaces() const;

  ///
  /// The id space family for this (mutable version).
  ///
  virtual index_space_family& id_spaces();

protected:

  ///
  /// The index space family of this collection.
  ///
  index_space_family* _id_spaces;

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@}

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// A factory for making descendants of this class.
  ///
  static factory_2<index_space_interval>& id_space_interval_factory();

  ///
  /// Virtual constructor; create a new instance of the same type at this
  /// with arguments xargs.
  ///
  virtual index_space_interval* clone(const arg_list& xargs) const = 0;

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
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert index_space_interval& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const index_space_interval& xn);

} // end namespace sheaf

#endif // ifndef INDEX_SPACE_INTERVAL_H
