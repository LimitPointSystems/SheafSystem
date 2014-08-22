
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
/// Interface for class sec_vd.

#ifndef SEC_VD_H
#define SEC_VD_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

#ifndef SEC_TUPLE_H
#include "sec_tuple.h"
#endif

#ifndef COM_LIMITPOINT_FIBER_BUNDLE_AT0_H
#include "ComLimitPoint/fiber_bundle/at0.h"
#endif
 
namespace fiber_bundle
{

class at0;
class at0_lite;
class chart_point;
class sec_at0;
class sec_vd_space;
class vd;
class vd_lite;

//==============================================================================
// CLASS SEC_VD
//==============================================================================

///
/// A section of a fiber bundle with a d-dimensional vector space fiber.
///
class SHEAF_DLL_SPEC sec_vd : public sec_tuple
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_VD
  // ===========================================================
  //@{

public:

  /// Typedefs:

  ///
  /// The type of host poset.
  ///
  typedef sec_vd_space host_type;

  ///
  /// The fiber type.
  ///
  typedef vd fiber_type;

  ///
  /// The type of local coordinate;
  /// the scalar type for the local coordinate vector space.
  ///
  typedef chart_point_coord_type coord_type;

  ///
  /// The type of component in the value;
  /// the scalar type in the fiber space.
  ///
  typedef sec_vd_value_type value_type;

  ///
  /// The type of degree of freedom.
  ///
  typedef sec_vd_dof_type dof_type;

  ///
  /// The scalar type in the section space.
  ///
  typedef sec_at0 scalar_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and table attribute scalar_space_path specified by xscalar_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xscalar_space_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name VD FACET OF CLASS SEC_VD
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_vd();

