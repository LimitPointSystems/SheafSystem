


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_st2_e2.

#ifndef SEC_ST2_E2_H
#define SEC_ST2_E2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_ST2_H
#include "sec_st2.h"
#endif

#ifndef ST2_E2
#include "st2_e2.h"
#endif

namespace fiber_bundle
{

class sec_e2;

//==============================================================================
// CLASS SEC_ST2_E2
//==============================================================================

///
/// A section of a bundle with fiber type st2_e2.
///
class SHEAF_DLL_SPEC sec_st2_e2 : public sec_st2
{

  //============================================================================
  /// @name ST2_E2 FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef st2_e2 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e2 vector_space_type;

  ///
  /// Default constructor.
  ///
  sec_st2_e2();

  // New handle/old state constructor.

  ///
  /// Creates a new sec_st2_e2 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_st2_e2(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_st2_e2 handle attached to the member state with id
  /// xindex in xhost.
  ///
  sec_st2_e2(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_st2_e2 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_st2_e2(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_st2_e2(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);

  ///
  /// Creates a new sec_st2_e2 handle attached to the same state as xother.
  ///
  explicit sec_st2_e2(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor
  ///
  sec_st2_e2(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_st2_e2(sec_rep_space* xhost,
             abstract_poset_member& xbase_mbr,
             int xbase_version = CURRENT_HOST_VERSION,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_st2_e2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_st2_e2& operator=(const sec_st2_e2& xother);

  ///
  /// Assignment operator.
  ///
  sec_st2_e2& operator=(const st2_e2& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_st2_e2& operator=(const st2_e2_lite& xfiber);

  ///
  /// Destructor
  ///
  ~sec_st2_e2();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ST2 FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_ST2_E2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_ST2_E2
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
  virtual sec_st2_e2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_st2_e2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_st2_e2*>(sec_st2::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_ST2_E2
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


class sec_at0;

namespace sec_st2_algebra
{

#ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

///
/// The determinant of x0.
///
SHEAF_DLL_SPEC void determinant(const sec_st2_e2& x0, sec_at0& xresult, bool xauto_access);

#endif // ifndef DOXYGEN_1_5_4_SKIP_UNKNOWN

} // namespace sec_st2_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_ST2_E2_H

