


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_t3_e3

#ifndef SEC_T3_E3_H
#define SEC_T3_E3_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_T3_H
#include "sec_t3.h"
#endif

#ifndef T3_E3
#include "t3_e3.h"
#endif

namespace fiber_bundle
{

class sec_e3;

//==============================================================================
// CLASS SEC_T3_E3
//==============================================================================

///
/// A section of a bundle with fiber type t3_e3.
///
class SHEAF_DLL_SPEC sec_t3_e3 : public sec_t3
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_T3_E3
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The fiber type.
  ///
  typedef t3_e3 fiber_type;

  ///
  /// Type of underlying vector space.
  ///
  typedef sec_e3 vector_space_type;

  ///
  /// Creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path, schema specified by xschema_path,
  /// and vector section space specified by xvector_space_path.
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             const poset_path& xvector_space_path,
                             bool xauto_access);

  ///
  /// The standard host for sections of this type with base space xbase_path,
  /// representation xrep_path, section suffix xsection_suffix,
  /// and fiber suffix xfiber_suffix. Creates the host and its prerequisites
  /// if necessary.
  ///
  static host_type& standard_host(namespace_type& xns, 
                                  const poset_path& xbase_path,
                                  const poset_path& xrep_path,
                                  const string& xsection_suffix, 
                                  const string& xfiber_suffix, 
                                  bool xauto_access);

protected:

private:

  //@}


  //============================================================================
  /// @name T3_E3 FACET OF CLASS SEC_T3_E3
  //============================================================================
  //@{

public:

  ///
  /// Default constructor; creates an unattached handle.
  ///
  sec_t3_e3();

  ///
  /// Copy constructor; creates a new sec_t3_e3 handle
  /// attached to the same state as xother.
  ///
  sec_t3_e3(const sec_rep_space_member& xother);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_t3_e3(sec_rep_space* xhost,
             abstract_poset_member& xbase_mbr,
             int xbase_version = CURRENT_HOST_VERSION,
             bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state in xhost.
  /// If xdof_map is not null, it is used as the dof map.
  ///
  sec_t3_e3(sec_rep_space* xhost,
             section_dof_map* xdof_map = 0,
             bool xauto_access = true);

  ///
  /// Creates a new sec_t3_e3 handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_t3_e3(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_t3_e3 handle attached to
  /// the member state with id xid in xhost.
  ///
  sec_t3_e3(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_t3_e3 handle attached to
  /// the member state with name xname in xhost.
  ///
  sec_t3_e3(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_t3_e3(const namespace_poset* xnamespace,
            const poset_path& xpath,
            bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_t3_e3& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_t3_e3& operator=(const sec_t3_e3& xother);

  ///
  /// Assignment operator.
  ///
  sec_t3_e3& operator=(const t3_e3& xfiber);

  ///
  /// Assignment operator.
  ///
  sec_t3_e3& operator=(const t3_e3_lite& xfiber);

  ///
  /// Destructor.
  ///
  ~sec_t3_e3();

  ///
  /// Virtual constructor for the associated fiber type.
  ///
  virtual const fiber_type& fiber_prototype() const;

protected:

private:

  //@}


  //============================================================================
  /// @name T3 FACET OF CLASS SEC_T3_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TP FACET OF CLASS SEC_T3_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name VD FACET OF CLASS SEC_T3_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_T3_E3
  //============================================================================
  //@{

public:

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_T3_E3
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
  virtual sec_t3_e3* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_t3_e3* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_t3_e3*>(sec_tp::clone(xnew_state, xauto_access));
  }

protected:

private:

  //@}


  //============================================================================
  /// @name ANY FACET OF CLASS SEC_T3_E3
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

#endif // ifndef SEC_T3_E3_H


