

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class jcb_space.

#ifndef JCB_SPACE_H
#define JCB_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef VD_SPACE_H
#include "vd_space.h"
#endif

#ifndef JCB_TABLE_DOFS_TYPE_H
#include "jcb_table_dofs_type.h"
#endif

namespace fiber_bundle
{

  using namespace sheaf;
  class at1_space;
  class jcb;
  
  
///
/// An abstract space of Jacobians.
///
class SHEAF_DLL_SPEC jcb_space : public vd_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name JCB_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef jcb member_type;

  ///
  /// The type of domain vector space  associated with this space.
  ///
  typedef at1_space domain_space_type;

  ///
  /// The type of range vector space  associated with this space.
  ///
  typedef at1_space range_space_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();
  
  ///
  /// The table dofs type defined by the standard schema.
  ///
  typedef jcb_table_dofs_type table_dofs_type;

  using vd_space::d;
  
  ///
  /// The jacobian dimension implied by the schema specified by xschema_path.
  ///
  static int d(const namespace_poset& xns, const poset_path& xschema_path, bool xauto_access);
  
  ///
  /// The jacobian dimension implied by tensor the dimension of the domain vector space
  /// specified by xdomain_space_path and the range vector space specified by xrange_space_path.
  ///
  static int d(const namespace_poset& xns, const poset_path& xdomain_space_path, const poset_path& xrange_space_path, bool xauto_access);

  ///
  /// Dimension d() as a function of domain dimension xdd and range dimension xdr.
  ///
  static int d(int xdd, int xdr);

  ///
  /// Creates a new jcb_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attributes 
  /// domain_path, range_path, and scalar_space_path specified by
  /// xdomain_path and xrange_path, respectively.
  ///
  static jcb_space& new_table(namespace_type& xhost, 
			      const poset_path& xpath, 
			      const poset_path& xschema_path,
			      const poset_path& xdomain_path,
			      const poset_path& xrange_path,
			      bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

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
  /// creates a new jcb_space handle not attached to any state.
  ///
  jcb_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  jcb_space(const jcb_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~jcb_space();

  ///
  /// Covariant constructor
  ///
  jcb_space(jcb* xtop, jcb* xbottom);

private:

  //@}

  // ===========================================================
  /// @name POSET FACET
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

  ///
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  jcb_space& operator=(const poset_state_handle& xother);

protected:

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
  virtual jcb_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // JCB_SPACE_H
