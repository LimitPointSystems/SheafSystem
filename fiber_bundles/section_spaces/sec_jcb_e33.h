


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_jcb_e33.

#ifndef SEC_JCB_E33_H
#define SEC_JCB_E33_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_JCB_ED_H
#include "sec_jcb_ed.h"
#endif

#ifndef JCB_E33_H
#include "jcb_e33.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_JCB_E33
//==============================================================================

///
/// A section of a bundle with fiber type jcb_e33.
///
class SHEAF_DLL_SPEC sec_jcb_e33 : public sec_jcb_ed
{

  //============================================================================
  /// @name JCB_E33 FACET OF CLASS SEC_JCB_E33
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef jcb_e33 fiber_type;

  ///
  /// Default constructor.
  ///
  sec_jcb_e33();

  ///
  /// Creates a new sec_jcb_e33 handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_jcb_e33(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_jcb_e33 handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_jcb_e33(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_jcb_e33 handle attached to the member state with name
  /// xname in* xhost.
  ///
  sec_jcb_e33(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_jcb_e33(const namespace_poset* xnamespace,
              const poset_path& xpath,
              bool xauto_access = true);

  ///
  /// Creates a new sec_jcb_e33 handle attached to the same state as xother.
  ///
  explicit sec_jcb_e33(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_jcb_e33(sec_rep_space* xhost,
              section_dof_map* xdof_map = 0,
              bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_jcb_e33& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_jcb_e33& operator=(const sec_jcb_e33& xother);

  ///
  /// Assignment operator.
  ///
  sec_jcb_e33& operator=(const jcb_e33& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_jcb_e33& operator=(const jcb_e33_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_jcb_e33();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name JCB_ED FACET OF CLASS SEC_JCB_E33
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name JCB FACET OF CLASS SEC_JCB_E33
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_JCB_E33
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_JCB_E33
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_JCB_E33
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
  virtual sec_jcb_e33* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_jcb_e33* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_jcb_e33*>(sec_jcb_ed::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_JCB_E33
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

class sec_e3;

namespace sec_jcb_algebra
{

#ifndef DOXYGEN_SKIP_UNKNOWN
///
/// Push vector forward (pre-allocated version).
///
SHEAF_DLL_SPEC void push(const sec_jcb_e33& xjcb, const sec_e3& xvector, sec_e3& xresult,
			 bool xauto_access);
#endif // ifndef DOXYGEN_SKIP_UNKNOWN

///
/// Pull covector back (pre-allocated version).
///
SHEAF_DLL_SPEC void pull(const sec_jcb_e33& xjcb, const sec_e3& xcovector, sec_e3& xresult,
			 bool xauto_access);

} // namespace sec_jcb_algebra

} // namespace fiber_bundle

#endif // ifndef SEC_JCB_E33_H


