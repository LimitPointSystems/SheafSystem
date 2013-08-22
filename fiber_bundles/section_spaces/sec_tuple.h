


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_tuple.

#ifndef SEC_TUPLE_H
#define SEC_TUPLE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_REP_SPACE_MEMBER_H
#include "sec_rep_space_member.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef TUPLE_H
#include "tuple.h"
#endif

namespace fiber_bundle
{

class sec_tuple_space;
class fiber_bundles_namespace;  
  
//==============================================================================
// CLASS SEC_TUPLE
//==============================================================================

///
/// A section of a bundle with fiber type tuple.
///
class SHEAF_DLL_SPEC sec_tuple : public sec_rep_space_member
{

  // ===========================================================
  /// @name HOST FACTORY FACET OF CLASS SEC_TUPLE
  // ===========================================================
  //@{

public:

  // Typedefs:

  ///
  /// The type of namespace for this type of member.
  ///
  typedef fiber_bundles_namespace namespace_type;

  ///
  /// The type of host poset.
  ///
  typedef sec_tuple_space host_type;

  ///
  /// The fiber type.
  ///
  typedef tuple fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_tuple scalar_type;

  ///
  /// The path to the standard rep for sections of this type.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// The standard host path for section type S with base path xbase_path,
  /// representation path xrep_path, and section and fiber suffixes 
  /// xsection_suffix and xfiber_suffix, respectively.
  ///
  template <typename S>
  static poset_path standard_host_path(const poset_path& xbase_path,
                                       const poset_path& xrep_path,
                                       const string& xsection_suffix,
                                       const string& xfiber_suffix);

  ///
  /// True if and only if the host with path standard_host_path<S>(xbase_path, xrep_path, xsection_suffix, xfiber_suffix)
  /// does not exist in namespace xns, or if it exists, conforms to S::host_type.
  ///
  template <typename S>
  static bool standard_host_is_available(const namespace_poset& xns,
                                         const poset_path& xbase_path,
                                         const poset_path& xrep_path,
                                         const string& xsection_suffix,
                                         const string& xfiber_suffix,
                                         bool xauto_access);

//   ///
//   /// True if and only if the fiber space with path S::fiber_type::standard_host_path<S::fiber_type>(xfiber_suffix)
//   /// does not exist in namespace xns, or if it exists, conforms to S:fiber_type:host_type and is auto-read-accessible.
//   ///
//   template <typename S>
//   static bool standard_fiber_host_is_auto_read_accessible(const namespace_poset& xns, const string& xfiber_suffix, bool xauto_access);

//   ///
//   /// The standard schema path for section type S with base path xbase_path,
//   /// representation path xrep_path, and fiber suffix xfiber_suffix.
//   ///
//   template <typename S>
//   static poset_path standard_schema_path(const poset_path& xbase_path,
//                                          const poset_path& xrep_path,
//                                          const string& xfiber_suffix);

//   ///
//   /// True if and only if the schema host with path standard_schema_path(xbase_path, xrep_path, xfiber_suffix)
//   /// does not exist in namespace xns, or if it exists, conforms to schema_type::host_type and is auto-read-write-accessible.
//   ///
//   template <typename S>
//   static bool standard_schema_host_is_auto_read_write_accessible(const namespace_poset& xns,
//                                                                  const poset_path& xbase_path,
//                                                                  const poset_path& xrep_path,
//                                                                  const string& xfiber_suffix,
//                                                                  bool xauto_access);

  ///
  /// Manual, shallow factory method; creates a new host table for members of this type.
  /// The poset is created in namespace xns with path xhost_path and schema specified by xschema_path,
  ///
  static host_type& new_host(namespace_type& xns, 
                             const poset_path& xhost_path, 
                             const poset_path& xschema_path,
                             bool xauto_access);

protected:

private:

  //@}
 

  //============================================================================
  /// @name TUPLE FACET OF CLASS SEC_TUPLE
  //============================================================================
  //@{


public:

  ///
  /// Default constructor.
  ///
  sec_tuple();

  ///
  /// Creates a new sec_tuple handle attached to the member state with hub id
  /// xhub_id in xhost.
  ///
  sec_tuple(const sec_rep_space* xhost, pod_index_type xhub_id);

  ///
  /// Creates a new sec_tuple handle attached to the member state with id
  /// xid in xhost.
  ///
  sec_tuple(const sec_rep_space* xhost, const scoped_index& xid);

