


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_stp.

#ifndef SEC_STP_H
#define SEC_STP_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_TP_H
#include "sec_tp.h"
#endif

#ifndef STP_H
#include "stp.h"
#endif

namespace fiber_bundle
{

class sec_stp_space;

//==============================================================================
// CLASS SEC_STP
//==============================================================================

///
/// A section of a bundle with fiber type stp.
///
class SHEAF_DLL_SPEC sec_stp : public sec_tp
{
  //============================================================================
  /// @name STP FACET OF CLASS SEC_STP
  //============================================================================
  //@{

public:

  ///
  /// The type of host poset.
  ///
  typedef sec_stp_space host_type;

  ///
  /// The fiber type.
  ///
  typedef stp fiber_type;

  ///
  /// Default constructor.
  ///
  sec_stp();

  ///
  /// Creates a new sec_stp handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_stp(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_stp handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_stp(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_stp handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_stp(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_stp(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_stp handle attached to the same state as xother.
  ///
  explicit sec_stp(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_stp(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_stp(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_stp& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_stp& operator=(const sec_stp& xother);

  ///
  /// Assignment operator.
  ///
  sec_stp& operator=(const stp& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_stp& operator=(const stp_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_stp();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_STP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_STP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_STP
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_STP
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
  virtual sec_stp* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_stp* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_stp*>(sec_tp::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS SEC_STP
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

//$$SCRIBBLE: Currently all symmetric_product functions are
//            "not_implemented()" because meaningful
//            results would be something like Sym(st2 (X) st2) = st4.
//            But we have not yet implemented any st4 classes.

///
/// Namespace containing the algrebra functions for a a section 
/// of a fiber bundle with a fiber type stp.
///
namespace sec_stp_algebra
{

///
/// The symmetric product of two general tensors (pre-allocated version).
///
SHEAF_DLL_SPEC void symmetric_product(const sec_stp& x0, const sec_stp& x1, sec_stp& xresult,
				      bool xauto_access);

} // namespace sec_stp_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_STP_H


