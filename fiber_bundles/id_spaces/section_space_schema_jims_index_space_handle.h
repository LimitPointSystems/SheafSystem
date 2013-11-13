
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
/// Interface for class section_space_schema_jims_index_space_handle

#ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_HANDLE_H
#define SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_HANDLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_HANDLE_H
#include "explicit_index_space_handle.h"
#endif

namespace sheaf
{
class ij_product_structure;
}

namespace fiber_bundle
{

using namespace sheaf;

class section_space_schema_jims_index_space_state;
  
///
/// An implementation of class explicit_index_space_handle that has
/// a section space schema jims id space state.
///
class SHEAF_DLL_SPEC section_space_schema_jims_index_space_handle : public explicit_index_space_handle
{

  friend class section_space_schema_jims_index_space_state;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new section space schema jims id space in the id space
  /// family xid_space with name xname, base space id space xbase_space_id_space,
  /// fiber schema id space, xfiber_schema_id_space and section space schema
  /// product structure xsection_space_schema_product.
  /// Returns a handle to the id space created.
  ///
  static
  section_space_schema_jims_index_space_handle
  new_space(index_space_family& xid_spaces,
	    const string& xname,
	    const index_space_handle& xbase_space_id_space,
	    const index_space_handle& xfiber_schema_id_space,
	    const ij_product_structure& xsection_space_schema_product);

protected:

private:

  //@}


  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  section_space_schema_jims_index_space_handle();

  ///
  /// Copy constructor
  ///
  section_space_schema_jims_index_space_handle(const section_space_schema_jims_index_space_handle& xother);

  ///
  /// Constructor: Attach to state with index xindex in the family xid_spaces.
  ///
  section_space_schema_jims_index_space_handle(const index_space_family& xid_spaces,
					       pod_type xindex);

  ///
  /// Constructor: Attach to state with name xname in the family xid_spaces.
  ///
  section_space_schema_jims_index_space_handle(const index_space_family& xid_spaces,
					       const string& xname);

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  section_space_schema_jims_index_space_handle& operator=(const section_space_schema_jims_index_space_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_jims_index_space_handle();

protected:

  ///
  /// Constructor: Attach to state xstate.
  ///
  section_space_schema_jims_index_space_handle(section_space_schema_jims_index_space_state& xstate);

  using explicit_index_space_handle::state;

  ///
  /// The section space schema jims id space state (mutable version).
  ///
  section_space_schema_jims_index_space_state& state();

  ///
  /// The section space schema jims id space state (const version).
  ///
  const section_space_schema_jims_index_space_state& state() const;

private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE SCHEMA JIMS INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Set the factors for this section space schema id space.
  ///
  void put_factors(const index_space_handle& xbase_space_id_space,
		   const index_space_handle& xfiber_schema_id_space,
		   const ij_product_structure& xsection_space_schema_product);

  ///
  /// The base space jims id space.
  ///
  const index_space_handle& base_space() const;

  ///
  /// The fiber schema jims id space.
  ///
  const index_space_handle& fiber_schema() const;

  ///
  /// The product structure of the section space schema id space.
  ///
  const ij_product_structure& section_space_schema_product_structure() const;

  ///
  /// True, if this id space is consistent with the base space and the
  /// fiber schema jims id spaces.
  ///
  bool is_consistent() const;

  ///
  /// Make this id space consistent with the base space and fiber schema
  /// jims id spaces.
  ///
  void update();

protected:

private:

  //@}


  // ===========================================================
  /// @name EXPLICIT_INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name INDEX_SPACE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Assignment operator; attach this handle to the state of xother.
  /// synonym for attach_to(xother).
  ///
  virtual section_space_schema_jims_index_space_handle& operator=(const index_space_handle& xother);

  ///
  /// Virtual constructor, makes a new instance of the same type as this.
  /// If the handle is attached, attach to the same state.
  ///
  virtual section_space_schema_jims_index_space_handle* clone() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE FACET
  // ===========================================================
  //@{

public:

  using explicit_index_space_handle::conforms_to_state;

  ///
  /// True if this conforms to the handle type required by the state
  /// with local scope id xlocal_id in the host id space collection xhost.
  ///
  virtual bool conforms_to_state(const index_space_collection& xhost,
				 pod_type xlocal_id) const;

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

} // end namespace sheaf

#endif // ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_HANDLE_H
