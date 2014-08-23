
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
/// Interface for class property_disc_iterator


#ifndef COM_LIMITPOINT_FIELDS_PROPERTY_DISC_ITERATOR_H
#define COM_LIMITPOINT_FIELDS_PROPERTY_DISC_ITERATOR_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef COM_LIMITPOINT_SHEAF_DEPTH_FIRST_ITERATOR_H
#include "ComLimitPoint/sheaf/depth_first_iterator.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SEC_VD_H
#include "ComLimitPoint/fiber_bundle/sec_vd.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_SECTION_ITERATION_STATE_H
#include "ComLimitPoint/fiber_bundle/section_iteration_state.h"
#endif

namespace fields
{

using namespace sheaf;
using namespace fiber_bundle;
 
class field_vd;

///
/// Abstract iterator over the discretization of the property
/// section of a field_vd. Concurrently traverses the schema of both the coordinates
/// and  property sections of a field, returning to the client
/// at each property discretization member, with enough context
/// to evaluate the coordinate section at the property discretization point.
///
class SHEAF_DLL_SPEC property_disc_iterator : public depth_first_iterator
{

  // ===========================================================
  /// @name PROPERTY_DISC_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an iterator appropriate for xcoords and xprop.
  ///
  static property_disc_iterator*
  new_property_disc_iterator(const section_space_schema_member& xcoords_schema,
                             const section_space_schema_member& xprop_schema);

  ///
  /// Destructor.
  ///
  ~property_disc_iterator();

  ///
  /// The coordinates field schema member which is being iterated over.
  ///
  const section_space_schema_member& coordinates_schema() const;

  ///
  /// The property field schema member which is being iterated over.
  ///
  const section_space_schema_member& property_schema() const;

  ///
  /// The base space shared by both schema.
  ///
  const base_space_poset& base_space() const;

  ///
  /// The evaluation subposet for the coordinates.
  ///
  const subposet& coordinates_evaluation() const;

  ///
  /// The evaluation subposet for the property.
  ///
  const subposet& property_evaluation() const;

  ///
  /// The dimension of the current evaluation member.
  ///
  int db() const;

  ///
  /// The type id of the current member.
  ///
  pod_index_type type_id() const;

  ///
  /// The type name of the current member.
  ///
  std::string type_name() const;

  ///
  /// The coordinate field evaluator associated
  /// with the current evaluation member.
  ///
  section_evaluator& coordinate_evaluator() const;

  ///
  /// The property field evaluator associated
  /// with the current evaluation member.
  ///
  section_evaluator& property_evaluator() const;

  ///
  /// The coordinate discretization members in
  /// the downset of the current evaluation member.
  ///
  const block<discretization_context>& coordinate_discretization_members() const;

  ///
  /// The property discretization members in
  /// the downset of the current evaluation member.
  ///
  const block<discretization_context>& property_discretization_members() const;

  ///
  /// The gets the values of xsec at the property discretization points.
  ///
  virtual void get_prop_disc_values(const sec_vd& xsec) = 0;


protected:

  ///
  /// Default constructor.
  ///
  property_disc_iterator() {};

  ///
  /// Copy constructor; disabled.
  ///
  property_disc_iterator(const property_disc_iterator& xother) {};

  ///
  /// Initializes this for iteration of type xorder over the schema of xfield.
  ///
  void initialize_iteration(const field_vd& xfield, order_type xorder);

  ///
  /// Initializes this for iteration of type xorder over
  /// xcoordinates_schema and xproperty_schema.
  ///
  void initialize_iteration(const section_space_schema_member& xcoordinates_schema,
                            const section_space_schema_member& xproperty_schema,
                            order_type xorder);

  ///
  /// Descriptor for coordinate section iteration.
  ///
  section_iteration_state _coord_state;

  ///
  /// Descriptor for property section iteration.
  ///
  section_iteration_state _prop_state;

  ///
  /// Relative depth flags type.
  ///
  struct SHEAF_DLL_SPEC depth_flags_type
  {
    bool coord_eval;
    bool coord_disc;
    bool prop_eval;
    bool prop_disc;

    depth_flags_type& operator=(bool xvalue)
    {
      coord_eval = xvalue;
      coord_disc = xvalue;
      prop_eval  = xvalue;
      prop_disc  = xvalue;

      return(*this);
    };
  };

  ///
  /// True if current iteration is a member of the
  /// subposet associated with the flag.
  ///
  depth_flags_type _at;

  ///
  /// True if current iteration is above the
  /// subposet associated with the flag.
  ///
  depth_flags_type _above;

  //@}


  // ===========================================================
  /// @name DEPTH_FIRST_ITERATOR FACET
  // ===========================================================
  //@{

public:

  ///
  /// Force the iterator to be done.
  ///
  virtual void force_is_done();

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Make a new instance of the same type as this
  ///
  virtual property_disc_iterator* clone() const = 0;

  ///
  /// The class invariant.
  ///
  bool invariant() const;

  //@}

};
 
} // namespace fields

#endif // ifndef COM_LIMITPOINT_FIELDS_PROPERTY_DISC_ITERATOR_H
