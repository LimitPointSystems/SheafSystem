

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class stp_space.

#ifndef STP_SPACE_H
#define STP_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef TP_SPACE_H
#include "tp_space.h"
#endif
  
namespace fiber_bundle
{

  using namespace sheaf;  

  class stp;
  
  
///
/// An abstract symmetric tensor space of degree p.
///
class SHEAF_DLL_SPEC stp_space : public tp_space
{
  friend class fiber_bundles_namespace;

public:

  // ===========================================================
  /// @name STP_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef stp member_type;

  ///
  /// The name of the standard schema poset for this class.
  ///
  static const string& standard_schema_poset_name();

  ///
  /// The path to the standard schema for this class.
  ///
  static const poset_path& standard_schema_path();

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xp, const poset_path& xvector_space_path);

  using tp_space::p;
  
  ///
  /// Tensor degree implied by the tensor dimension (number of row dofs)
  /// defined by the schema specified by xschema_path and the dimension
  /// of the domain vector space specified by xvector_space_path.
  ///
  static int p(const namespace_poset& xns, 
               const poset_path& xschema_path, 
               const poset_path& xvector_space_path, 
               bool xauto_access);

  ///
  /// Creates a new stp_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and table attribute 
  /// vector_space_path specified by xvector_space_path.
  ///
  static void new_table(namespace_type& xhost, 
                        const poset_path& xpath, 
                        const poset_path& xschema_path,
                        const poset_path& xvector_space_path,
                        bool xauto_access);
  
protected:

  ///
  /// Default constructor;
  /// creates a new stp_space handle not attached to any state.
  ///
  stp_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  stp_space(const stp_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~stp_space();

  ///
  /// Covariant constructor
  ///
  stp_space(stp* xtop, stp* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  stp_space(namespace_poset& xhost,
	      const string& xname,
	      const arg_list& xargs,
	      const poset_path& xschema_path,
	      bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the stp_space with
  /// index xindex in namespace xhost.
  ///
  stp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the stp_space with
  /// index xindex in namespace xhost.
  ///
  stp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the stp_space with
  /// name xname in namespace xhost.
  ///
  stp_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the stp_space associated
  /// with namespace member xmbr.
  ///
  stp_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}

  // ===========================================================
  /// @name TP_SPACE FACET
  // ===========================================================
  //@{

public:

  using tp_space::d;
  
  ///
  /// Dimension d() as a function of degree xp and domain dimension xdd.
  ///
  virtual int d(int xp, int xdd) const;

  ///
  /// "Rounds" xvariance up or down to a supported value;
  /// either pure covariant or pure contravariant.
  ///
  virtual tensor_variance round_variance(const tensor_variance& xvariance) const;

protected:

  ///
  /// The number of covariant subposets.
  ///
  virtual size_type covariant_subposet_ct() const;

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
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  stp_space& operator=(const poset_state_handle& xother);

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
  virtual stp_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:
private:

  //@}
 
};


} // namespace fiber_bundle


#endif // STP_SPACE_H
