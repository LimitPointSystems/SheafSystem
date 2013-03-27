
// $RCSfile: ternary_section_space_schema_poset.h,v $ $Revision: 1.23 $ $Date: 2013/01/12 17:17:13 $

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class POSET

#ifndef TERNARY_SECTION_SPACE_SCHEMA_POSET_H
#define TERNARY_SECTION_SPACE_SCHEMA_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SECTION_SPACE_SCHEMA_POSET_H
#include "section_space_schema_poset.h"
#endif


namespace fiber_bundle
{

///
/// A schema poset for a section space. A Cartesian product
/// subspace of the tensor of a base space lattice, a fiber
/// schema lattice, and a local schema lattice.
///
class SHEAF_DLL_SPEC ternary_section_space_schema_poset : public section_space_schema_poset
{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///@todo static_class_name

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates standard schema for this class in namespace xns.
  ///
  static void make_standard_schema(namespace_poset& xns);

  // CANONICAL MEMBERS

  ///
  /// Default constructor; creates a new ternary_section_space_schema_poset handle not attached to any state.
  ///
  ternary_section_space_schema_poset();

  ///
  /// Copy constructor; attaches this to the same state as xother
  ///
  ternary_section_space_schema_poset(const ternary_section_space_schema_poset& xother);

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual ternary_section_space_schema_poset* clone() const;

  ///
  /// Assignment operator; attaches this to the same state as xother
  ///
  ternary_section_space_schema_poset& operator=(const poset_state_handle& xother);

  ///
  /// Destructor
  ///
  virtual ~ternary_section_space_schema_poset();

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant
  ///
  virtual bool invariant() const;


  // NEW HANDLE, NEW STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to a new ternary_section_space_schema_poset state
  /// in namespace xns with name xname, representation xrep, base xbase, fiber space
  /// xfiber_space, and local schema xlocal_schema.
  ///
  ternary_section_space_schema_poset(namespace_poset* xns,
                                     const string& xname,
                                     sec_rep_descriptor& xrep,
                                     poset_state_handle& xbase_space,
                                     poset_state_handle& xfiber_space,
                                     poset_state_handle& xlocal_schema,
                                     bool xauto_access = true);

  // NEW HANDLE, EXISTING STATE CONSTRUCTORS

  ///
  /// Creates a new handle attached to the ternary_section_space_schema_poset with
  /// index xindex in namespace xhost.
  ///
  ternary_section_space_schema_poset(namespace_poset* xhost, const scoped_index& xindex);

  ///
  /// Creates a new handle attached to the ternary_section_space_schema_poset with
  /// name xname in namespace xhost.
  ///
  ternary_section_space_schema_poset(namespace_poset* xhost, const string& xname);

  ///
  /// Creates a new handle attached to the ternary_section_space_schema_poset associated
  /// with namespace member xmbr
  ///
  ternary_section_space_schema_poset(namespace_poset_member* xmbr);


  // EXISTING HANDLE, NEW STATE "CONSTRUCTORS"

  ///
  /// Attaches this to a new ternary_section_space_schema_poset state
  /// in namespace xns with name xname, representation xrep, base xbase,
  /// fiber space xfiber_space, and local schema xlocal_schema.
  ///
  void new_state(namespace_poset* xns,
                 const string& xname,
                 sec_rep_descriptor& xrep,
                 poset_state_handle& xbase_space,
                 poset_state_handle& xfiber_space,
                 poset_state_handle& xlocal_schema,
                 bool xauto_access = true);

  ///
  /// Attaches this to a new ternary_section_space_schema_poset state in namespace xns with name xname,
  /// representation the member with index xrep_member_id in the poset with index xrep_poset_id,
  /// base the poset with index xbase_space_poset_id,
  /// fiber space the poset with index xfiber_space_poset_id,
  /// local schema the poset with index xlocal_space_poset_id.
  ///
  void new_state(namespace_poset* xns,
                 const string& xname,
                 const scoped_index& xrep_poset_id,
                 const scoped_index& xrep_member_id,
                 const scoped_index& xbase_space_poset_id,
                 const scoped_index& xfiber_space_poset_id,
                 const scoped_index& xlocal_schema_poset_id,
                 bool xauto_access = true);

