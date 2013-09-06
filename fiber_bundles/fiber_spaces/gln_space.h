

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class gln_space.

#ifndef GLN_SPACE_H
#define GLN_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef GLN_TABLE_DOFS_TYPE_H
#include "gln_table_dofs_type.h"
#endif
 

namespace sheaf
{
  class namespace_poset;
}

namespace fiber_bundle
{

  using namespace sheaf;  

  class gln;
  class vd_space;
  
///
/// A Cartesian product space.
///
class SHEAF_DLL_SPEC gln_space : public poset
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name GLN_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef gln member_type;

  ///
  /// The type of the vector space associated with this space.
  ///
  typedef vd_space vector_space_type;

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
  typedef gln_table_dofs_type table_dofs_type;

  ///
  /// The dimension of the representation space; n in GL(n, R) implied by the
  /// vector space specified by xvector_space_path.
  ///
  static int d(const namespace_poset& xns, const poset_path& xvector_space_path, bool xauto_access);

  ///
  /// The dimension of the representation space; n in GL(n, R) implied by the
  /// vector space with dimension specified by xn.
  ///
  static int d(int xn);

  ///
  /// Creates a new tp_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute
  /// vector_space_path specified by xvector_space_path.
  ///
  static gln_space& new_table(namespace_type& xhost, 
			      const poset_path& xpath, 
			      const poset_path& xschema_path,
			      const poset_path& xvector_space_path,
			      bool xauto_access);
  
  //============================================================================
  // TABLE DOFS
  //============================================================================

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n() const;

  ///
  /// Dimension of the representation space; n in GL(n, R).
  ///
  int n(bool xauto_access) const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path() const;

  ///
  /// The path of the underlying scalar space.
  ///
  poset_path scalar_space_path(bool xauto_access) const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path() const;

  ///
  /// The path of the underlying vector space.
  ///
  poset_path vector_space_path(bool xauto_access) const;

  ///
  /// Dimension of this as a vector space.
  ///
  virtual int d() const;

  ///
  /// Dimension of this as a vector space; auto-access version.
  ///
  int d(bool xauto_access) const;
 

protected:

  ///
  /// Default constructor;
  /// creates a new gln_space handle not attached to any state.
  ///
  gln_space();

  ///
  /// Copy constructor; disabled.
  ///
  gln_space(const gln_space& xother) { };

  ///
  /// Destructor.
  ///
  virtual ~gln_space();

  ///
  /// Covariant constructor
  ///
  gln_space(gln* xtop, gln* xbottom);

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

protected:

  ///
  /// Assignment operator; disabled.
  ///
  gln_space& operator=(const poset_state_handle& xother) { };

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
  virtual gln_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // GLN_SPACE_H
