

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class structured_block

#ifndef STRUCTURED_BLOCK_H
#define STRUCTURED_BLOCK_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef HOMOGENEOUS_BLOCK_H
#include "homogeneous_block.h"
#endif

#ifndef CHART_POINT_H
#include "chart_point.h"
#endif

#ifndef STD_CMATH_H
#include "std_cmath.h"
#endif

namespace fiber_bundle
{
  
using namespace sheaf;

class chart_point_3d;

///
/// A client handle for a base space member which represents
/// a homgeneous collection of local cells.
///
class SHEAF_DLL_SPEC structured_block : public homogeneous_block
{
  // ===========================================================
  /// @name HOST FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// The path of the schema required by this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// The path of the schema required by this.
  ///
  virtual const poset_path& schema_path() const;

  ///
  /// Creates the standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  ///
  /// Manual, shallow factory method; creates a new host poset for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path.
  ///
  static host_type& new_host(namespace_type& xns, 
			     const poset_path& xhost_path, 
			     const poset_path& xschema_path, 
			     int xmax_db,
			     bool xauto_access);

  ///
  /// Auto, deep factory method; creates a new host poset and any prerequisite posets
  /// for members of this type. The poset is created in namespace xns with path xhost_path
  /// and schema specified by standard_schema_path().
  ///
  static host_type& new_host(namespace_type& xns,
			     const poset_path& xhost_path,
			     int xmax_db,
			     bool xauto_access);
  

protected:

private:

  //@}


  // ===========================================================
  /// @name STRUCTURED_BLOCK FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor; creates a new, unattached structured_block handle.
  ///
  structured_block();

  ///
  /// Destructor; deletes a poset member and its attached state, if any.
  ///
  virtual ~structured_block();

protected:

  ///
  /// Initializes handle data members when attaching
  /// to a different member in a different host.
  ///
  virtual void init_handle_data_members();

  ///
  /// The client id space for the elements subposet.
  ///
  index_space_handle* _elements_id_space;

  ///
  /// Transforms local coordinate xcoord from block local to zone local.
  ///
  void refine_coordinate(chart_point_coord_type& xcoord,
                         scoped_index::pod_type& xchart_id,
                         size_type xchart_id_ub) const;

  static inline double TOLERANCE()
  {
    static const double result = 10.0*numeric_limits<double>::epsilon();
    return result;
  };

  ///
  /// True if x2 is close enough to x1 to be considered equal.
  ///
  static inline bool is_close_enough(double x1, double x2)
  {
    return (std::fabs(x2 - x1) <= TOLERANCE());
  };

private:

  //@}


  // ===========================================================
  /// @name LOCAL_BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

  /// @issue In principle, this class inherits local_base_space_member.
  /// However, this would require multiple inheritance, which we have
  /// decided not to use. So the features of local_base_space_member
  /// are simply duplicated in this class.

  ///
  /// A chart point in the direct refinement of this which is
  /// the same as xpt in this; auto-allocated version.
  ///
  chart_point* refine_point(const chart_point& xpt) const;

  ///
  /// A chart point in the direct refinement of this which is
  /// the same as xpt in this; pre-allocated version
  ///
  virtual void refine_point_pa(const chart_point& xpt, chart_point& result) const = 0;

  ///
  /// All chart points in the direct refinement of this which are
  /// the same as xpt in this; pre-allocated version.
  /// Note that if xpt lies on a zone boundary in the direct refinement,
  /// it lies in more than one zone.
  ///
  virtual void refine_point_pa(const chart_point& xpt,
                               block<chart_point_3d>& result) const = 0;

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; auto-allocated version
  ///
  chart_point* unrefine_point(const chart_point& xpt) const;

  ///
  /// The point in this which is the same as xpt in
  /// the direct refinement of this; pre-allocated version
  ///
  virtual void unrefine_point_pa(const chart_point& xpt, chart_point& result) const = 0;

  ///
  /// Inserts the standard refinement of this into its lower cover
  /// and changes this from a jim to a jrm.
  ///
  virtual void refine() = 0;

  ///
  /// Removes the standard refinement of this from its lower cover
  /// and changes this from a jrm to a jim.
  ///
  virtual void unrefine() = 0;

  ///
  /// Inserts the standard simplex refinement of this
  /// into its lower cover and changes this from a jim to a jrm.
  ///
  virtual void simplify() = 0;

  ///
  /// Removes the standard simplex refinement of this
  /// from its lower cover and changes this from a jrm to a jim.
  ///
  virtual void unsimplify() = 0;

protected:

private:

  //@}


  // ===========================================================
  /// @name HOMOGENEOUS_BLOCK FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name BASE_SPACE_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name TOTAL_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name ABSTRACT_POSET_MEMBER FACET
  // ===========================================================
  //@{

public:

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual structured_block* clone() const = 0;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline structured_block* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<structured_block*>(homogeneous_block::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  // ===========================================================
  /// @name ORDERING RELATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// The largest member which is join-equivalent to this
  ///
  inline structured_block* greatest_jem() const
  {
    return static_cast<structured_block*>(base_space_member::greatest_jem());
  };

  ///
  /// The smallest member which is join-equivalent to this
  ///
  inline structured_block* least_jem() const
  {
    return static_cast<structured_block*>(base_space_member::least_jem());
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// poset join of this with other, auto-, pre-, and self-allocated versions
  /// the poset join is the least upper bound in the poset
  ///
  inline structured_block* p_join(abstract_poset_member* other) const
  {
    return static_cast<structured_block*>(base_space_member::p_join(other));
  };

  ///
  /// poset meet of this with other, auto-, pre-, and self-allocated versions
  /// the poset meet is the greatest lower bound in the poset
  ///
  inline structured_block* p_meet(abstract_poset_member* other)
  {
    return static_cast<structured_block*>(base_space_member::p_meet(other));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name LATTICE ALGEBRA FACET
  // ===========================================================
  //@{

public:

  ///
  /// lattice join of this with other, auto-, pre-, and self-allocated versions
  /// the lattice join is the least upper bound in the lattice generated by the
  /// jims in the poset
  ///
  inline structured_block* l_join(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block*>(base_space_member::l_join(other, xnew_jem));
  };

  ///
  /// lattice meet of this with other, auto-, pre-, and self-allocated versions
  /// the lattice meet is the greatest lower bound in the lattice generated by
  /// the jims in the poset
  ///
  inline structured_block* l_meet(abstract_poset_member* other, bool xnew_jem = true)
  {
    return static_cast<structured_block*>(base_space_member::l_meet(other, xnew_jem));
  };

  ///
  /// lattice pseudo-complement of this, auto-, pre- and self allocated versions
  /// The lattice pseudo-complement is the largest lattice member m for which
  /// this.l_meet(m) = 0
  ///
  inline structured_block* l_not(bool xnew_jem = true) const
  {
    return static_cast<structured_block*>(base_space_member::l_not(xnew_jem));
  };

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  virtual structured_block& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator
  ///
  structured_block& operator=(const structured_block& xother);

protected:

private:

  //@}
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The deep size of the referenced object of type structured_block.
/// if xinclude_shallow, add the sizeof x0 to the result.
///
SHEAF_DLL_SPEC size_t deep_size(const structured_block& x0, bool xinclude_shallow = true);

 
} // namespace fiber_bundle


#endif // STRUCTURED_BLOCK_H
