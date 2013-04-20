


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_at2.

#ifndef SEC_AT2_H
#define SEC_AT2_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_ATP_H
#include "sec_atp.h"
#endif

#ifndef AT2_H
#include "at2.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_AT2
//==============================================================================

///
/// A section of a bundle with fiber type at2.
///
class SHEAF_DLL_SPEC sec_at2 : public sec_atp
{

  //============================================================================
  /// @name AT2 FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef at2 fiber_type;

  ///
  /// Default constructor.
  ///
  sec_at2();

  ///
  /// Creates a new sec_at2 handle attached to the member state with hub id
  /// xhub_id in* xhost.
  ///
  sec_at2(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_at2 handle attached to the member state with id
  /// xid in* xhost.
  ///
  sec_at2(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_at2 handle attached to the member state with name
  /// xname in xhost.
  ///
  sec_at2(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_at2(const namespace_poset* xnamespace,
          const poset_path& xpath,
          bool xauto_access = true);

  ///
  /// Creates a new sec_at2 handle attached to the same state as xother.
  ///
  explicit sec_at2(const sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_at2(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_at2(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_at2& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_at2& operator=(const sec_at2& xother);

  ///
  /// Assignment operator.
  ///
  sec_at2& operator=(const at2& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_at2& operator=(const at2_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_at2();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name ATP FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name SEC_REP_SPACE_MEMBER FACET OF CLASS SEC_AT2
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
  virtual sec_at2* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_at2* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_at2*>(sec_atp::clone(xnew_state, xauto_access));
  }
  
protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_AT2
  //============================================================================
  //@{

public:

  ///
  /// True if xother conforms to an instance of the fiber of current.
  ///
  bool fiber_is_ancestor_of(const any* xother) const;

  ///
  /// True if xother conforms to current
  ///
  bool is_ancestor_of(const any* xother) const;

  ///
  /// Class invariant.
  ///
  bool invariant() const;

protected:

private:

  //@}


//##############################################################################

public:

  ///
  /// component indexed by row and col
  ///
//   virtual scalar_type* comp2(int row, int col);

  ///
  /// Returns index into linear storage of the component
  /// in a specified row and column
  ///
//   int index_for_row_column(int row, int column);


  ///
  /// set component indexed by row and col
  ///
//   virtual void set_comp2(int row, int col, scalar_type* new_comp);


};

} // namespace fiber_bundle

#endif // ifndef SEC_AT2_H
