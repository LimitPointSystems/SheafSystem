


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_jcb_ed.

#ifndef SEC_JCB_ED_H
#define SEC_JCB_ED_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef JCB_ED_H
#include "jcb_ed.h"
#endif

#ifndef SEC_JCB_H
#include "sec_jcb.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_JCB_ED
//==============================================================================

///
/// A section of a bundle with fiber type jcb_ed.
///
class SHEAF_DLL_SPEC sec_jcb_ed : public sec_jcb
{
  //============================================================================
  /// @name JCB_ED FACET OF CLASS SEC_JCB_ED
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef jcb_ed fiber_type;

  ///
  /// Default constructor.
  ///
  sec_jcb_ed();

  ///
  /// Creates a new sec_jcb_ed handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_jcb_ed(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_jcb_ed handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_jcb_ed(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_jcb_ed handle attached to the member state with name
  /// xname in xhost.
  ///
  sec_jcb_ed(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_jcb_ed(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);

  ///
  /// Creates a new sec_jcb_ed handle attached to the same state as xother.
  ///
  explicit sec_jcb_ed(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_jcb_ed(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_jcb_ed& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_jcb_ed& operator=(const sec_jcb_ed& xother);

  ///
  /// Assignment operator.
  ///
  sec_jcb_ed& operator=(const jcb_ed& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_jcb_ed& operator=(const jcb_ed_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_jcb_ed();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name JCB FACET OF CLASS SEC_JCB_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_JCB_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_JCB_ED
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_JCB_ED
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
  /// Make a new handle, no state instance of current.
  ///
  virtual sec_jcb_ed* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_jcb_ed* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_jcb_ed*>(sec_jcb::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_JCB_ED
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

} // namespace fiber_bundle

#endif // ifndef SEC_JCB_ED_H

