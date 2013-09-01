


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_t4

#ifndef SEC_T4_H
#define SEC_T4_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_TP_H
#include "sec_tp.h"
#endif

#ifndef T4_H
#include "t4.h"
#endif

namespace fiber_bundle
{

//==============================================================================
// CLASS SEC_T4
//==============================================================================

///
/// A section of a bundle with fiber type t4.
///
class SHEAF_DLL_SPEC sec_t4 : public sec_tp
{

  // ===========================================================
  /// @name HOST_FACTORY FACET OF CLASS SEC_T4
  // ===========================================================
  //@{

public:

  ///
  /// The fiber type.
  ///
  typedef t4 fiber_type;

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
  /// @name T4 FACET OF CLASS SEC_T4
  //============================================================================
  //@{

public:

  ///
  /// Default constructor.
  ///
  sec_t4();

  ///
  /// Creates a new sec_t4 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_t4(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_t4 handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_t4(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_t4 handle attached to the member state with name xname
  /// in* xhost.
  ///
  sec_t4(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_t4(const namespace_poset* xnamespace,
         const poset_path& xpath,
         bool xauto_access = true);

  ///
  /// Creates a new sec_t4 handle attached to the same state as xother.
  ///
  explicit sec_t4(sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_t4(sec_rep_space* xhost,
          section_dof_map* xdof_map = 0,
          bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_t4(sec_rep_space* xhost,
          abstract_poset_member& xbase_mbr,
          int xbase_version = CURRENT_HOST_VERSION,
          bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_t4& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_t4& operator=(const sec_t4& xother);

  ///
  /// Assignment operator.
  ///
  sec_t4& operator=(const t4& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_t4& operator=(const t4_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_t4();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_T4
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_T4
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_T4
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_T4
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
  virtual sec_t4* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_t4* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_t4*>(sec_tp::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_T4
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

#endif // ifndef SEC_T4_H


