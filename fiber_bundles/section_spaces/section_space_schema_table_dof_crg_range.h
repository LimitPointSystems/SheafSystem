
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
/// Interface for class section_space_schema_table_dof_crg_range

#ifndef SECTION_SPACE_SCHEMA_TABLE_DOF_CRG_RANGE_H
#define SECTION_SPACE_SCHEMA_TABLE_DOF_CRG_RANGE_H

#ifndef SHEAF_DLL_SPEC_H
#include "SheafSystem/sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_CRG_RANGE_H
#include "SheafSystem/section_space_schema_crg_range.h"
#endif

namespace sheaf
{
class poset_state_handle;
}

namespace fiber_bundle
{
  
using namespace sheaf;

class product_section_space_schema_crg_range;
class product_section_space_schema_poset;

///
/// Abstract emulator for a range of implicit section space schema members.
///
class SHEAF_DLL_SPEC section_space_schema_table_dof_crg_range : public section_space_schema_crg_range
{

  // ===========================================================
  /// @name SECTION_SPACE_SCHEMA_TABLE_DOF_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  section_space_schema_table_dof_crg_range();

  ///
  /// Destructor
  ///
  virtual ~section_space_schema_table_dof_crg_range();

  ///
  /// True if the product range has been initialized.
  ///
  bool product_range_initialized() const;

protected:

  ///
  /// Sets the product crg range.
  ///
  void initialize_product_range(product_section_space_schema_crg_range& xproduct_range);

  ///
  /// The product crg range.
  ///
  const product_section_space_schema_crg_range* _product_range;

private:

  //@}


  // ===========================================================
  // SECTION_SPACE_SCHEMA_CRG_RANGE FACET
  // ===========================================================
  //@{

public:

  using section_space_schema_crg_range::contains_member;

  ///
  /// True if this range contains the member with base space id xbase_space_id
  /// and fiber schema id xfiber_schema_id.
  ///
  virtual bool contains_member(pod_index_type xbase_space_id,
			       pod_index_type xfiber_schema_id) const;

  ///
  /// The tuple conversion from section space schema id xindex to the
  /// base space id xbase_space_id and fiber schema id xfiber_schema_id.
  ///
  virtual void tuple(pod_index_type xindex,
		     pod_index_type& xbase_space_id,
		     pod_index_type& xfiber_schema_id) const;

  ///
  /// The ordinal conversion from base space id xbase_space_id and
  /// fiber schema id xfiber_schema_id to section space schema id xindex.
  ///
  virtual void ordinal(pod_index_type xbase_space_id,
		       pod_index_type xfiber_schema_id,
		       pod_index_type& xindex) const;

protected:

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
  /// @name RANGE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The size for an instance created with parameter xhost.
  ///
  static void get_size(const product_section_space_schema_poset& xhost,
		       size_type& result);

  ///
  /// An iterator over the atoms in this range.
  ///
  virtual cover_set_iterator atoms() const;

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
  /// Iterator for lower (xlower true) or upper (xlower false) cover set
  /// of the member with index xmbr_index.
  ///
  virtual cover_set_iterator implicit_cover_iterator(bool xlower,
						     pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or upper (xlower false)
  /// cover set of the member with index xmbr_index is empty.
  ///
  virtual bool implicit_cover_is_empty(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// The number of members in the lower (xlower true) or
  /// upper (xlower false) cover set.
  ///
  virtual size_type implicit_cover_size(bool xlower, pod_index_type xmbr_index) const;

  ///
  /// True if and only if the lower (xlower true) or
  /// upper (xlower false) cover set contains xindex.
  ///
  virtual bool implicit_cover_contains_member(bool xlower,
					      pod_index_type xmbr_index,
					      pod_index_type xother_index) const;

  ///
  /// The first member of the lower (xlower true) or upper (xlower false) cover.
  ///
  virtual pod_index_type implicit_first_cover_member(bool xlower,
						     pod_index_type xmbr_index) const;

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  using implicit_crg_range::is_jim;

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  virtual bool is_jim(pod_index_type xmbr_index) const;

  using implicit_crg_range::dof_tuple_id;

  ///
  /// The dof tuple id of the member with index xmbr_index
  ///
  virtual const scoped_index& dof_tuple_id(pod_index_type xmbr_index) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const;

  ///
  /// The private data for this instance.
  ///
  virtual void get_implicit_private_data(block<pod_index_type>& xdata) const;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void put_implicit_private_data(const block<pod_index_type>& xdata);

private:

  //@}


  // ===========================================================
  /// @name FINIALIZE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Finialize the initialization of this crg range in the host xhost.
  ///
  virtual void finalize(poset_state_handle& xhost);

protected:

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const std::string& class_name() const;

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
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual section_space_schema_table_dof_crg_range* clone() const;

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

#endif // ifndef SECTION_SPACE_SCHEMA_TABLE_DOF_CRG_RANGE_H