  // STATE FACET

  ///
  /// Detach this handle from its state
  ///
  virtual void detach_from_state();

  // SCHEMATIZATION FACET

  ///
  /// True if this poset has been prepared for use as a schema,
  /// i.e. if it has been given table_dofs and row_dofs subposets
  ///
  virtual bool is_schematized(bool xauto_access);

  ///
  /// True if the member with index xindex has been prepared for use as a schema,
  /// i.e. if it has been given table_dofs and row_dofs subposets
  ///
  virtual bool is_schematized(const scoped_index& xindex, bool xauto_access);

  ///
  /// Prepare this poset and its top member for use as a schema.
  /// If xall_members = true, schematize all other members as well.
  ///
  virtual void schematize(subposet* xtable_dof_subposet,
                          subposet* xrow_dof_subposet,
                          bool xall_members = false);

  // MEMBERSHIP FACET

  ///
  /// The number of members of this poset
  ///
  virtual int member_ct();

  ///
  /// The number of standard members automatically
  /// allocated by the constructor.
  ///
  virtual int standard_member_ct() const;

  ///
  /// The upper bound on the member_index;
  ///
  //   virtual int member_index_ub();
  virtual scoped_index member_index_ub();

  ///
  /// An iterator for members of this poset
  ///
  index_iterator member_iterator();

  ///
  /// True if this poset contains poset member with index xindex
  ///
  virtual bool contains_member(const scoped_index& xindex);

  ///
  /// True if version xversion of this poset contains poset member with index xindex
  ///
  virtual bool contains_member(const scoped_index& xindex, int xversion);

  ///
  /// True if this poset contains a member with name xname
  ///
  virtual bool contains_member(const string& xname)
  {
    return poset_state_handle::contains_member(xname);
  };

  ///
  /// True if this poset contains xmbr
  ///
  bool contains_member(abstract_poset_member* xmbr)
  {
    return poset_state_handle::contains_member(xmbr);
  };

  ///
  /// True if the member with index xindex is a jim.
  ///
  virtual bool is_jim(const scoped_index& xindex, bool xin_current_version = true);

  ///
  /// True if the member with name xname is a jim.
  ///
  inline bool is_jim(const string& xname, bool xin_current_version = true)
  {
    return poset_state_handle::is_jim(xname, xin_current_version);
  }

  ///
  /// True if the member with index xindex covers the bottom.
  ///
  virtual bool is_atom(const scoped_index& xindex);

  // COVER RELATION FACET

  ///
  /// True if there is a cover link between xlesser and xgreater
  ///
  virtual bool contains_link(const scoped_index& xgreater,
			     const scoped_index& xlesser);

  ///
  /// The number of members in the lower cover (xlower true)
  /// or upper cover (xlower false) of the member with index xindex.
  ///
  virtual size_type cover_ct(bool xlower, const scoped_index& xindex);

  ///
  /// True if xlesser is less than or equal to xgreater.
  ///
  virtual bool le(const scoped_index& xgreater, const scoped_index& xlesser);

  ///
  /// True if xlesser is less than or equivalent to xgreater.
  ///
  virtual bool leqv(const scoped_index& xgreater, const scoped_index& xlesser);

  ///
  /// True if xother is join equivalent to xindex
  ///
  virtual bool is_jem(const scoped_index& xindex, const scoped_index& xother);

  ///
  /// The index of the largest member which is join-equivalent to xindex
  ///
  virtual scoped_index greatest_jem(const scoped_index& xindex);

  ///
  /// The index of the smallest member which is join-equivalent to xindex
  ///
  virtual scoped_index least_jem(const scoped_index& xindex);

  ///
  /// Merge the join-equivalence class of xjem2 under that of xjem1
  ///
  virtual void merge_jems(const scoped_index& xjem1, const scoped_index& xjem2);


