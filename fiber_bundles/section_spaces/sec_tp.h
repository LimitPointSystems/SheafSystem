
// $RCSfile: sec_tp.h,v $ $Revision: 1.16 $ $Date: 2013/03/13 00:58:51 $

// $Name: HEAD $
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_tp

#ifndef SEC_TP_H
#define SEC_TP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_VD_H
#include "sec_vd.h"
#endif

#ifndef TP_H
#include "tp.h"
#endif

namespace fiber_bundle
{

class sec_at1;
class sec_tp_space; 

//==============================================================================
// CLASS SEC_TP
//==============================================================================

///
/// A section of a bundle with fiber type tp.
///
class SHEAF_DLL_SPEC sec_tp : public sec_vd
{
  //============================================================================
  /// @name TP FACET OF CLASS SEC_TP
  //============================================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef sec_tp_space host_type;

  ///
  /// The type of the underlying vector space.
  ///
  typedef sec_at1 vector_space_type;

  ///
  /// The fiber type.
  ///
  typedef tp fiber_type;

  ///
  /// Default constructor.
  ///
  sec_tp();

  ///
  /// Creates a new sec_tp handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_tp(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_tp handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_tp(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_tp handle attached to the member state with name xname
  /// in xhost.
  ///
  sec_tp(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_tp(const namespace_poset* xnamespace,
         const poset_path& xpath,
         bool xauto_access = true);

  ///
  /// Creates a new sec_tp handle attached to the same state as xother.
  ///
  explicit sec_tp(sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_tp(sec_rep_space* xhost,
         section_dof_map* xdof_map = 0,
         bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_tp(sec_rep_space* xhost,
         abstract_poset_member& xbase_mbr,
         int xbase_version = CURRENT_HOST_VERSION,
         bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_tp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_tp& operator=(const sec_tp& xother);

  ///
  /// Assignment operator.
  ///
  sec_tp& operator=(const tp& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_tp& operator=(const tp_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_tp();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

  ///
  /// The degree of the tensors in host(); 
  /// the sum of the contravariant and covariant degrees.
  ///
  virtual int p() const;

  ///
  /// The degree of the tensors in host()
  /// (auto-access version).
  ///
  int p(bool xauto_access) const;

  ///
  /// Dimension of the underlying vector space.
  ///
  virtual int dd() const;

  ///
  /// Dimension of the underlying vector space (auto-access version).
  ///
  virtual int dd(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space, auto access version.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// The underlying vector space.
  ///
  virtual sec_tp_space& vector_space() const;

  ///
  /// The underlying vector space, auto access version.
  ///
  virtual sec_tp_space& vector_space(bool xauto_access) const;

  ///
  ///  Create a standard tensor space name.
  ///
  static const string create_tensor_space_name(const string& xvector_space_name, const string& xname);

  ///
  /// The variance.
  ///
  virtual tensor_variance variance(bool xauto_access) const;

  ///
  /// The variance of the xi-th tensor index position;
  /// true if covariant, false if contravariant.
  ///
  virtual bool variance(int xi, bool xauto_access) const;

  ///
  /// Sets the variance to xvariance.
  ///
  void put_variance(const tensor_variance& xvariance, bool xauto_access);

  ///
  /// Sets the variance of the xi-th index to xvariance.
  ///
  void put_variance(int xi, bool xvariance, bool xauto_access);
    
  ///
  /// True if and only if all tensor index positions are covariant.
  ///
  virtual bool is_covariant(bool xauto_access) const;
    
  ///
  /// True if and only if the xi-th tensor index position is covariant.
  ///
  virtual bool is_covariant(int xi, bool xauto_access) const;
   
  ///
  /// Sets all tensor index positions to covariant.
  ///
  virtual void put_is_covariant(bool xauto_access);
  
  ///
  /// Sets the variance of the xi-th tensor index position to covariant.
  ///
  void put_is_covariant(int xi, bool xauto_access);
 
  ///
  /// True if and only if all tensor index positions are contravariant.
  ///
  virtual bool is_contravariant(bool xauto_access) const;
 
  ///
  /// True if and only if the xi-th tensor index position is contravariant.
  ///
  virtual bool is_contravariant(int xi, bool xauto_access) const;
   
  ///
  /// Sets all tensor index positions to contravariant.
  ///
  virtual void put_is_contravariant(bool xauto_access);  
  
  ///
  /// Sets the variance of the xi-th tensor index position to contravariant.
  ///
  void put_is_contravariant(int xi, bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_TP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_TP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_TP
  //============================================================================
  //@{

public:

  ///
  /// The name of this class.
  ///
  virtual const string& class_name() const;

  ///
  /// The name of this class.
  ///
  static const string& static_class_name();

  ///
  /// Make a new handle, no state instance of current
  ///
  virtual sec_tp* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_tp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_tp*>(sec_vd::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  // ===========================================================
  /// @name POSET_COMPONENT FACET
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
  /// @name ANY FACET OF CLASS SEC_TP
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// True if xother conforms to current.
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a fiber type tp.
///
namespace sec_tp_algebra
{

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void alt(const sec_tp& x0, sec_atp& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void sym(const sec_tp& x0, sec_stp& xresult, bool xauto_access);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version).
///
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xq.
///
SHEAF_DLL_SPEC void contract(const sec_tp& x0, int xp, int xq, sec_tp& xresult,
			     bool xauto_access);

///
/// Tensor product of x0 and x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void tensor(const sec_tp& x0, const sec_tp& x1, sec_tp& xresult,
			   bool xauto_access);

//==============================================================================

} // namespace sec_tp_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_TP_H
