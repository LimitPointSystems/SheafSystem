


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_jcb_space.

#ifndef SEC_JCB_SPACE_H
#define SEC_JCB_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_VD_SPACE_H
#include "sec_vd_space.h"
#endif

#ifndef JCB_TABLE_DOFS_TYPE_H
#include "jcb_table_dofs_type.h"
#endif

namespace sheaf
{
class namespace_poset;
}

namespace fiber_bundle
{
using namespace sheaf;

class sec_at0;
class sec_at1;
class sec_jcb;
class jcb;

///
/// An abstract section space of Jacobians.
///
class SHEAF_DLL_SPEC sec_jcb_space : public sec_vd_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_JCB_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_jcb member_type;

  ///
  /// The fiber type.
  ///
  typedef jcb fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_at0 scalar_type;

  ///
  /// The type of vector sections that form the domain of jacobian sections of this type.
  ///
  typedef sec_at1 domain_space_type;

  ///
  /// The type of vector sections that form the range of jacobian sections of this type.
  ///
  typedef sec_at1 range_space_type;

  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef jcb_table_dofs_type table_dofs_type;

  ///
  /// True if and only if domain space of fiber space == fiber space of domain space and
  /// the range space of fiber space == fiber space of range space.
  /// More precisely, true if and only if the domain and range space of the fiber space of the 
  /// jacobian section schema specified by  xschema_path is the same as the fiber space 
  /// of the schema of the domain section space and range section space specified by
  /// xdomain_path and xrange_path respectively.
  ///
  static bool same_vector_fiber_space(const namespace_poset& xns, 
                                      const poset_path& xschema_path, 
                                      const poset_path& xdomain_path,
				      const poset_path& xrange_path,
                                      bool xauto_access);

  ///
  /// Creates a new sec_jcb_space in namespace xns with path xpath,
  /// schema specified by xschema_path, domain vector space specified
  /// by xdomain_path, and range vector space specified by xrange_path.
  ///
  static sec_jcb_space& new_table(namespace_type& xhost, 
				  const poset_path& xpath, 
				  const poset_path& xschema_path,
				  const poset_path& xdomain_path,
				  const poset_path& xrange_path,
				  bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  using sec_vd_space::d;
  
  ///
  /// Dimension d() as a function of domain dimension xdd and range dimension xdr.
  ///
  static int d(int xdd, int xdr);

  ///
  /// The dimension of the underlying ("domain") vector space.
  ///
  int dd() const;

  ///
  /// The dimension of the underlying ("domain") vector space; auto access signature.
  ///
  int dd(bool xauto_access) const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path() const;

  ///
  /// The path of the domain vector space.
  ///
  poset_path domain_path(bool xauto_access) const;

  ///
  /// Dimension of the range.
  ///
  virtual int dr() const;

  ///
  /// Dimension of the range (auto-access version).
  ///
  int dr(bool xauto_access) const;

  ///
  /// The path of the range vector space.
  ///
  poset_path range_path() const;

  ///
  /// The path of the range vector space.
  ///
  poset_path range_path(bool xauto_access) const;

protected:

  ///
  /// Default constructor;
  /// creates a new sec_jcb_space handle not attached to any state.
  ///
  sec_jcb_space();

  ///
  /// Copy constructor; disabled.
  ///
  sec_jcb_space(const sec_jcb_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~sec_jcb_space();

  ///
  /// Covariant constructor
  ///
  sec_jcb_space(sec_jcb* xtop, sec_jcb* xbottom);

private:

  //@}


  // ===========================================================
  /// @name SEC_VD_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_TUPLE_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}


  // ===========================================================
  /// @name SEC_REP_SPACE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}

 
  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// The id of the xi-th prerequisite poset for this.
  ///
  virtual pod_index_type prereq_id(int xi) const;

protected:

  ///
  /// Assignment operator; disabled.
  ///
  sec_jcb_space& operator=(const poset_state_handle& xother)
  {
    return const_cast<sec_jcb_space&>(*this);
  };

private:

  //@}

 
  // ===========================================================
  /// @name READ_WRITE_MONITOR_HANDLE FACET
  // ===========================================================
  //@{

public:

protected:

private:

  //@}
 
 
  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this.
  ///
  virtual bool is_ancestor_of(const any* xother) const;

  ///
  /// Virtual constructor; creates a new handle of the same
  /// actual type as this, attached to the same state as this.
  ///
  virtual sec_jcb_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // SEC_JCB_SPACE_H
