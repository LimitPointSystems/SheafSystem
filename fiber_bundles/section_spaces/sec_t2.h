


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_t2.

#ifndef SEC_T2_H
#define SEC_T2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_TP_H
#include "sec_tp.h"
#endif

#ifndef T2_H
#include "t2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_T2
//==============================================================================

///
/// A section of a bundle with fiber type tp.
///
class SHEAF_DLL_SPEC sec_t2 : public sec_tp
{

  //============================================================================
  /// @name T2 FACET OF CLASS SEC_T2
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef t2 fiber_type;


  ///
  /// Default constructor.
  ///
  sec_t2();

  ///
  /// Creates a new sec_t2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_t2(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_t2 handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_t2(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_t2 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_t2(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_t2(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_t2 handle attached to the same state as xother.
  ///
  explicit sec_t2(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_t2(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_t2(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_t2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_t2& operator=(const sec_t2& xother);

  ///
  /// Assignment operator.
  ///
  sec_t2& operator=(const t2& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_t2& operator=(const t2_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_t2();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_T2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_T2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_T2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_T2
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
  virtual sec_t2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_t2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_t2*>(sec_tp::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_T2
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

public:

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

class sec_at1;

namespace sec_tp_algebra
{

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void alt(const sec_t2& x0, sec_at2& xresult, bool xauto_access);

///
/// The alternating (antisymmetric) part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void alt(const sec_t2& x0, sec_t2& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void sym(const sec_t2& x0, sec_st2& xresult, bool xauto_access);

///
/// The symmetric part of tensor x0
/// (pre-allocated version).
///
SHEAF_DLL_SPEC void sym(const sec_t2& x0, sec_t2& xresult, bool xauto_access);

///
/// Contraction on contravariant index xp and covariant index xq
/// (pre-allocated version).
///
/// The arguments xp and xq are indices into the "variance type" bitset.
/// This implies that xp != xq.
///
SHEAF_DLL_SPEC void contract(const sec_t2& x0, int xp, int xq, sec_at0& xresult,
			     bool xauto_access);

///@todo: Remove when we have an efficient general implementation.
///
/// Tensor product of x0 and x1 (pre-allocated version).
///
SHEAF_DLL_SPEC void tensor(const sec_at1& x0, const sec_at1& x1, sec_t2& xresult,
			   bool xauto_access);

//==============================================================================

} // namespace sec_tp_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_T2_H


