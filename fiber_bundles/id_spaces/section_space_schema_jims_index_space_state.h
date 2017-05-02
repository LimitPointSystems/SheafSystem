
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
/// Interface for class section_space_schema_jims_index_space_state.

#ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_STATE_H
#define SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_STATE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef EXPLICIT_INDEX_SPACE_STATE_H
#include "SheafSystem/explicit_index_space_state.h"
#endif

#ifndef LIST_POOL_H
#include "SheafSystem/list_pool.h"
#endif

namespace sheaf
{
class index_space_handle;
class ij_product_structure;
}

namespace fiber_bundle
{

using namespace sheaf;

class section_space_schema_jims_index_space_handle;
class section_space_schema_jims_index_space_iterator;

///
/// An implementation class explicit_index_space_state for the jims id space
/// of the section space schema.
///
class SHEAF_DLL_SPEC section_space_schema_jims_index_space_state : public explicit_index_space_state
{

  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SPACE FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Create a new section space schema jims id space in the id space
  /// family xid_space at the next available id space index with name xname,
  /// base space id space xbase_space_id_space, fiber schema id space,
  /// xfiber_schema_id_space and section space schema product structure
  /// xsection_space_schema_product.
  /// Returns a handle to the id space created.
  ///
  static
  section_space_schema_jims_index_space_handle
  new_space(index_space_family& xid_spaces,
	    const std::string& xname,
	    const index_space_handle& xbase_space_id_space,
	    const index_space_handle& xfiber_schema_id_space,
	    const ij_product_structure& xsection_space_schema_product);

  ///
  /// Create a new section space schema jims id space in the id space
  /// family xid_space at id space index xid with name xname,
  /// base space id space xbase_space_id_space, fiber schema id space,
  /// xfiber_schema_id_space and section space schema product structure
  /// xsection_space_schema_product.
  /// Returns a handle to the id space created.
  ///
  static
  section_space_schema_jims_index_space_handle
  new_space(index_space_family& xid_spaces,
	    pod_type xid,
	    const std::string& xname,
	    const index_space_handle& xbase_space_id_space,
	    const index_space_handle& xfiber_schema_id_space,
	    const ij_product_structure& xsection_space_schema_product);

protected:

private:

  //@}


  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_STATE FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Default constructor
  ///
  section_space_schema_jims_index_space_state();

  ///
  /// Copy constructor; disabled.
  ///
  section_space_schema_jims_index_space_state(const section_space_schema_jims_index_space_state& xother) { };

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_jims_index_space_state();

private:

  //@}


  // ===========================================================
  /// @name SECTION SPACE SCHEMA INDEX SPACE FACET
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

  ///
  /// The base space jims id space.
  ///
  index_space_handle* _base_space;

  ///
  /// The fiber schema jims id space.
  ///
  index_space_handle* _fiber_schema;

  ///
  /// The product structure of the section space schema id space.
  ///
  ij_product_structure* _section_space_schema_product;

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

  ///
  /// The deep size of this.
  ///
  virtual size_type deep_size(bool xinclude_shallow) const;

protected:

  ///
  /// Assignment operator
  ///
  virtual section_space_schema_jims_index_space_state& operator=(const explicit_index_space_state& xother);

private:

  //@}


  // ===========================================================
  /// @name INDEX SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this space contains id xid.
  ///
  virtual bool contains(pod_type xid) const;

  ///
  /// True if this space contains an id equivalent to xid in the unglued hub id space.
  ///
  virtual bool contains_unglued_hub(pod_type xid) const;

  ///
  /// The pod index in this space equivalent to xid in the hub id space.
  ///
  virtual pod_type pod(pod_type xid) const;

  ///
  /// The pod index in the unglued hub id space equivalent to xid in this id space.
  ///
  virtual pod_type unglued_hub_pod(pod_type xid) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRODUCT STRUCTURE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates a new product structure for this id space by cloning the
  /// product structure, xproduct.
  ///
  virtual void new_product_structure(const abstract_product_structure& xproduct);

  ///
  /// Deletes the product structure for this id space.
  ///
  virtual void delete_product_structure();

  ///
  /// The product structure for this id space (const version).
  ///
  const ij_product_structure& product_structure() const;

  ///
  /// The product structure for this id space (mutable version).
  ///
  ij_product_structure& product_structure();

protected:

private:

  //@}


  // ===========================================================
  /// @name HANDLE POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of handles in the pool.
  ///
  static size_type handle_pool_ct();

  ///
  /// The deep size of the handle pool.
  ///
  static size_type handle_pool_deep_size();

  ///
  /// The id space handle with this state.
  ///
  virtual index_space_handle& get_id_space() const;

  ///
  /// Release the id space handle xid_space.
  ///
  virtual void release_id_space(index_space_handle& xid_space) const;

  ///
  /// True if and only if id space handle xid_space was allocated by
  /// the handle pool.
  ///
  virtual bool allocated_id_space(const index_space_handle& xid_space) const;

protected:

private:

  ///
  /// The handle pool.
  ///
  static list_pool<section_space_schema_jims_index_space_handle>& handles();

  //@}


  // ===========================================================
  /// @name ITERATOR POOL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of iterators in the pool.
  ///
  static size_type iterator_pool_ct();

  ///
  /// The deep size of the iterator pool.
  ///
  static size_type iterator_pool_deep_size();

  ///
  /// Allocates an id space iterator from the iterator pool.
  ///
  virtual index_space_iterator& get_iterator() const;

  ///
  /// Returns the id space iterator xitr to the iterator pool.
  ///
  virtual void release_iterator(index_space_iterator& xitr) const;

  ///
  /// True if and only if id space iterator xitr was allocated by
  /// the iterator pool.
  ///
  virtual bool allocated_iterator(const index_space_iterator& xitr) const;

protected:

private:

  ///
  /// Pool of iterators.
  ///
  static list_pool<section_space_schema_jims_index_space_iterator>& iterators();

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

  ///
  /// Virtual constructor; create a new instance of the same type at this.
  ///
  virtual section_space_schema_jims_index_space_state* clone() const;

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

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
/// The deep size of section_space_schema_jims_index_space_state& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const section_space_schema_jims_index_space_state& xn, bool xinclude_shallow = true);
  
} // end namespace sheaf

#endif // ifndef SECTION_SPACE_SCHEMA_JIMS_INDEX_SPACE_STATE_H
