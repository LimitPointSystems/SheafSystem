
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
/// Interface for class section_space_schema_crg_range

#ifndef SECTION_SPACE_SCHEMA_CRG_RANGE_H
#define SECTION_SPACE_SCHEMA_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef IMPLICIT_CRG_RANGE_H
#include "implicit_crg_range.h"
#endif

namespace sheaf
{
class poset_state_handle;
}

namespace fiber_bundle
{
  
using namespace sheaf;

class base_space_poset;

///
/// Abstract emulator for a range of implicit section space schema members.
///
class SHEAF_DLL_SPEC section_space_schema_crg_range : public implicit_crg_range
{

  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  section_space_schema_crg_range();

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_crg_range();

  ///
  /// The base space for section spaces on this schema (mutable version).
  ///
  base_space_poset& base_space();

  ///
  /// The base space for section spaces on this schema (const version).
  ///
  const base_space_poset& base_space() const;

  ///
  /// True if the base space has been initialized.
  ///
  bool base_space_initialized() const;

  ///
  /// The fiber schema for section spaces on this schema (mutable version).
  ///
  poset_state_handle& fiber_schema();

  ///
  /// The fiber schema for section spaces on this schema (const version).
  ///
  const poset_state_handle& fiber_schema() const;

  ///
  /// True if the fiber schema has been initialized.
  ///
  bool fiber_schema_initialized() const;

  using implicit_crg_range::contains_member;

  ///
  /// True if this range contains the member with base space id xbase_space_id
  /// and fiber schema id xfiber_schema_id.
  ///
  virtual bool contains_member(pod_index_type xbase_space_id,
			       pod_index_type xfiber_schema_id) const = 0;

  ///
  /// The tuple conversion from section space schema id xindex to the
  /// base space id xbase_space_id and fiber schema id xfiber_schema_id.
  ///
  virtual void tuple(pod_index_type xindex,
		     pod_index_type& xbase_space_id,
		     pod_index_type& xfiber_schema_id) const = 0;

  ///
  /// The ordinal conversion from base space id xbase_space_id and
  /// fiber schema id xfiber_schema_id to section space schema id xindex.
  ///
  virtual void ordinal(pod_index_type xbase_space_id,
		       pod_index_type xfiber_schema_id,
		       pod_index_type& xindex) const = 0;

protected:

  ///
  /// Sets the base space for section spaces on this schema to xbase_space.
  ///
  void initialize_base_space(base_space_poset& xbase_space);

  ///
  /// Sets the fiber schema for section spaces on this schema to xfiber_schema.
  ///
  void initialize_fiber_schema(poset_state_handle& xfiber_schema);

  ///
  /// The base space for section spaces on this schema.
  ///
  base_space_poset* _base_space;

  ///
  /// The fiber schema for section spaces on this schema.
  ///
  poset_state_handle* _fiber_schema;

private:

  //@}


  // ===========================================================
  // IMPLICIT_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set of the member with index xmbr_index.
  /// is the domain of iterator xitr.
  ///
  virtual bool implicit_cover_contains_iterator(bool xlower,
						pod_index_type xmbr_index,
						const cover_set_iterator& xitr) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set contains exactly one member.
  ///
  virtual bool implicit_cover_is_singleton(bool xlower, pod_index_type xmbr_index) const;

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
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
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual section_space_schema_crg_range* clone() const;

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
 
} // end namespace fiber_bundle

#endif // ifndef SECTION_SPACE_SCHEMA_CRG_RANGE_H
