


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_st4_e3

#ifndef SEC_ST4_E3_H
#define SEC_ST4_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_ST4_H
#include "sec_st4.h"
#endif

#ifndef ST4_E3
#include "st4_e3.h"
#endif

namespace fiber_bundle
{

class sec_e3;

//==============================================================================
// CLASS SEC_ST4_E3
//==============================================================================

///
/// A section of a bundle with fiber type st4_e3.
///
class SHEAF_DLL_SPEC sec_st4_e3 : public sec_st4
{
  //============================================================================
  /// @name ST4_E3 FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef st4_e3 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e3 vector_space_type;

  ///
  /// Default constructor.
  ///
  sec_st4_e3();

  ///
  /// Creates a new sec_st4_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_st4_e3(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_st4_e3 handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_st4_e3(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_st4_e3 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_st4_e3(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_st4_e3(const namespace_poset* xnamespace,
             const poset_path& xpath,
             bool xauto_access = true);

  ///
  /// Creates a new sec_st4_e3 handle attached to the same state as xother.
  ///
  explicit sec_st4_e3(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_st4_e3(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_st4_e3(sec_rep_space* xhost,
             abstract_poset_member& xbase_mbr,
             int xbase_version = CURRENT_HOST_VERSION,
             bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_st4_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_st4_e3& operator=(const sec_st4_e3& xother);

  ///
  /// Assignment operator.
  ///
  sec_st4_e3& operator=(const st4_e3& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_st4_e3& operator=(const st4_e3_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_st4_e3();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ST4 FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name STP FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_ST4_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_ST4_E3
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
  virtual sec_st4_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_st4_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_st4_e3*>(sec_st4::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_ST4_E3
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

} // namespace fiber_bundle

#endif // ifndef SEC_ST4_E3_H