  ///
  /// Creates a new sec_tuple handle attached to the member state with name
  /// xname in* xhost.
  ///
  sec_tuple(const sec_rep_space* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the member state
  /// with path xpath in namespace xnamespace.
  ///
  sec_tuple(const namespace_poset* xnamespace,
            const poset_path& xpath,
            bool xauto_access = true);

  ///
  /// Creates a new sec_tuple handle attached to the same state as xother.
  ///
  explicit sec_tuple(sec_rep_space_member* xother);

  ///
  /// New handle/new state constructor.
  ///
  sec_tuple(sec_rep_space* xhost,
            section_dof_map* xdof_map = 0,
            bool xauto_access = true);

  ///
  /// Creates a new handle attached to a new jim state
  /// which is a partial section defined only on the base space
  /// member with index xbase_mbr_index and version xbase_version.
  ///
  sec_tuple(sec_rep_space* xhost,
            abstract_poset_member& xbase_mbr,
            int xbase_version = CURRENT_HOST_VERSION,
            bool xauto_access = true);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  virtual sec_tuple& operator=(const abstract_poset_member& xother);

  ///
  /// Assignment operator; synonym for attach_to_state(&xother).
  ///
  sec_tuple& operator=(const sec_tuple& xother);

  ///
  /// Destructor.
  ///
  ~sec_tuple();

  ///
  /// Number of factors (components) in tuple.
  ///
  virtual int factor_ct() const;

  ///
  /// Number of factors (components) in tuple.
  ///
  int factor_ct(bool xauto_access) const;

protected:

private:

  //@}


  //============================================================================
  /// @name ABSTRACT POSET MEMBER FACET OF CLASS SEC_TUPLE
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
  virtual sec_tuple* clone() const;

  ///
  /// Make a new handle instance of current.  Attach the new instance to
  /// a new state if xnew_state is true.  Otherwise, attach the new instance
  /// to the current state.
  ///
  inline sec_tuple* clone(bool xnew_state, bool xauto_access = true) const
  {
    return static_cast<sec_tuple*>(
      sec_rep_space_member::clone(xnew_state, xauto_access));
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
  /// @name ANY FACET OF CLASS SEC_TUPLE
  //============================================================================
  //@{

public:

  ///@todo Make virtual.
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

  using sec_rep_space_member::restrict_to;

  ///
  /// Restricts this section and its components to schema member xschema.
  ///
  virtual void restrict_to(const abstract_poset_member* xschema);

  ///
  /// Restricts this section to base with index xbase_id and
  /// fiber schema with index xfiber_schema_id
  ///
  virtual void restrict_to(pod_index_type xbase_id,
                           pod_index_type xfiber_schema_id);

  ///
  /// Restricts this section and its components to base xbase and
  /// fiber schema xfiber_schema
  ///
  virtual void restrict_to(const abstract_poset_member* xbase, const abstract_poset_member* xfiber_schema);

  ///
  /// Restricts this handle and its components to the same restriction
  /// as xother.
  ///
  virtual void restrict_to_same(const abstract_poset_member* xother);

  ///
  /// Removes any restriction to this handle and its components;
  /// restores base and fiber to the base and fiber of host, respectively.
  ///
  void unrestrict();

  ///
  /// The ith component of section.
  ///
  scalar_type* comp(int i) const;

  ///
  /// Sets ith comp of section.
  ///
  void set_comp(int i, scalar_type* component);

  // STATE INTERFACE

  ///
  /// Detaches field from state it is currently attached to.
  ///
  void detach_from_state();


protected:

  ///
  /// Initializes data members introduced by this handle.
  ///
  void attach_handle_data_members();

  ///
  /// Creates a fiber space name for sec class with name xname.
  /// Convenience method used by derived class "new_host" methods.
  ///
  inline static string create_fiber_name(const string& xname)
  {
    return xname + "_fiber";
  }

private:

  //@}

};

//==============================================================================
// NON-MEMBER FUNCTIONS
//==============================================================================

///
/// The deep size of the referenced object of type sec_tuple.
/// if xinclude_shallow, add the sizeof x0 to the result.
///
SHEAF_DLL_SPEC size_t deep_size(const sec_tuple& x0, bool xinclude_shallow = true);

} // namespace fiber_bundle

#endif // ifndef SEC_TUPLE_H