  // SUBPOSET FACET

  ///
  /// The number of subposets of this poset
  ///
  virtual int subposet_ct();

  ///
  /// The number of standard subposets automatically
  /// allocated by the constructor.
  ///
  virtual int standard_subposet_ct();

  ///
  /// The upper bound on the subposet index;
  ///
  //   virtual int subposet_index_ub();
  virtual scoped_index subposet_index_ub();

  ///
  /// The number of versions currently defined.
  ///
  virtual int version_ct();

  ///
  /// The current version
  ///
  virtual int version();

  ///
  /// The subposet index of the whole() subposet for version xversion.
  ///
  virtual scoped_index version_index(int xversion);

  ///
  /// The subposet index of the jims() subposet for version xversion.
  ///
  virtual scoped_index version_jims_index(int xversion);

  // SECTION_SPACE_SCHEMA_FACET

  ///
  /// The poset id of the local schema for section spaces on this schema.
  ///
  pod_index_type local_schema_poset_id();

  ///
  /// The upper bound on the member id of the local schema
  /// for section spaces on this schema.
  ///
  scoped_index local_schema_member_id_ub();

  ///
  /// The increment in the member id when the id of the
  /// local schema component is increased by one.
  ///
  int local_schema_stride();

  ///
  /// The local schema for section spaces on this schema.
  ///
  inline poset_state_handle& local_schema()
  {
    return _local_schema;
  };

  ///
  /// Computes the index associated with component ids
  /// xbase_space_id and xfiber_schema_id.
  ///
  virtual scoped_index
  get_index_from_components(const scoped_index& xbase_space_id,
                            const scoped_index& xfiber_schema_id)
  {
    return get_index_from_components(xbase_space_id, xfiber_schema_id, TOP_INDEX);
  };

  ///
  /// Computes the index associated with component ids
  /// xbase_space_id, xfiber_schema_id, and xlocal_schema_id.
  ///
  scoped_index get_index_from_components(const scoped_index& xbase_id,
					       const scoped_index& xfiber_schema_id,
					       const scoped_index& xlocal_schema_id);

  ///
  /// Computes the base space component id associated with xindex.
  ///
  virtual scoped_index get_base_space_id_from_index(const scoped_index& xindex) const;

  ///
  /// Computes the fiber schema component id associated with xindex.
  ///
  virtual scoped_index get_fiber_schema_id_from_index(const scoped_index& xindex);

  ///
  /// Computes the local schema component id associated with xindex.
  ///
  scoped_index get_local_schema_id_from_index(const scoped_index& xindex);


  // ===========================================================
  // I/O SUPPORT FACET
  // ===========================================================

  ///
  /// Creates a member handle of the type appropriate for members of this
  /// when used as a schema. Intended for use only by the i/o subsystem.
  //// @hack the product subposet hack, version 2.
  //// This member exists only to encapsulate the hack.
  ////
  virtual schema_poset_member*
  new_schema_handle(const string& xid_space_name,
                    pod_index_type xschema_member_ext_id,
                    pod_index_type xbase_space_ext_id,
                    pod_index_type xfiber_schema_ext_id,
                    pod_index_type xlocal_schema_ext_id);

  // Note that we can not covariantly redefine the return type
  // of new_schema_handle without including ternary_section_space_schema_member.h,
  // which causes a cyclic dependency between the poset and member classes.

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual scoped_index prereq_id(int xi) const;

protected:

  // The using declaration is placed here as opposed to being at the beginning
  // of the public "new_state" methods because putting it in the public section
  // makes the following new_state method public also.

  using section_space_schema_poset::new_state;

  ///
  /// Attaches this external poset to a new poset state with schema
  /// given by xschema and table dofs by xdof_map.
  /// Intended for use by i/o subsystem.
  ///
  virtual void new_state(schema_poset_member& xschema, array_poset_dof_map& xdof_map);