  ///
  /// Creates a new sec_vd handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_vd(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_vd handle attached to the member state with id xid
  /// in xhost.
  ///
  sec_vd(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_vd handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_vd(const sec_rep_space* xhost, const std::string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_vd(const namespace_poset* xnamespace,
         const poset_path& xpath,
         bool xauto_access = true);

  ///
  /// Creates a new sec_vd handle attached to the same state as xother.
  ///
  explicit sec_vd(sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_vd(sec_rep_space* xhost,
         section_dof_map* xdof_map = 0,
         bool xauto_access = true);

  ///
  /// Creates a new sec_vd handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_vd(sec_rep_space* xhost,
         abstract_poset_member& xbase_mbr,
         int xbase_version = CURRENT_HOST_VERSION,
         bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(xother).
  ///
  virtual sec_vd& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_vd& operator=(const sec_vd& xother);

  ///
  /// Assignment operator.
  ///
  sec_vd& operator=(const vd& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_vd& operator=(const vd_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_vd();

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

  ///
  /// The fiber dimension.
  ///
  virtual int d() const;

  ///
  /// The fiber dimension; auto-access version.
  ///
  virtual int d(bool xauto_access) const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying scalar space; auto-access version.
  ///
  poset_path scalar_space_path(bool xauto_access) const;

  ///
  /// True if and only if this is a vector (as opposed to a covector).
  ///
  virtual bool is_vector(bool xauto_access) const;

  ///
  /// Sets is_vector true.
  ///
  virtual void put_is_vector(bool xauto_access);

  ///
  /// True if and only if this is a covector.
  ///
  virtual bool is_covector(bool xauto_access) const;;

  ///
  /// Sets is_covector true.
  ///
  virtual void put_is_covector(bool xauto_access);

  ///
  /// Ith component of section
  ///
  scalar_type* comp(int i) const;

  ///
  /// Sets ith component of section
  ///
  void set_comp(int i, scalar_type* xcomponent);

  ///
  /// Value of the field at xpt, auto-allocated version.
  ///
  vd* value_at_point(const chart_point& xpt, bool xauto_access = true) const;

  ///
  /// Value of the field at xpt, pre-allocated version.
  ///
  virtual void value_at_point_pa(const chart_point& xpt,
                                 vd& xresult,
                                 bool xauto_access = true) const;

  ///
  /// Value of the field at xpt, unattached version.
  ///
  virtual void value_at_point_ua(const chart_point& xpt,
                                 value_type* xresult,
                                 size_type xresult_ub,
                                 bool xauto_access = true) const;

  ///
  /// @deprecated no longer supported.
  ///
  virtual int dof_packet_ub();

  ///
  /// Copies the entire dof tuple into xbuf
  ///
  void dof_tuple(dof_type* xbuf, int xbuflen) const;

  ///
  /// Virtual constructor; makes a new handle of the same type as this,
  /// attached to a copy of the state of this.
  ///
  sec_vd* deep_copy(bool xauto_access);

  ///
  /// Copies the dofs of this to xother.
  ///
  void deep_copy(sec_vd& xother, bool xauto_access);

protected:

  ///
  /// Creates a new component for attach_handle_data_members.
  /// A "virtual constructor" for components.
  ///
  virtual sec_tuple::scalar_type* new_comp();

private:

  //@}

  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_VD
  //============================================================================
  //@{

public:

protected:

private:

  //@}
 

  //============================================================================
  /// @name MULTISECTION FACET
  //============================================================================
  //@{

  ///
  /// Unifies this multisection into result using the painters algorithm
  /// (result at disccretization point is value of last branch
  /// overlapping that point); auto-allocated version.
  ///
  sec_vd* unify(bool xauto_access);

  ///
  /// Unifies this multisection into xresult using the painters algorithm
  /// (result at disccretization point is value of last branch
  /// overlapping that point); pre-allocated version.
  ///
  void unify(sec_vd& xresult, bool xauto_access);

protected:

private:

  //@}

  //============================================================================
  /// @name NEW DOF ACCESS FACET
  //============================================================================
  //@{

public:

  using sec_tuple::get_fiber;
  
  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  void get_fiber(pod_index_type xdisc_id, vd_lite& xfiber) const;

  ///
  /// Sets xfiber to the fiber referred to by discretization id xdisc_id.
  ///
  void get_fiber(const scoped_index& xdisc_id, vd_lite& xfiber, bool xauto_access) const;

  using sec_tuple::put_fiber;
  
  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void put_fiber(pod_index_type xdisc_id, const vd_lite& xfiber);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void put_fiber(const scoped_index& xdisc_id, const vd_lite& xfiber, bool xauto_access);

  using sec_tuple::force_fiber;
  
  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void force_fiber(pod_index_type xdisc_id, const vd_lite& xfiber);

  ///
  /// Sets the fiber referred to by discretization id xdisc_id to xfiber.
  ///
  void force_fiber(const scoped_index& xdisc_id, const vd_lite& xfiber, bool xauto_access);

protected:

private:

  //@} 

  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_VD
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const std::string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const std::string& static_class_name();

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual sec_vd* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_vd* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_vd*>(sec_tuple::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}
 

  // ===========================================================
  /// @name HOST POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The poset this is a member of.
  ///
  host_type* host() const;

  ///
  /// True if other conforms to host.
  ///
  virtual bool host_is_ancestor_of(const poset_state_handle* other) const;

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_VD
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Clsss invariant.
  ///
  bool invariant() const;

protected:

private:

  //@} 

}; // end of class sec_vd


//==============================================================================
// NON-MEMBER CLASSES
//==============================================================================

//==============================================================================
// TENSOR SECTION TRAITS
//==============================================================================

// Forward declarations needed for specialization:

class sec_tp;
class sec_t2;
class sec_t3;
class sec_t4;
class sec_atp;
class sec_at2;
class sec_at3;
class sec_stp;
class sec_st2;
class sec_st3;
class sec_st4;

///
/// Tensor types of degree P over VECTOR_TYPE.
/// Must be specialized for every supported
/// combination of VECTOR_TYPE and P.
///
template <int P, typename VECTOR_TYPE>
class tensor_section_traits
{
public:
  ///
  /// Type of general tensor of degree P over VECTOR_TYPE.
  ///
  typedef void tp_type;

  ///
  /// Type of antisymmetric tensor of degree P over VECTOR_TYPE.
  ///
  typedef void atp_type;

  ///
  /// Type of symmetric tensor of degree P over VECTOR_TYPE.
  ///
  typedef void stp_type;
};

///
/// Tensor types of degree P over sec_vd; partial specialization.
///
template <int P>
class tensor_section_traits<P, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree P over sec_vd.
  ///
  typedef sec_tp tp_type;

  ///
  /// Type of antisymmetric tensor of degree P over sec_vd.
  ///
  typedef sec_atp atp_type;

  ///
  /// Type of symmetric tensor of degree P over sec_vd.
  ///
  typedef sec_stp stp_type;
};

///
/// Tensor types of degree 0 over sec_vd; full specialization.
///
template <>
class tensor_section_traits<0, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree 0 over sec_vd.
  ///
  typedef at0 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 0 over sec_vd.
  ///
  typedef at0 atp_type;

  ///
  /// Type of symmetric tensor of degree 0 over sec_vd.
  ///
  typedef at0 stp_type;
};

///
/// Tensor types of degree 1 over sec_vd; full specialization.
///
template <>
class tensor_section_traits<1, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree 1 over sec_vd.
  ///
  typedef sec_vd tp_type;

  ///
  /// Type of antisymmetric tensor of degree 1 over sec_vd.
  ///
  typedef sec_vd atp_type;

  ///
  /// Type of symmetric tensor of degree 1 over sec_vd.
  ///
  typedef sec_vd stp_type;
};

///
/// Tensor types of degree 2 over sec_vd; full specialization.
///
template <>
class tensor_section_traits<2, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree 2 over sec_vd.
  ///
  typedef sec_t2 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 2 over sec_vd.
  ///
  typedef sec_at2 atp_type;

  ///
  /// Type of symmetric tensor of degree 2 over sec_vd.
  ///
  typedef sec_st2 stp_type;
};

///
/// Tensor types of degree 3 over sec_vd; full specialization.
///
template <>
class tensor_section_traits<3, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree 3 over sec_vd.
  ///
  typedef sec_t3 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 3 over sec_vd.
  ///
  typedef sec_at3 atp_type;

