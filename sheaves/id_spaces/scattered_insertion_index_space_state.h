
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
/// Interface for class scattered_insertion_index_space_state.

#ifndef SCATTERED_INSERTION_INDEX_SPACE_STATE_H
#define SCATTERED_INSERTION_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef GATHERED_INSERTION_INDEX_SPACE_STATE_H
#include "SheafSystem/gathered_insertion_index_space_state.h"
#endif

namespace sheaf
{

class scattered_insertion_index_space_handle;

///
///
/// An implementation of class explicit_index_space_state that supports
/// either gathered or scattered insertion of new members, that is, 
/// new members can be inserted within the existing domain interval,
/// at the end of it, or discontiguously.
///
///
class SHEAF_DLL_SPEC scattered_insertion_index_space_state : public gathered_insertion_index_space_state
{

  // ===========================================================
  /// @name SCATTERED_INSERTION_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  scattered_insertion_index_space_state();

  ///
  /// Copy constructor; disabled.
  ///
  scattered_insertion_index_space_state(const scattered_insertion_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~scattered_insertion_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name MUTABLE INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make id xid in this id space equivalent to xhub_id in the hub id space.
  /// synonym for insert(xid, xhub_id.hub_pod()).
  ///
  void insert(pod_type xid, const scoped_index& xhub_id);

  ///
  /// Make id xid in this id space equivalent to xhub_id in the hub id space.
  ///
  void insert(pod_type xid, pod_type xhub_id);

protected:

private:

  //@}

  // ===========================================================
  /// @name GATHERED_INSERTION_INDEX_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}
 

  // ===========================================================
  /// @name MAP REPRESENTATION FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Inserts entry (xdomain_id, xrange_id) into the map representation.
  ///
  virtual void map_rep_insert_entry(pod_type xdomain_id, pod_type xrange_id) = 0;

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this is equivalent to xother.
  ///
  virtual bool operator==(const explicit_index_space_state& xother) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual scattered_insertion_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

protected:

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
  virtual const std::string& class_name() const;

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
/// The deep size of scattered_insertion_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const scattered_insertion_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef SCATTERED_INSERTION_INDEX_SPACE_STATE_H
