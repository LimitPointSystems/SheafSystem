


//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class sec_stp_space.

#ifndef SEC_STP_SPACE_H
#define SEC_STP_SPACE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef SEC_TP_SPACE_H
#include "sec_tp_space.h"
#endif

namespace sheaf
{
class arg_list;
class namespace_poset;
}

namespace fiber_bundle
{
using namespace sheaf;

class sec_stp;
class stp;

///
/// An abstract symmetric tensor section space of degree p.
///
class SHEAF_DLL_SPEC sec_stp_space : public sec_tp_space
{
  friend class fiber_bundles_namespace;

  // ===========================================================
  /// @name SEC_STP_SPACE FACET
  // ===========================================================
  //@{

public:

  ///
  /// The type of member associated with this space.
  ///
  typedef sec_stp member_type;

  ///
  /// The fiber type.
  ///
  typedef stp fiber_type;

  ///
  /// The scalar type definition.
  ///
  typedef sec_stp scalar_type;

  ///
  /// Creates an arg list which conforms to the schema of this.
  ///
  static arg_list make_arg_list(int xp, const poset_path& xvector_space_path);
  
  ///
  /// Creates a new sec_atp_space in namespace xns with path xpath,
  /// schema specified by xschema_path, and vector space specified
  /// by xvector_space_path.
  ///
  static sec_stp_space& new_table(namespace_type& xhost, 
                                 const poset_path& xpath, 
                                 const poset_path& xschema_path,
                                 const poset_path& xvector_space_path,
                                 bool xauto_access);
  
protected:

  ///
  /// Default constructor;
  /// creates a new sec_stp_space handle not attached to any state.
  ///
  sec_stp_space();

  ///
  /// Copy constructor; attaches this to the same state as xother.
  ///
  sec_stp_space(const sec_stp_space& xother);

  ///
  /// Destructor.
  ///
  virtual ~sec_stp_space();

  ///
  /// Covariant constructor
  ///
  sec_stp_space(sec_stp* xtop, sec_stp* xbottom);

  //============================================================================
  // NEW HANDLE, NEW STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new poset handle attached to a new state in namespace xhost,
  /// with schema specified by xschema_path,  name xname, and
  /// table dofs initialized by xargs.
  ///
  sec_stp_space(namespace_poset& xhost,
		const string& xname,
		const arg_list& xargs,
		const poset_path& xschema_path,
		bool xauto_access);

  //============================================================================
  // NEW HANDLE, EXISTING STATE CONSTRUCTORS
  //============================================================================

  ///
  /// Creates a new handle attached to the sec_stp_space with
  /// index xindex in namespace xhost.
  ///
  sec_stp_space(const namespace_poset& xhost, pod_index_type xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_stp_space with
  /// index xindex in namespace xhost.
  ///
  sec_stp_space(const namespace_poset& xhost, const scoped_index& xindex, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_stp_space with
  /// name xname in namespace xhost.
  ///
  sec_stp_space(const namespace_poset& xhost, const string& xname, bool xauto_access);

  ///
  /// Creates a new handle attached to the sec_stp_space associated
  /// with namespace member xmbr.
  ///
  sec_stp_space(const namespace_poset_member& xmbr, bool xauto_access);

private:

  //@}


  // ===========================================================
  /// @name SEC_TP_SPACE FACET
  // ===========================================================
  //@{

public:

  using sec_tp_space::d;
  
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
  /// Assignment operator; attaches this to the same state as xother.
  /// @issue This is probably the wrong signature for operator=,
  /// see thread Misc/Language/covariance in C++/covariance and operator=
  /// in the discusion forum. But it is consistent with all the
  /// other derivatives of poset_state_handle and it will soon be refactored
  /// out of existence any way.
  ///
  sec_stp_space& operator=(const poset_state_handle& xother);

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
  virtual sec_stp_space* clone() const;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 
};


} // namespace fiber_bundle


#endif // SEC_STP_SPACE_H