  ///
  /// Type of symmetric tensor of degree 3 over sec_vd.
  ///
  typedef sec_st3 stp_type;
};

///
/// Tensor types of degree 4 over sec_vd; full specialization.
///
template <>
class tensor_section_traits<4, sec_vd>
{
public:
  ///
  /// Type of general tensor of degree 4 over sec_vd.
  ///
  typedef sec_t4 tp_type;

  ///
  /// Type of antisymmetric tensor of degree 4 over sec_vd.
  ///
  typedef void atp_type;
  //typedef sec_at4 atp_type;

  ///
  /// Type of symmetric tensor of degree 4 over sec_vd.
  ///
  typedef sec_st4 stp_type;
};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The deep size of the referenced object of type sec_vd.
/// if xinclude_shallow, add the sizeof x0 to the result.
///
SHEAF_DLL_SPEC size_t deep_size(const sec_vd& x0, bool xinclude_shallow = true);

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a d-dimensional vector space fiber.
///
namespace sec_vd_algebra
{

///
/// x0 add x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void add(const sec_vd& x0, const sec_vd& x1, sec_vd& xresult,
			bool xauto_access);

///
/// x0 add_equal x1 (self-allocated version);
/// synonym for add(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void add_equal(sec_vd& xresult, const sec_vd& xother, bool xauto_access);

///
/// x0 subtract x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void subtract(const sec_vd& x0, const sec_vd& x1, sec_vd& xresult,
			     bool xauto_access);

///
/// x0 subtract_equal x1 (self-allocated version);
/// synonym for subtract(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void subtract_equal(sec_vd& xresult, const sec_vd& xother, bool xauto_access);

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// x0 multiplied by x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void multiply(const sec_vd& x0, const sec_at0& x1, sec_vd& xresult,
			     bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// xresult multiply_equal xresult (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void multiply_equal(sec_vd& xresult, const sec_at0& xother, bool xauto_access);

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// x0 multiplied by x1 (a constant) (pre-allocated version).
///
SHEAF_DLL_SPEC void multiply(const sec_vd& x0, const vd_value_type& x1, sec_vd& xresult,
			     bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// xresult multiply_equal xresult (pre-allocated version);
/// synonym for multiply(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void multiply_equal(sec_vd& xresult, const vd_value_type& xother,
				   bool xauto_access);

