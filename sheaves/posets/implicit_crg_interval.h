// $RCSfile: implicit_crg_interval.h,v $ $Revision: 1.2 $ $Date: 2013/01/10 13:55:03 $

// $Name: HEAD $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Interface for class implicit_crg_interval

#ifndef IMPLICIT_CRG_INTERVAL_H
#define IMPLICIT_CRG_INTERVAL_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef CRG_INTERVAL_H
#include "crg_interval.h"
#endif

namespace sheaf
{

// Forward declarations to support friend declaration.

class implicit_crg_interval;

///
/// Abstract implementation of crg_interval for an interval of implicit cover
/// relation graph members.
///
class SHEAF_DLL_SPEC implicit_crg_interval : public crg_interval
{

  friend SHEAF_DLL_SPEC size_t deep_size(const implicit_crg_interval& xp, bool xinclude_shallow);

  // ===========================================================
  /// @name IMPLICIT_CRG_INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default Constructor; constructs an uninitialized interval.
  ///
  implicit_crg_interval();

  ///
  /// Destructor
  ///
  virtual ~implicit_crg_interval();

protected:

private:

  //@}


  // ===========================================================
  /// @name IMPLICIT INTERVAL FACET
  // ===========================================================
  //@{

public:

  ///
  /// The beginning of the implicit member interval 
  /// (begin(), end()), excludes interval member;
  /// synonym for begin() + 1.
  ///
  pod_index_type implicit_begin() const;

  ///
  /// The beginning of the implicit member interval 
  /// (begin(), end()), excludes interval member;
  /// synonym for begin() + 1.
  ///
  void implicit_begin(scoped_index& result) const;

  ///
  /// The index of the interval member itself;
  /// synonym for begin().
  ///
  pod_index_type interval_member() const;

  ///
  /// The index of the interval member itself;
  /// synonym for begin().
  ///
  void interval_member(scoped_index& result) const;

  ///
  /// True if xindex is the interval member.
  ///
  bool is_interval_member(pod_index_type xindex) const;

  ///
  /// True if xindex is the interval member.
  ///
  bool is_interval_member(const scoped_index& xindex) const;

protected:

private:

  //@}


  // ===========================================================
  /// @name COVER SET FACET
  // ===========================================================
  //@{

public:

protected:

  ///
  /// Creates a name for the implicit cover id space for member with index, xmbr_index.
  ///
  static string implicit_cover_name(bool xlower, const scoped_index& xmbr_index);

  ///
  /// Creates a name for the implicit cover id space for member with index, xmbr_index.
  ///
  static string implicit_cover_name(bool xlower, pod_index_type xmbr_index);

private:

  //@}


  // ===========================================================
  /// @name DOF_TUPLE_ID FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  virtual bool is_jim(pod_index_type xmbr_index) const = 0;

  ///
  /// True if and only if the member with index xmbr_index is join-irreducible.
  ///
  bool is_jim(const scoped_index& xmbr_index) const;

  ///
  /// The dof tuple id of the member with index xmbr_index.
  ///
  virtual pod_index_type dof_tuple_id(pod_index_type xmbr_index) const = 0;

  ///
  /// The dof tuple id of the member with index xmbr_index.
  ///
  pod_index_type dof_tuple_id(const scoped_index& xmbr_index) const;

  ///
  /// The ids of the dof tuples associated with this interval.
  ///
  block<pod_index_type>& dof_tuple_ids();

  ///
  /// The ids of the dof tuples associated with this interval; const version.
  ///
  const block<pod_index_type>& dof_tuple_ids() const;

  ///
  /// True if dof tuple ids have been initialized
  ///
  bool dof_tuple_ids_initialized() const;

  ///
  /// Allocates and initializes dof_tuple_ids() with xdof_tuple_ids.
  ///
  void initialize_dof_tuple_ids(const block<pod_index_type>& xdof_tuple_ids);

protected:

  ///
  /// The ids of the dof tuples associated with this interval.
  ///
  block<pod_index_type> _dof_tuple_ids;

  ///
  /// True if dof tuple ids have been initialized
  ///
  bool _dof_tuple_ids_initialized;

private:

  //@}


  // ===========================================================
  /// @name I/O SUPPORT FACET
  // ===========================================================
  //@{

public:

  ///
  /// Removes members of the cover that are no longer members of the crg.
  ///
  void clean_cover(bool xlower, pod_index_type xmbr_index);

protected:

private:

  //@}


  // ===========================================================
  /// @name PRIVATE_DATA FACET
  // ===========================================================
  //@{

public:

  // $$SCRIBBLE: implicit-cover-reorganization
  // Made private data functions non-virtual.

  ///
  /// The size of the private data.
  ///
  size_type private_data_size() const;

  ///
  /// Initializes this using private data xdata.
  ///
  void get_private_data(block<pod_index_type>& xdata) const;

  ///
  /// Initializes this using private data xdata.
  ///
  void put_private_data(const block<pod_index_type>& xdata);

  ///
  /// True if private data has been initialized
  ///
  bool private_data_initialized() const;

protected:

  // $$SCRIBBLE: implicit-cover-reorganization
  // Added implicit private data function

  ///
  /// The size of the private data.
  ///
  virtual size_type implicit_private_data_size() const = 0;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void get_implicit_private_data(block<pod_index_type>& xdata) const = 0;

  ///
  /// Initializes this using private data xdata.
  ///
  virtual void put_implicit_private_data(const block<pod_index_type>& xdata) = 0;

  ///
  /// True if private data has been initialized
  ///
  bool _private_data_initialized;

private:

  //@}


  // ===========================================================
  /// @name FINIALIZE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Finialize the initialization of this crg interval in the host xhost.
  ///
  virtual void finalize(poset_state_handle& xhost);

protected:

  ///
  /// True if the initialization of this crg interval has been finalized.
  ///
  bool _is_finalized;

private:

  //@}


  // ===========================================================
  /// @name FACTORY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Sets is_initialized() == true;
  /// dummy routine provided to satisfy factory template.
  ///
  void initialize(const namespace_poset& xnamespace);

  ///
  /// True if fully initialized.
  ///
  virtual bool is_initialized() const;

  ///
  /// The name of this class;
  /// provided to satisfy factory template.
  ///
  virtual const string& class_name() const;

protected:

private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual implicit_crg_interval* clone() const = 0;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

///
/// The deep size of the referenced object of type implicit_crg_interval;
/// if xinclude_shallow, add the sizeof xp to the result.
///
SHEAF_DLL_SPEC 
size_t deep_size(const implicit_crg_interval& xp, bool xinclude_shallow = true);

} // namespace sheaf

#endif // ifndef IMPLICIT_CRG_INTERVAL_H