  ///
  ///  Class represention of table dofs.
  ///
  class SHEAF_DLL_SPEC table_dof_tuple_type
  {
  public:

    ///
    /// The id of the representation for section spaces on this schema.
    ///
    namespace_relative_member_index::pod_type rep_id;

    ///
    /// The id of the base space for section spaces on this schema.
    ///
    namespace_relative_member_index::pod_type base_space_id;

    ///
    /// The upper bound on base space member ids.
    ///
    int base_space_member_id_ub;

    ///
    /// The increment in the member id when the id of the
    /// base space component is increased by one.
    ///
    int base_space_stride;

    ///
    /// The dimension of the base space.
    ///
    int db;

    ///
    /// The id of the fiber schema for section spaces on this schema.
    ///
    namespace_relative_member_index::pod_type fiber_schema_id;

    ///
    /// The upper bound on fiber schema member ids.
    ///
    int fiber_schema_member_id_ub;

    ///
    /// The increment in the member id when the id of the
    /// fiber schema component is increased by one.
    ///
    int fiber_schema_stride;

    ///
    /// The dimension of the fiber space.
    ///
    int df;

    ///
    /// The id of the fiber space for section spaces on this schema.
    ///
    namespace_relative_member_index::pod_type fiber_space_id;

    ///
    /// Default for fiber_schema_member_id_ub.
    ///
    static const int FIBER_SCHEMA_MEMBER_ID_UB = 256;

    ///
    /// Default for base_space_member_id_ub.
    ///
    static const int BASE_SPACE_MEMBER_ID_UB = INT_MAX/FIBER_SCHEMA_MEMBER_ID_UB;

    ///
    /// The id of the local schema for section spaces on this schema.
    ///
    namespace_relative_member_index::pod_type local_schema_id;

    ///
    /// The upper bound on local schema member ids.
    ///
    int local_schema_member_id_ub;

    ///
    /// The increment in the member id when the id of the
    /// local schema component is increased by one.
    ///
    int local_schema_stride;

    ///
    /// Default for fiber_schema_member_id_ub.
    ///
    static const int LOCAL_SCHEMA_MEMBER_ID_UB = 16;

    ///
    /// Default constructor.
    ///
    table_dof_tuple_type();
  };

  ///
  /// Initializes the handle data members when this handle
  /// is attached to a state.
  ///
  virtual void attach_handle_data_members();

  ///
  /// Initializes the table dofs ("class variables")
  ///
  inline void initialize_table_dofs(void* xtable_dofs, size_t xtable_dof_ub)
  {
    poset_state_handle::initialize_table_dofs(xtable_dofs, xtable_dof_ub);
  };

private:

  ///
  /// Pointer to the storage for the table dofs.
  ///
  inline table_dof_tuple_type* table_dof_tuple_ptr()
  {
    return reinterpret_cast<table_dof_tuple_type*>(table_dof_map().dofs());
  };

  ///
  /// Initializes the handle data members of this class when
  /// this handle is created.
  ///
  void attach_handle_data_members(namespace_poset* xns,
                                  const scoped_index& xrep_poset_id,
                                  const scoped_index& xrep_member_id,
                                  const scoped_index& xbase_space_poset_id,
                                  const scoped_index& xfiber_space_poset_id,
                                  const scoped_index& xlocal_schema_poset_id);

  ///
  /// Initializes the table dofs ("class variables")
  ///
  void initialize_table_dofs(const scoped_index& xrep_poset_id,
                             const scoped_index& xrep_member_id,
                             const scoped_index& xbase_space_poset_id,
                             const scoped_index& xfiber_space_poset_id,
                             const scoped_index& xlocal_schema_poset_id);

  ///
  /// The local schema for section spaces on this schema.
  ///
  poset_state_handle _local_schema;

  ///
  /// True if prototype for this class has been entered in factory.
  /// Intended to force creation of prototype at initialization.
  ///
  static bool _has_prototype;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

};

} // namespace fiber_bundle

#endif // TERNARY_SECTION_SPACE_SCHEMA_POSET_H