///
/// x0 divided by x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void divide(const sec_vd& x0, const sec_at0& x1, sec_vd& xresult,
			   bool xauto_access);

///
/// xresult divide_equal xresult (pre-allocated version);
/// synonym for  divide(xresult, xother, xresult, xauto_access).
///
SHEAF_DLL_SPEC void divide_equal(sec_vd& xresult, const sec_at0& xother, bool xauto_access);

///
/// x0 divided by x1 (a constant) (pre-allocated version).
///
SHEAF_DLL_SPEC void divide(const sec_vd& x0, const vd_value_type& x1, sec_vd& xresult,
			   bool xauto_access);

///
/// xresult divide_equal xresult (pre-allocated version);
/// synonym for divide(xresult, xresult, xresult, xauto_access).
///
SHEAF_DLL_SPEC void divide_equal(sec_vd& xresult, const vd_value_type& xother,
				 bool xauto_access);

///
/// Contraction of vector xvector on covector xcovector
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void contract(const sec_vd& xvector, const sec_vd& xcovector, sec_at0& xresult,
			     bool xauto_access);

//==============================================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Maximum (pre-allocated version).
///
SHEAF_DLL_SPEC void max(const sec_vd& x0, vd_lite& xresult, bool xauto_access);

///
/// Maximum (auto-allocated version).
///
SHEAF_DLL_SPEC vd_lite* max(const sec_vd& x0, bool xauto_access);

///
/// Minimum (pre-allocated version).
///
SHEAF_DLL_SPEC void min(const sec_vd& x0, vd_lite& xresult, bool xauto_access);

///
/// Minimum (auto-allocated version).
///
SHEAF_DLL_SPEC vd_lite* min(const sec_vd& x0, bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Extrema (pre-allocated version).
///
SHEAF_DLL_SPEC void extrema(const sec_vd& x0, vd_lite& xmin, vd_lite& xmax, bool xauto_access);

/// $$SCRIBBLE This function is called from point_locator::update_domain
///            in Shell_components.  We continue to provide it here
///            until we can eliminate it.

///
/// Extrema (pre-allocated version).
///
SHEAF_DLL_SPEC void extrema(const sec_vd& x0,
			    sec_vd_value_type xmin[], size_type xmin_ub,
			    sec_vd_value_type xmax[], size_type xmax_ub);

//==============================================================================

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// Assignment to another section; makes x0 have 
/// the same value as x1 on the meet of their bases.
///
SHEAF_DLL_SPEC void assign(sec_vd& x0, const sec_vd& x1, bool xauto_access);

///
/// Assignment to a constant fiber.
///
SHEAF_DLL_SPEC void assign(sec_vd& x0, const vd_lite& x1, bool xauto_access);

///
/// Assignment to a scalar constant.
///
SHEAF_DLL_SPEC void assign(sec_vd& x0, const vd_value_type& xvalue, bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN


//==============================================================================
// BINARY AND UNARY OPERATORS.
//==============================================================================

///
/// Binary operator.
///
template <typename S0, typename S1, typename SR, typename F>
void binary_op(const S0& x0, const S1& x1, SR& xresult, F xfunctor,
               bool xauto_access);

///
/// Binary operator.
///
template <typename S0, typename SR, typename F>
void binary_op(const S0& x0, const vd_value_type& x1, SR& xresult, F xfunctor,
               bool xauto_access);

///
/// Unary operator.
///
template <typename S0, typename SR, typename F>
void unary_op(const S0& x0, SR& xresult, F xfunctor,
              bool xauto_access);

///
/// Unary operator.
///
template <typename S0, typename F>
void unary_op(S0& x0, const vd_value_type& x1, F xfunctor,
              bool xauto_access);

///
/// Unary operator (has 2 return sections).
///
template <typename S0, typename SR, typename F>
void unary_op(const S0& x0, SR& xresult1, SR& xresult2, F xfunctor,
              bool xauto_access);

} // namespace sec_vd_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_VD_H

