
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

// Interface for class section_evaluator

#ifndef SECTION_EVALUATOR_H
#define SECTION_EVALUATOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef FIBER_BUNDLE_H
#include "fiber_bundle.h"
#endif

#ifndef POD_TYPES_H
#include "pod_types.h"
#endif
  
namespace sheaf
{
template <typename T> class block;
}

namespace fiber_bundle
{

using namespace sheaf;

///
/// An abstract local section evaluator; 
/// a map from {local coordinates x dofs} to section value.
///
class SHEAF_DLL_SPEC section_evaluator : public any
{

  // ===========================================================
  /// @name SECTION_EVALUATOR FACET
  // ===========================================================
  //@{

public:
 
  // The following types are derived from the role the evaluators play
  // in the section space classes. The domain of an evaluator must be
  // a local chart of a base space and the range must be a fiber space.
  // Hence the coord type here must be chart_point::coord_type and the value
  // type here must be vd::value_type. Although it is tempting to make a
  // similar argument about the dof type, the sections and the fibers don't
  // actually share representations or dofs anywhere, so there is no reason
  // in principle they need to be the same type. In practice, of course,
  // everything is a double.

  ///
  /// The type of local coordinate;
  /// the scalar type for the local coordinate vector space.
  ///
  typedef chart_point_coord_type coord_type;

  ///
  /// The type of component in the value;
  /// the scalar type in the range vector space.
  ///
  typedef vd_value_type value_type;

  ///
  /// The type of degree of freedom.
  ///
  typedef sec_vd_dof_type dof_type;

  /// @todo revise the signatures of the functions in this class
  /// and all its descendants to properly distinguish between the
  /// above three types.

  ///
  /// Copy constructor.
  ///
  ///
  section_evaluator(const section_evaluator& xother);

  ///
  /// Destructor
  ///
  virtual ~section_evaluator();

protected:

  ///
  /// Default constructor
  ///
  ///
  section_evaluator();

private:

  //@}

  // ===========================================================
  /// @name DOMAIN FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// The base dimension; the dimension of the
  /// local coordinates (independent variable).
  ///
  virtual int db() const = 0;

  ///
  /// The local coordinates of the dof with local index xindex.
  ///
  virtual void local_coordinates(pod_index_type xindex,
                                 coord_type xresult[],
                                 size_type xresult_ub) const = 0;

  ///
  /// The local coordinates of the dof with local index xindex.
  ///
  void local_coordinates(pod_index_type xindex, block<coord_type>& xresult) const;

  ///
  /// The local coordinates at the center of the evaluator.
  ///
  virtual void center(coord_type xresult[], size_type xresult_ub) const;

  ///
  /// The local coordinates at the center of the evaluator.
  ///
  void center(block<coord_type>& xresult) const;

  ///
  /// True if the specified local coordinates are in the "standard" domain.
  ///
  virtual bool in_standard_domain(const dof_type xlocal_coords[],
                                  size_type xlocal_coords_ub) const = 0;

  ///
  /// True if the specified local coordinates are in the "standard" domain.
  ///
  bool in_standard_domain(const block<dof_type>& xlocal_coords) const;

protected:

private:

  //@}

  // ===========================================================
  /// @name EVALUATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The number of dofs required for each
  /// component of the dependent variable.
  ///
  virtual size_type dof_ct() const = 0;

  ///
  /// True if and only if the fiber dimension
  /// (number of components of the dependent variable)
  /// is variable.
  ///
  bool df_is_variable() const;
  
  ///
  /// The fiber dimension (number of components of dependent variable).
  ///
  virtual int df() const;

  ///
  ///  Value at a specified local_coordinate.
  ///  Single component version.
  ///
  virtual dof_type value_at_coord(const dof_type xdofs[],
                                  size_type xdofs_ub,
                                  const dof_type xlocal_coords[],
                                  size_type xlocal_coords_ub) const;

  ///
  ///  Value at a specified local_coordinate.
  ///  Single component version.
  ///
  dof_type value_at_coord(const block<dof_type>& xdofs,
                          const block<dof_type>& xlocal_coords) const;

  ///
  ///  Values at a specified local_coordinate.
  ///  Multiple component version.
  ///
  virtual void value_at_coord(const dof_type xdofs[],
                              size_type xdofs_ub,
                              const dof_type xlocal_coords[],
                              size_type xlocal_coords_ub,
                              dof_type xresult[],
                              size_type xresult_ub) const = 0;
  ///
  ///  Values at a specified local_coordinate.
  ///  Multiple component version.
  ///
  void value_at_coord(const block<dof_type>& xdofs,
                      const block<dof_type>& xlocal_coords,
                      block<dof_type>& xresult) const;
  ///
  /// The local coordinates of a point at which
  /// the field has the value xvalue.
  /// The dofs are assumed to be interleaved.
  ///
  virtual void coord_at_value(const dof_type xdofs[],
                              size_type xdofs_ub,
                              const dof_type xvalue[],
                              size_type xvalue_ub,
                              dof_type xlocal_coords[],
                              size_type xlocal_coords_ub) const = 0;

  ///
  /// The local coordinates of a point at which
  /// the field has the value xvalue.
  /// The dofs are assumed to be interleaved.
  ///
  void coord_at_value(const block<dof_type>& xdofs,
                      const block<dof_type>& xvalue,
                      block<dof_type>& xlocal_coords) const;
 
  ///
  /// The minimum value of the scalar or component section defined by xdofs.
  ///
  virtual dof_type min(const dof_type xdofs[], size_type xdofs_ub) const;

  ///
  /// The minimum value of the scalar or component section defined by xdofs.
  ///
  dof_type min(const block<dof_type>& xdofs) const;

  ///
  /// The minimum value of the vector section defined by xdofs.
  ///
  virtual void min(const dof_type xdofs[],
                   size_type xdofs_ub,
                   dof_type xresult[],
                   size_type xresult_ub) const;

  ///
  /// The minimum value of the vector section defined by xdofs.
  ///
  void min(const block<dof_type>& xdofs, block<dof_type>& xresult) const;

  ///
  /// The maximum value of the scalar or component section defined by xdofs.
  ///
  virtual dof_type max(const dof_type xdofs[], size_type xdofs_ub) const;

  ///
  /// The maximum value of the scalar or component section defined by xdofs.
  ///
  dof_type max(const block<dof_type>& xdofs) const;

  ///
  /// The maximum value of the vector section defined by xdofs.
  ///
  virtual void max(const dof_type xdofs[],
                   size_type xdofs_ub,
                   dof_type xresult[],
                   size_type xresult_ub) const;

  ///
  /// The maximum value of the vector section defined by xdofs.
  ///
  void max(const block<dof_type>& xdofs, block<dof_type>& xresult) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:
 
  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this.
  ///
  virtual section_evaluator* clone() const = 0;

  ///
  /// Assignment operator.
  ///
  ///
  virtual section_evaluator& operator=(const section_evaluator& xother);

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

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The deep size of the referenced object of type section_evaluator.
/// if xinclude_shallow, add the sizeof xpath to the result.
///
size_t
SHEAF_DLL_SPEC
deep_size(const section_evaluator& xe, bool xinclude_shallow = true);
 

} // namespace fiber_bundle

#endif // ifndef SECTION_EVALUATOR_H
